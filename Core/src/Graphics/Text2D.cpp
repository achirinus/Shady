#include "Text2D.h"
#include "ShAssert.h"
#include "DebugHelper.h"

namespace Shady
{
#define MAX_TEXT_GL_BUFFER_SIZE 2048 * 24
	Text2D::Text2D(Shader* shader): mGlBuffer{0}
	{
		mShader = shader;
		mWidth = 0;
		mHeight = 0;
		
		glGenVertexArrays(1, &mVAO);
		glBindVertexArray(mVAO);
		glGenBuffers(1, &mVBO);
		glBindBuffer(GL_ARRAY_BUFFER, mVBO);
		glBufferData(GL_ARRAY_BUFFER, MAX_TEXT_GL_BUFFER_SIZE, 0 , GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(POS_BUFFER);
		glEnableVertexAttribArray(TEX_BUFFER);
		glEnableVertexAttribArray(COL_BUFFER);

		void* posOffset = (void*)0;
		void* texOffset = (void*)(3 * sizeof(f32));
		void* colOffset = (void*)((3 * sizeof(f32)) + (2 * sizeof(f32)));

		glVertexAttribPointer(POS_BUFFER, 3, GL_FLOAT, GL_FALSE, sizeof(TextGlBuffer), posOffset);
		glVertexAttribPointer(TEX_BUFFER, 2, GL_FLOAT, GL_FALSE, sizeof(TextGlBuffer), texOffset);
		glVertexAttribPointer(COL_BUFFER, 4, GL_FLOAT, GL_FALSE, sizeof(TextGlBuffer), colOffset);

		
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	void Text2D::draw(Renderer2D* renderer)
	{
		AUTO_TIMED_FUNCTION();
		glBindVertexArray(mVAO);
		glBindBuffer(GL_ARRAY_BUFFER, mVBO);
		mGlBuffer = (TextGlBuffer*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		for(u32 gIndex = 0; gIndex < mGlyphs.Size(); gIndex++)
		{
			Glyph* glyph = mGlyphs[gIndex];
			Vec3f pos = glyph->mPos;

			Vec3f vertices[6];

			vertices[0] = { pos.x, pos.y, pos.z };
			vertices[1] = { pos.x, pos.y + glyph->mData.mHeight, pos.z };
			vertices[2] = { pos.x + glyph->mData.mWidth, pos.y, pos.z };
			vertices[3] = { pos.x + glyph->mData.mWidth, pos.y, pos.z };
			vertices[4] = { pos.x, pos.y + glyph->mData.mHeight, pos.z };
			vertices[5] = { pos.x + glyph->mData.mWidth, pos.y + glyph->mData.mHeight, pos.z };

			Vec2f TopLeft = glyph->mData.mAtlasCoordsTopLeft;
			Vec2f BotRight = glyph->mData.mAtlasCoordsBotRight;

			Vec2f coords[6] =
			{
				{ TopLeft.x, TopLeft.y},
				{ TopLeft.x, BotRight.y },
				{ BotRight.x, TopLeft.y },
				{ BotRight.x, TopLeft.y },
				{ TopLeft.x, BotRight.y },
				{ BotRight.x, BotRight.y }
			};
			
			for (u32 i = 0; i < 6; ++i)
			{
				mGlBuffer->Pos = vertices[i];
				mGlBuffer->TexCoord = coords[i];
				mGlBuffer->Color = mColor;
				mGlBuffer++;
			}
		}
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDepthMask(false);

		if (mTextureAtlas) mTextureAtlas->bind(0);
		mShader->Enable();
		
		mShader->SetUniformMat4("viewMat", renderer->mCamera->getViewMat());
		mShader->SetUniformMat4("projMat", renderer->mCamera->getProjMat());

		glDrawArrays(GL_TRIANGLES, 0, mGlyphs.Size() * 6);

		glBindVertexArray(0);
		
		glDepthMask(true);
		if (mTextureAtlas) mTextureAtlas->unbind(0);
		mShader->Disable();
	}

	void Text2D::addGlyph(Glyph* glyph)
	{
		mWidth += glyph->mData.mWidth;
		
		mGlyphs.Add(glyph);
	}

	Text2D::~Text2D()
	{
		for(u32 gIndex = 0; gIndex < mGlyphs.Size(); gIndex++)
		{
			delete mGlyphs[gIndex];
		}
		glDeleteBuffers(1, &mVBO);
		glDeleteVertexArrays(1, &mVAO);
	}

	
	void Text2D::SetColor(const Vec4f& color)
	{
		mColor = color;
	}

	void Text2D::SetPosition(const Vec2f& newPos)
	{
		for (Glyph* glyph : mGlyphs)
		{
			/*For now I have to do this because i am not keeping the glyphs is text space 
			 *Change this as soon as I use a model matrix to change the space and keep glyph mPos to text space
			 **/
			glyph->mPos -= mPos;
			glyph->mPos += newPos;
		}
		mPos = newPos;
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
		Vec2f result = {};
		Glyph* temp = nullptr;
		if (index >= mGlyphs.Size())
		{
			temp = mGlyphs[mGlyphs.Size() - 1];
		}
		else
		{
			temp = mGlyphs[index];
		}

		if (temp)
		{
			result = temp->mPos.xy;
			if (temp->mData.mChar == ' ') //Special case for space for now
			{
				result.x += temp->mData.mAdvanceWidth;
			}
			else
			{
				result.x += temp->mData.mWidth;
			}
		}
		return result;
	}

	f32 Text2D::GetHeight()
	{
		f32 result = 0.f;
		u32 ElCount = mGlyphs.Size();
		if (ElCount)
		{
			result = mGlyphs[ElCount - 1]->mPos.y + mGlyphs[ElCount - 1]->mData.mHeight;
			result -= mPos.y;
		}
		else
		{
			result = 0.f;
		}
		return result;
	}

	void Text2D::SetTextureAtlas(Texture* atlas)
	{
		mTextureAtlas = atlas;
	}
}