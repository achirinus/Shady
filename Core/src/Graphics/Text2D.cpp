#include "Text2D.h"

namespace Shady
{

	Text2D::Text2D(Shader* shader)
	{
		mShader = shader;
	}
	void Text2D::draw(Renderer2D* renderer)
	{
		for(u32 gIndex = 0; gIndex < mGlyphs.Size(); gIndex++)
		{
			mGlyphs[gIndex]->draw(renderer);
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

	
	void Text2D::SetColor(const Vec4f& color)
	{
		//TODO this is not cool.
		for (Glyph* glyph : mGlyphs)
		{
			glyph->setColor(color);
		}
	}
}