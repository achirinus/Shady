#include "Text2D.h"
#include "ShAssert.h"

namespace Shady
{

	Text2D::Text2D(Shader* shader)
	{
		mShader = shader;
		mWidth = 0;
		mHeight = 0;
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
		mWidth += glyph->mWidth;
		
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
	Vec2f Text2D::GetGlyphsOffset(u32 index)
	{
		SH_ASSERT(index >= 0);

		Glyph* temp = mGlyphs[index];
		Vec2f result = { temp->mPos.x - mPos.x, temp->mPos.y - mPos.y };

		return result;
	}

	Vec2f Text2D::GetGlyphBeginPos(u32 index)
	{
		SH_ASSERT(index >= 0);
		Vec2f result;
		if (index >= mGlyphs.Size())
		{
			result = mGlyphs[mGlyphs.Size() - 1]->mPos.xy;
		}
		else
		{
			result = mGlyphs[index]->mPos.xy;
		}
		
		return result;
	}

	Vec2f Text2D::GetGlyphEndPos(u32 index)
	{
		SH_ASSERT(index >= 0);
		Vec2f result;
		
		if (index >= mGlyphs.Size())
		{
			result = mGlyphs[mGlyphs.Size() - 1]->mPos.xy;
			result.x += mGlyphs[mGlyphs.Size() - 1]->mWidth;
		}
		else
		{
			result = mGlyphs[index]->mPos.xy;
			result.x += mGlyphs[index]->mWidth;
		}
		
		return result;
	}
}