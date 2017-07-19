#ifndef SH_GLYPH_DATA_H
#define SH_GLYPH_DATA_H

#include "ShadyTypes.h"
#include "Texture.h"

namespace Shady
{
	struct GlyphData
	{
		Texture* texture;
		s32 mAdvanceWidth;
		s32 mLeftSideBearing;
	};
}

#endif