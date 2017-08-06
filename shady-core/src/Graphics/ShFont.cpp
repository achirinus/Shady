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

	Font::Font(): mGlyphs(), mFontSize(60.0f)
	{
		mShader = new Shader("text", SH_FRAGMENT_SHADER | SH_VERTEX_SHADER);
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
		BinaryFileContent fileResult = File::win32ReadBinaryFile("c:/windows/fonts/arial.ttf");
		
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
			mGlyphs.add(cp,  {tex, advanceW * mScale, leftBearing * mScale});
		}
	}

	Text2D* Font::getText(Vec3f pos, const c8* str, f32 size)
	{
		f32 baseLine = pos.y  + mAscent;
		f32 scale = size / mFontSize;
		Vec3f initialRowPos = pos;
		Vec3f lastCharPos = initialRowPos;
		Text2D* result = new Text2D(mShader);
		c8 lastChar = 0;
		s32 kernAdvance = 0;
		GlyphData* lastGlyphData = 0;
		while(*str)
		{
			Vec3f thisPos = lastCharPos;
			if(*str == ' ')
			{
				thisPos += {mFontSize * scale * mScale, 0.0f, 0.0f};
				Vec3f thisPos = lastCharPos;
				lastChar = *str;
				lastGlyphData = 0;
				str++;
				continue;	
			}
			GlyphData* data = &mGlyphs[*str];
			
			if(lastGlyphData)
			{
				thisPos.x += (lastGlyphData->mAdvanceWidth * 2 * scale) - 
				lastGlyphData->mLeftSideBearing + 
				stbtt_GetCodepointKernAdvance(&mFontInfo, lastChar, *str);
			}
			else
			{
				thisPos.x += size * 2;
			}
			thisPos.y =baseLine - data->texture->getHeight();
			
			Glyph* glyph = new Glyph(thisPos, data->texture, mShader);
			glyph->scale(scale);
			result->addGlyph(glyph);
			
			lastCharPos = thisPos;
			lastChar = *str;
			lastGlyphData = data;
			str++;
		}
		return result;
	}

	Texture* Font::getGlyph(c8 codePoint)
	{
		return mGlyphs[codePoint].texture;
	}
}