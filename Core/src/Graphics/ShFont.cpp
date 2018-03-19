#include "ShFont.h"
#include "ShadyApp.h"
#include "Line2D.h"
#include "ShaderManager.h"
#include "DebugHelper.h"

#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"
namespace Shady
{
#define DEFAULT_FONT_SIZE 40.0f

	Font::~Font()
	{
		for(u32 index = 0; index < mGlyphs.Size(); index++)
		{
			Texture* tex = mGlyphs[mGlyphs.GetKeyByIndex(index)].texture;
			delete tex;
		}
	}

	Font::Font(): mGlyphs(), mFontSize(DEFAULT_FONT_SIZE)
	{
		mShader = ShaderManager::CreateShader("text");
		STBloadSupportedGlyphs(mFontSize);
	}


	//TODO Codepoint glyphs are for now stored in video memory,
	//decide where to keep them.
	Texture* Font::STBgetGlyphTexture(stbtt_fontinfo* fontInfo, c8 cp,
										s32* xOffset, s32* yOffset)
	{
		s32 width, height;
		u8* monoBitmap = stbtt_GetCodepointBitmap(fontInfo, 0, mScale, cp,
													&width, &height, xOffset, yOffset);
		
		Bitmap goodBmp = get32bppBitmapFrom8bpp(monoBitmap, width, height);

		Texture* result = new Texture(goodBmp);
		freeBitmap(goodBmp);
		stbtt_FreeBitmap(monoBitmap, 0);
		return result;
	}

	void Font::STBloadSupportedGlyphs(f32 sizeInPixels)
	{
		Win32BinaryFileContent fileResult = File::win32ReadBinaryFile("c:/windows/fonts/arial.ttf");
		
		stbtt_InitFont(&mFontInfo, (u8*)fileResult.contents, 
						stbtt_GetFontOffsetForIndex((u8*)fileResult.contents, 0));
		mScale = stbtt_ScaleForPixelHeight(&mFontInfo, sizeInPixels);

		//Advance v position by (ascent - descent + linegap)
		stbtt_GetFontVMetrics(&mFontInfo, &mAscent, &mDescent, &mLineGap);
		mAscent = mAscent * mScale;
		mDescent = mDescent * mScale;
		mLineGap = mLineGap * mScale;

		for(c8 cp = MIN_ASCII_CODEPOINT; cp <= MAX_ASCII_CODEPOINT; cp++)
		{
			s32 advanceW, leftBearing, xOffset, yOffset;
			Texture* tex = STBgetGlyphTexture(&mFontInfo, cp, &xOffset, &yOffset);
			stbtt_GetCodepointHMetrics(&mFontInfo, cp, &advanceW, &leftBearing);
			mGlyphs.Add(cp,  {tex, advanceW * mScale, leftBearing * mScale, xOffset, yOffset});
		}
		fileResult.Clear();
	}

	Text2D* Font::GetText(Vec3f pos, const c8* str, f32 size)
	{
		AUTO_TIMED_FUNCTION();
		if (!str) return nullptr;

		f32 baseLine = pos.y;
		u32 numOfChars = 0;

		f32 scale = size / mFontSize;
		Text2D* result = new Text2D(mShader);
		result->mPos = pos;
		Vec3f lastCharPos = result->mPos;
		c8 lastChar = 0;
		f32 kernAdvance = 0;
		GlyphData* lastGlyphData = 0;
		while (*str)
		{
			Vec3f thisPos = lastCharPos;
			;
			GlyphData* data = 0;
			if (*str == '\n')
			{
				thisPos.x = pos.x;
				baseLine += (f32)mAscent* scale - (f32)mDescent * scale + (f32)mLineGap*scale - 10.0f;
			}
			else
			{

				if (*str == ' ')
				{
					data = &mGlyphs['e'];
				}
				else
				{
					data = &mGlyphs[*str];
				}

				if (!data)
				{
					lastGlyphData = data;
					lastChar = *str;

					str++;
					continue;
				}
				if (lastGlyphData)
				{
					/*
					if (lastGlyphData != data)
					{
					if ((lastChar == 'T') && (*str == 'i'))
					{
					kernAdvance = 0.0f;
					}
					else
					{
					kernAdvance = stbtt_GetCodepointKernAdvance(&mFontInfo, lastChar, *str);
					kernAdvance = Clamp(kernAdvance, -1.0f, 1.0f);
					}

					}
					else
					{
					kernAdvance = 0.f;
					}
					*/

					thisPos.x += lastGlyphData->mAdvanceWidth * scale
						+ kernAdvance * scale - scale * lastGlyphData->mLeftSideBearing;
				}

				thisPos.y = baseLine - (f32)data->texture->getHeight() * scale +
					((f32)data->texture->getHeight() * scale
						+ (f32)data->mYOff * scale);
				thisPos.y += scale * (f32)mAscent + (f32)mDescent * scale;
				if (*str != ' ')
				{

					Glyph* glyph = new Glyph(thisPos, data->texture, mShader);
					glyph->mChar = *str;
					glyph->scale(scale);
					glyph->SetTransparency(true);
					result->addGlyph(glyph);
				}
			}
			lastCharPos = thisPos;
			lastChar = *str;
			lastGlyphData = data;
			str++;
			numOfChars++;
		}
		return result;
	}

	Texture* Font::GetGlyph(c8 codePoint)
	{
		return mGlyphs[codePoint].texture;
	}
}