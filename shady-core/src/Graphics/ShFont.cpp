#include "ShFont.h"


namespace Shady
{

	Font::~Font()
	{
		for(u32 index = 0; index < mGlyphs.size(); index++)
		{
			Texture* tex = mGlyphs[mGlyphs.getKeyByIndex(index)];
			delete tex;
		}
	}

	Font::Font(): mGlyphs()
	{
		STBloadSupportedGlyphs(120.0f);
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

		for(c8 cp = MIN_ASCII_CODEPOINT; cp <= MAX_ASCII_CODEPOINT; cp++)
		{
			mGlyphs.add(cp, STBgetGlyphTexture(&fontInfo, cp, scale));
		}
	}

	Texture* Font::getGlyph(c8 codePoint)
	{
		return mGlyphs[codePoint];
	}
}