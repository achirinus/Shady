#ifndef SH_FONT_H
#define SH_FONT_H

#include "ShMultiMap.h"
#include "Texture.h"

#include "stb_truetype.h"
#include "GlyphData.h"
#include "Text2D.h"
#include "Vec3.h"


#define MIN_ASCII_CODEPOINT 33 // !
#define MAX_ASCII_CODEPOINT 126 // ~
#define NUM_OF_SUPPORTED_GLYPHS (MAX_ASCII_GLYPH - MIN_ASCII_GLYPH)

namespace Shady
{
	
	class Font
	{
	private:
		MultiMap<c8, GlyphData> mGlyphs;
		stbtt_fontinfo mFontInfo;

		Texture* STBgetGlyphTexture(stbtt_fontinfo* fontInfo, c8 cp,
									s32* xOffset, s32* yOffset);
		void STBloadSupportedGlyphs(f32 sizeInPixels);

	public:
		~Font();
		Font();

		Shader* mShader;
		s32 mAscent;
		s32 mDescent;
		s32 mLineGap;
		f32 mFontSize;
		f32 mScale;

		Text2D* GetText(Vec3f pos, const c8* str, f32 size);
		Texture* GetGlyph(c8 codePoint);

	};
}

#endif