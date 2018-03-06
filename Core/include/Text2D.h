#ifndef SH_TEXT_2D_H
#define SH_TEXT_2D_H

#include "Renderable2D.h"
#include "ShTypes.h"
#include "GlyphData.h"
#include "Glyph.h"
#include "ShArray.h"

namespace Shady
{
	class Text2D : public Renderable2D
	{
	private:
		Array<Glyph*> mGlyphs;
		
	public:
		Text2D(Shader* shader);
		virtual void draw();
		virtual ~Text2D();

		void addGlyph(Glyph* glyph);
		Glyph* operator[](u32 index) { return mGlyphs[index];}
		u32 size() { return mGlyphs.Size();}
	};
}

#endif