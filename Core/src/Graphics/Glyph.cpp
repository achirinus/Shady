#include "Glyph.h"

namespace Shady
{

	Glyph::Glyph(const Vec3f& pos, GlyphData data)
	{
		mPos = pos;
		mData = data;
	}


#if 0
	void Glyph::draw()
	{
		mTexture->bind(0);
		
		mShader->setUniformMat4("modelMat", getModelMat());
		mShader->setUniformMat4("totalMovedMat", Matrix4f::translation(getCurrentPos()));
			
		glBindVertexArray(mVAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
		mTexture->unbind(0);
	}
#endif
	Glyph::~Glyph()
	{
		
	}
}