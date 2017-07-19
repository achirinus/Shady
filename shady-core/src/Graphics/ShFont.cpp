#include "ShFont.h"


namespace Shady
{

	Font::~Font()
	{
		for(u32 index = 0; index < mGlyphs.size(); index++)
		{
			Texture* tex = mGlyphs[mGlyphs.getKeyByIndex(index)].texture;
			delete tex;
		}

		delete mShader;
	}

	Font::Font(): mGlyphs(), mFontSize(30.0f)
	{
		mShader = new Shader("text", SH_FRAGMENT_SHADER | SH_VERTEX_SHADER);
		STBloadSupportedGlyphs(mFontSize);
	}


	//TODO Codepoint glyphs are for now stored in video memory,
	//decide where to keep them.
	Texture* Font::STBgetGlyphTexture(stbtt_fontinfo* fontInfo, c8 cp, f32 scale)
	{
		int width, height, xOffset, yOffset;
		u8* monoBitmap = stbtt_GetCodepointBitmap(fontInfo, 0, scale, cp,
													&width, &height, &xOffset, &yOffset);
		
		Bitmap goodBmp = get32bppBitmapFrom8bpp(monoBitmap, width, height);

		Texture* result = new Texture(goodBmp);
		freeBitmap(goodBmp);
		stbtt_FreeBitmap(monoBitmap, 0);
		return result;
	}

	void Font::STBloadSupportedGlyphs(f32 sizeInPixels)
	{
		BinaryFileContent fileResult = File::win32ReadBinaryFile("c:/windows/fonts/arial.ttf");
		stbtt_fontinfo fontInfo;
		stbtt_InitFont(&fontInfo, (u8*)fileResult.contents, 
						stbtt_GetFontOffsetForIndex((u8*)fileResult.contents, 0));
		f32 scale = stbtt_ScaleForPixelHeight(&fontInfo, sizeInPixels);

		//Advance v position by (ascent - descent + linegap)
		stbtt_GetFontVMetrics(&fontInfo, &mAscent, &mDescent, &mLineGap);

		for(c8 cp = MIN_ASCII_CODEPOINT; cp <= MAX_ASCII_CODEPOINT; cp++)
		{
			Texture* tex = STBgetGlyphTexture(&fontInfo, cp, scale);
			s32 advanceW;
			s32 leftBearing;
			stbtt_GetCodepointHMetrics(&fontInfo, cp, &advanceW, &leftBearing);
			mGlyphs.add(cp,  {tex, advanceW, leftBearing});
		}
	}

	Text2D* Font::getText(Vec3f pos, const c8* str, f32 size)
	{
		f32 scale = size / mFontSize;
		Text2D* result = new Text2D(mShader);
		while(*str)
		{
			if(*str == ' ')
			{
				pos += {mFontSize * scale, 0.0f, 0.0f};
				str++;
				continue;	
			}
			result->addGlyph(new Glyph(pos, mGlyphs[*str].texture, mShader));
			pos += {mFontSize * scale, 0.0f, 0.0f};
			str++;
		}
		return result;
	}



	Texture* Font::getGlyph(c8 codePoint)
	{
		return mGlyphs[codePoint].texture;
	}
}