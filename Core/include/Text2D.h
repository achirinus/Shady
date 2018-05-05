#ifndef SH_TEXT_2D_H
#define SH_TEXT_2D_H

#include "Renderable2D.h"
#include "ShTypes.h"
#include "GlyphData.h"
#include "Glyph.h"
#include "ShArray.h"

namespace Shady
{
	struct TextGlBuffer
	{
		Vec3f Pos;
		Vec2f TexCoord;
		Vec4f Color;
	};
	

	class Text2D : public Renderable2D
	{
	private:
		Array<Glyph*> mGlyphs;
		
		TextGlBuffer* mGlBuffer;
		Texture* mTextureAtlas;

		u32 mVAO;
		u32 mVBO;
	public:

		u32 mNumOfLines;
		Vec4f mColor;
		Text2D(Shader* shader);
		virtual void draw(Renderer2D* renderer);
		virtual ~Text2D();

		void addGlyph(Glyph* glyph);
		Glyph* operator[](u32 index) { return mGlyphs[index];}
		u32 size() { return mGlyphs.Size();}
		Vec2f GetGlyphsOffset(u32 index);
		Vec2f GetGlyphBeginPos(u32 index);
		Vec2f GetGlyphEndPos(u32 index);
		void SetColor(const Vec4f& color);
		void SetPosition(const Vec2f& newPos);
		void SetTextureAtlas(Texture* atlas);
		f32 GetHeight();
	};
}

#endif