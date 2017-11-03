#include "Text2D.h"

namespace Shady
{

	Text2D::Text2D(Shader* shader)
	{
		mShaders.Add(shader);
	}
	void Text2D::draw()
	{
		for(u32 gIndex = 0; gIndex < mGlyphs.Size(); gIndex++)
		{
			mGlyphs[gIndex]->draw();
		}
	}

	void Text2D::addGlyph(Glyph* glyph)
	{
		mGlyphs.Add(glyph);
	}

	Text2D::~Text2D()
	{
		for(u32 gIndex = 0; gIndex < mGlyphs.Size(); gIndex++)
		{
			delete mGlyphs[gIndex];
		}
	}
}