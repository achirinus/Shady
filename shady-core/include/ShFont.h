#ifndef SH_FONT_H
#define SH_FONT_H

#include "ShMap.h"
#include "Texture.h"
#define STB_TRUETYPE_IMPLEMENTATION
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
		Map<c8, GlyphData> mGlyphs;

		Texture* STBgetGlyphTexture(stbtt_fontinfo* fontInfo, c8 cp, f32 scale);
		void STBloadSupportedGlyphs(f32 sizeInPixels);

	public:
		~Font();
		Font();

		Shader* mShader;
		s32 mAscent;
		s32 mDescent;
		s32 mLineGap;
		f32 mFontSize;

		Text2D* getText(Vec3f pos, const c8* str, f32 size);
		Texture* getGlyph(c8 codePoint);

	};
}

#endif