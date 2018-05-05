#ifndef SH_FONT_H
#define SH_FONT_H

#include "ShMultiMap.h"
#include "Texture.h"

#include "stb_truetype.h"
#include "GlyphData.h"
#include "Text2D.h"
#include "Vec3.h"
#include "ShMath.h"

#define MIN_ASCII_CODEPOINT 32 // Space
#define MAX_ASCII_CODEPOINT 126 // ~
#define NUM_OF_SUPPORTED_GLYPHS (MAX_ASCII_GLYPH - MIN_ASCII_GLYPH)

namespace Shady
{
	struct AtlasedGlyphData
	{
		Texture* Atlas;
		MultiMap<c8, GlyphData> mCachedGlyphs;
	};
	class Font
	{
	private:
		stbtt_fontinfo mFontInfo;
		Texture* STBgetGlyphTexture(stbtt_fontinfo* fontInfo, c8 cp,
									s32* xOffset, s32* yOffset, f32 scale);
		
		void STBLoadAtlasData(u32 size);

	public:
		~Font();
		Font();
		MultiMap<u32, AtlasedGlyphData> mAtlasGlyphs;
		Shader* mShader;
		s32 mAscent;
		s32 mDescent;
		s32 mLineGap;
		
		Text2D* GetText(Vec3f pos, const c8* str, u32 size);
		Vec2f GetTextDim(const c8* str, u32 size);
		Text2D* GetTextWrappedToBounds(Vec3f pos, const c8* str, u32 size, Rect bounds);
	};
}

#endif