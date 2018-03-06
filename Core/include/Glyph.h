#ifndef SH_GLYPH_H
#define SH_GLYPH_H

#include <ShadyGL.h>
#include "Sprite.h"
namespace Shady
{
	class Glyph : public Sprite
	{
	public:
		Glyph(const Vec3f& pos, Texture* texture, Shader* shader = 0);
		virtual ~Glyph();
		//virtual void draw();
		
	};
}

#endif