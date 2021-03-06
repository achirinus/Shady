#ifndef SH_GLYPH_DATA_H
#define SH_GLYPH_DATA_H

#include "ShTypes.h"
#include "Texture.h"

namespace Shady
{
	struct GlyphData
	{
		f32 mAdvanceWidth;
		f32 mLeftSideBearing;
		s32 mXOff;
		s32 mYOff;
		f32 mScale;
		c8 mChar;
		Vec2f mAtlasCoordsTopLeft;
		Vec2f mAtlasCoordsBotRight;
		u32 mWidth;
		u32 mHeight;
	};
}

#endif