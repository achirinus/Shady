#ifndef SH_GLYPH_H
#define SH_GLYPH_H

#include <ShadyGL.h>
#include "Sprite.h"
namespace Shady
{
	class Glyph : public Sprite
	{
	public:
		Glyph(const Vec3f& pos, u32 width, u32 height, Texture* texture, Shader* shader = 0);
		virtual ~Glyph();
		//virtual void draw();
		char mChar;
		f32 mAdvanceWidth;
	};
}

#endif