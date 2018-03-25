#include "ShFont.h"
#include "ShadyApp.h"
#include "Line2D.h"
#include "ShaderManager.h"
#include "DebugHelper.h"

#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"
namespace Shady
{
#define DEFAULT_FONT_SIZE 20

	Font::~Font()
	{
		for(u32 index = 0; index < mGlyphs.Size(); index++)
		{
			Texture* tex = mGlyphs[mGlyphs.GetKeyByIndex(index)].texture;
			delete tex;
		}
	}

	Font::Font(): mGlyphs()
	{
		mShader = ShaderManager::CreateShader("text");
		Win32BinaryFileContent fileResult = File::win32ReadBinaryFile("c:/windows/fonts/arial.ttf");
		if (!stbtt_InitFont(&mFontInfo, (u8*)fileResult.contents, stbtt_GetFontOffsetForIndex((u8*)fileResult.contents, 0)))
		{
			DEBUG_OUT_ERR("Failed to Initialize font!");
		}
		fileResult.Clear();
		STBloadSupportedGlyphs(DEFAULT_FONT_SIZE);
	}

	//TODO Codepoint glyphs are for now stored in video memory,
	//decide where to keep them.
	Texture* Font::STBgetGlyphTexture(stbtt_fontinfo* fontInfo, c8 cp,
										s32* xOffset, s32* yOffset, f32 scale)
	{
		s32 width, height;
		u8* monoBitmap = stbtt_GetCodepointBitmap(fontInfo, 0, scale, cp,
													&width, &height, xOffset, yOffset);
		
		Bitmap goodBmp = get32bppBitmapFrom8bpp(monoBitmap, width, height);

		Texture* result = new Texture(goodBmp);
		freeBitmap(goodBmp);
		stbtt_FreeBitmap(monoBitmap, 0);
		return result;
	}

	void Font::STBloadSupportedGlyphs(u32 sizeInPixels)
	{
		f32 scale = stbtt_ScaleForPixelHeight(&mFontInfo, sizeInPixels);

		//Advance v position by (ascent - descent + linegap)
		stbtt_GetFontVMetrics(&mFontInfo, &mAscent, &mDescent, &mLineGap);
		
		MultiMap<c8, GlyphData> GlyphsToCache;
		for(c8 cp = MIN_ASCII_CODEPOINT; cp <= MAX_ASCII_CODEPOINT; cp++)
		{
			s32 advanceW, leftBearing, xOffset, yOffset;
			Texture* tex = STBgetGlyphTexture(&mFontInfo, cp, &xOffset, &yOffset, scale);
			stbtt_GetCodepointHMetrics(&mFontInfo, cp, &advanceW, &leftBearing);
			GlyphsToCache.Add(cp,  {tex, advanceW * scale, leftBearing * scale, xOffset, yOffset, scale, cp});
		}
		mCachedGlyphs.Add(sizeInPixels, GlyphsToCache);
		
	}

	Text2D* Font::GetText(Vec3f pos, const c8* str, u32 size)
	{
		AUTO_TIMED_FUNCTION();
		if (!str) return nullptr;

		f32 baseLine = pos.y;
		u32 numOfChars = 0;

		Text2D* result = new Text2D(mShader);
		result->mPos = pos;
		Vec3f lastCharPos = result->mPos;
		c8 lastChar = 0;
		f32 kernAdvance = 0;
		GlyphData* lastGlyphData = 0;

		if (!mCachedGlyphs.HasKey(size))
		{
			STBloadSupportedGlyphs(size);
		}

		MultiMap<c8, GlyphData>& Glyphs = mCachedGlyphs[size];

		GlyphData& TempGlyph = Glyphs['a'];

		f32 SizedAscent = mAscent * TempGlyph.mScale;
		f32 SizedDescent = mDescent * TempGlyph.mScale;
		f32 SizedLineGap = mLineGap * TempGlyph.mScale;

		while (*str)
		{
			Vec3f thisPos = lastCharPos;
			
			GlyphData* data = 0;
			if (*str == '\n')
			{
				thisPos.x = pos.x;
				baseLine += SizedAscent - SizedDescent + SizedLineGap;
			}
			else
			{
				data = &Glyphs[*str];
				
				if (!data)
				{
					lastGlyphData = data;
					lastChar = *str;
					str++;
					continue;
				}
				if (lastGlyphData)
				{
					kernAdvance = stbtt_GetCodepointKernAdvance(&mFontInfo, lastChar, *str);
					kernAdvance *= data->mScale;
					
					thisPos.x += lastGlyphData->mAdvanceWidth + kernAdvance - lastGlyphData->mLeftSideBearing +data->mXOff;
				}

				thisPos.y = baseLine - (f32)data->texture->getHeight() + (f32)data->texture->getHeight() + (f32)data->mYOff;
				thisPos.y += SizedAscent + SizedDescent;
				
				Glyph* glyph = new Glyph(thisPos, *data, mShader);
				//glyph->SetTransparency(true);
				result->addGlyph(glyph);
			}
			lastCharPos = thisPos;
			lastChar = *str;
			lastGlyphData = data;
			str++;
			numOfChars++;
		}
		return result;
	}

	Vec2f Font::GetTextDim(const c8* str, u32 size)
	{
		AUTO_TIMED_FUNCTION();
		Vec2f result{};
		if (!str) return result;

		f32 baseLine = 0;
		u32 numOfChars = 0;
		
		Vec3f lastCharPos{};
		c8 lastChar = 0;
		f32 kernAdvance = 0;
		GlyphData* lastGlyphData = 0;

		if (!mCachedGlyphs.HasKey(size))
		{
			STBloadSupportedGlyphs(size);
		}

		MultiMap<c8, GlyphData>& Glyphs = mCachedGlyphs[size];

		GlyphData& TempGlyph = Glyphs['a'];

		f32 SizedAscent = mAscent * TempGlyph.mScale;
		f32 SizedDescent = mDescent * TempGlyph.mScale;
		f32 SizedLineGap = mLineGap * TempGlyph.mScale;

		f32 MaxWidth = 0.f;
		f32 WidthThisLine = 0.f;
		f32 Height = 0.f;
		while (*str)
		{
			Vec3f thisPos = lastCharPos;

			GlyphData* data = 0;
			if (*str == '\n')
			{
				if (WidthThisLine > MaxWidth) MaxWidth = WidthThisLine;
				thisPos.x = 0;
				baseLine += SizedAscent - SizedDescent + SizedLineGap;
			}
			else
			{
				data = &Glyphs[*str];

				if (!data)
				{
					lastGlyphData = data;
					lastChar = *str;
					str++;
					continue;
				}
				if (lastGlyphData)
				{
					kernAdvance = stbtt_GetCodepointKernAdvance(&mFontInfo, lastChar, *str);
					kernAdvance *= data->mScale;

					thisPos.x += lastGlyphData->mAdvanceWidth + kernAdvance - lastGlyphData->mLeftSideBearing + data->mXOff;
					
				}
				WidthThisLine = thisPos.x + data->texture->getWidth();
				thisPos.y = baseLine - (f32)data->texture->getHeight() + (f32)data->texture->getHeight() + (f32)data->mYOff;
				thisPos.y += SizedAscent + SizedDescent;
				Height = thisPos.y + data->texture->getHeight();
			}
			lastCharPos = thisPos;
			lastChar = *str;
			lastGlyphData = data;
			str++;
			numOfChars++;
		}
		if (MaxWidth > 0.f)
		{
			result.x += MaxWidth;
		}
		else
		{
			result.x += WidthThisLine;
		}
		
		result.y += Height;
		return result;
	}
	Texture* Font::GetGlyphTexture(c8 codePoint, u32 size)
	{
		return mGlyphs[codePoint].texture;
	}
}