#include "Glyph.h"

namespace Shady
{
	Glyph::Glyph(const Vec3f& pos, Texture* texture, Shader* shader):
	 Sprite(pos, texture, false, shader)
	{

	}

	void Glyph::draw()
	{
		mTexture->bind(0);
		
		mShader->setUniformMat4("modelMat", getModelMat());
		mShader->setUniformMat4("totalMovedMat", Matrix4f::translation(getCurrentPos()));
			
		glBindVertexArray(mVAO);
		glDrawArrays(GL_QUADS, 0, 4);
		glBindVertexArray(0);
		mTexture->unbind(0);
	}

	Glyph::~Glyph()
	{
		glDeleteBuffers(NUM_BUFFERS, mVBO);
		glDeleteVertexArrays(1, &mVAO);
	}
}