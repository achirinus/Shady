#include "ShFont.h"
#include "ShadyApp.h"
#include "Line2D.h"
#include "ShaderManager.h"
#include "DebugHelper.h"
#include "MemUtils.h"


#define STB_TRUETYPE_IMPLEMENTATION
#define STB_RECT_PACK_IMPLEMENTATION
#include "stb_rect_pack.h"
#include "stb_truetype.h"

namespace Shady
{
#define DEFAULT_FONT_SIZE 20

	Font::~Font()
	{
		for (u32 i = 0; i < mAtlasGlyphs.Size(); ++i)
		{
			delete mAtlasGlyphs[mAtlasGlyphs.GetKeyByIndex(i)].Atlas;
		}
	}

	Font::Font()
	{
		mShader = ShaderManager::CreateShader("text");
		BinaryFileContent fileResult = File::ReadBinaryFile("c:/windows/fonts/arial.ttf");
		if (!stbtt_InitFont(&mFontInfo, (u8*)fileResult.Data, stbtt_GetFontOffsetForIndex((u8*)fileResult.Data, 0)))
		{
			DEBUG_OUT_ERR("Failed to Initialize font!");
		}
		File::ClearContent(&fileResult);
		STBLoadAtlasData(DEFAULT_FONT_SIZE);
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

	void Font::STBLoadAtlasData(u32 size)
	{
		f32 scale = stbtt_ScaleForPixelHeight(&mFontInfo, size);
		stbtt_GetFontVMetrics(&mFontInfo, &mAscent, &mDescent, &mLineGap);
		u32 NumOFChars = MAX_ASCII_CODEPOINT - MIN_ASCII_CODEPOINT;
		Array<Bitmap> AllBitmaps{NumOFChars};

		MultiMap<c8, GlyphData> GlyphsToCache;
		for (c8 cp = MIN_ASCII_CODEPOINT; cp <= MAX_ASCII_CODEPOINT; cp++)
		{
			s32 advanceW, leftBearing, xOffset, yOffset;

			s32 width, height;
			u8* monoBitmap = stbtt_GetCodepointBitmap(&mFontInfo, 0, scale, cp,
				&width, &height, &xOffset, &yOffset);

			Bitmap goodBmp = get32bppBitmapFrom8bpp(monoBitmap, width, height);
			AllBitmaps.Add(goodBmp);
			stbtt_FreeBitmap(monoBitmap, 0);
			stbtt_GetCodepointHMetrics(&mFontInfo, cp, &advanceW, &leftBearing);
			GlyphsToCache.Add(cp, { advanceW * scale, leftBearing * scale, xOffset, yOffset, scale, cp, {}, {}, (u32)width, (u32)height });
		}
		u32 Padding = 5;
		u32 GlyphsPerLine = 10;
		u32 LineSize = GlyphsPerLine * (size + Padding);
		u32* AtlasPixels = new u32[LineSize * LineSize];
		ZeroMem(AtlasPixels, LineSize * LineSize * sizeof(u32));
		Bitmap AtlasBmp{};
		AtlasBmp.bpp = 4;
		AtlasBmp.contents = AtlasPixels;
		AtlasBmp.width = LineSize;
		AtlasBmp.height = LineSize;
		u32 LastX = 0;
		u32 LastY = 0;
		u32 BitMapIndex = 0;
		
		for (c8 cp = MIN_ASCII_CODEPOINT; cp <= MAX_ASCII_CODEPOINT; cp++)
		{

			Bitmap Bmp = AllBitmaps[BitMapIndex++];
			if (!Bmp.width || !Bmp.height) continue;
			if (BitMapIndex % GlyphsPerLine == 0)
			{
				LastY += size + Padding;
				LastX = 0;
			}
			Vec2f TopLeftCoords{ Get01FromRange(LastX, 0, LineSize), Get01FromRange(LastY, 0, LineSize) };
			Vec2f BotRightCoords{ Get01FromRange(LastX + Bmp.width, 0, LineSize), Get01FromRange(LastY + Bmp.height, 0, LineSize) };
			BlitRectInBitmap(Bmp.contents, Bmp.width, Bmp.height, LastX, LastY, AtlasPixels, LineSize, LineSize);
			GlyphsToCache[cp].mAtlasCoordsTopLeft = TopLeftCoords;
			GlyphsToCache[cp].mAtlasCoordsBotRight = BotRightCoords;
			LastX += Bmp.width + Padding;
		}
		Texture* AtlasTex = new Texture(AtlasBmp);

		mAtlasGlyphs.Add(size, {AtlasTex, GlyphsToCache });
		
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

		if (!mAtlasGlyphs.HasKey(size))
		{
			STBLoadAtlasData(size);
		}

		MultiMap<c8, GlyphData>& Glyphs = mAtlasGlyphs[size].mCachedGlyphs;
		Texture* Atlas = mAtlasGlyphs[size].Atlas;
		result->SetTextureAtlas(Atlas);
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

				thisPos.y = baseLine - (f32)data->mHeight + (f32)data->mHeight + (f32)data->mYOff;
				thisPos.y += SizedAscent + SizedDescent;
				
				Glyph* glyph = new Glyph(thisPos, *data);
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

		if (!mAtlasGlyphs.HasKey(size))
		{
			STBLoadAtlasData(size);
		}

		MultiMap<c8, GlyphData>& Glyphs = mAtlasGlyphs[size].mCachedGlyphs;

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
				WidthThisLine = thisPos.x + data->mWidth;
				thisPos.y = baseLine - (f32)data->mHeight + (f32)data->mHeight + (f32)data->mYOff;
				thisPos.y += SizedAscent + SizedDescent;
				Height = thisPos.y + data->mHeight;
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

	Text2D* Font::GetTextWrappedToBounds(Vec3f pos, const c8* str, u32 size, Rect bounds)
	{
		Text2D* result = nullptr;
		//TODO: not leave this blank

		return result;
	}

}