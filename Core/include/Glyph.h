#ifndef SH_GLYPH_H
#define SH_GLYPH_H

#include <ShadyGL.h>
#include "Sprite.h"
#include "GlyphData.h"
namespace Shady
{
	class Glyph : public Sprite
	{
	public:
		Glyph(const Vec3f& pos, u32 width, u32 height, Texture* texture, Shader* shader = 0);
		Glyph(const Vec3f& pos, GlyphData data, Shader* shader);
		virtual ~Glyph();
		
		GlyphData mData;
	};
}

#endif