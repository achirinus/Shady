#ifndef SH_GLYPH_H
#define SH_GLYPH_H

#include <ShadyGL.h>
#include "Sprite.h"
#include "GlyphData.h"
namespace Shady
{
	class Glyph
	{
	public:
		Glyph(const Vec3f& pos, GlyphData data);
		~Glyph();
		
		Vec3f mPos;
		GlyphData mData;
	};
}

#endif