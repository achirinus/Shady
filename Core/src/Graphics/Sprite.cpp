#include "Sprite.h"
#include "Windows.h"
#include "ShaderManager.h"
#include "DebugHelper.h"

namespace Shady
{

	Matrix4f Sprite::getModelMat()
	{
		Matrix4f result{1};
		
		result *= Matrix4f::scale(mScale);
		
		result.rotX(mPitch);
		result.rotY(mYaw);
		result.rotZ(mRoll);
		result *= Matrix4f::translation(mMoveAmount);

		return result;
	}

	void Sprite::initGlBuffers(const Vec3f& pos, const Vec4f& color, b8 posInCenter)
	{
				
		Vec3f vertices[6];
		if(posInCenter)
		{
			vertices[0] = {pos.x - mWidth/2, pos.y - mHeight/2, pos.z}; 
			vertices[1] = {pos.x - mWidth/2, pos.y + mHeight/2, pos.z};
			vertices[2] = {pos.x + mWidth/2, pos.y - mHeight/2, pos.z};
			vertices[3] = {pos.x + mWidth/2, pos.y - mHeight/2, pos.z};
			vertices[4] = {pos.x - mWidth/2, pos.y + mHeight/2, pos.z};
			vertices[5] = {pos.x + mWidth/2, pos.y + mHeight/2, pos.z};
		} 
		else
		{
			vertices[0] = {pos.x, pos.y, pos.z};
			vertices[1] = {pos.x, pos.y + mHeight, pos.z};
			vertices[2] = {pos.x + mWidth, pos.y, pos.z};
			vertices[3] = {pos.x + mWidth, pos.y, pos.z};
			vertices[4] = {pos.x, pos.y + mHeight, pos.z};
			vertices[5] = {pos.x + mWidth, pos.y + mHeight, pos.z};
		}
		
		Vec2f texCoords[] = 
		{
			{0.0f, 0.0f},
			{0.0f, 1.0f},
			{1.0f, 0.0f},
			{1.0f, 0.0f},
			{0.0f, 1.0f},
			{1.0f, 1.0f},
		};

		Vec4f colors[] = 
		{
			mColor,
			mColor,
			mColor,
			mColor,
			mColor,
			mColor
		};

		
		glGenVertexArrays(1, &mVAO);
		glBindVertexArray(mVAO);
		glGenBuffers(NUM_BUFFERS, mVBO);
		glBindBuffer(GL_ARRAY_BUFFER, mVBO[POS_BUFFER]);
		glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(Vec3f), vertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(POS_BUFFER);
		glVertexAttribPointer(POS_BUFFER, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindBuffer(GL_ARRAY_BUFFER, mVBO[TEX_BUFFER]);
		glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(Vec2f), texCoords, GL_STATIC_DRAW);
		glEnableVertexAttribArray(TEX_BUFFER);
		glVertexAttribPointer(TEX_BUFFER, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		
		glBindBuffer(GL_ARRAY_BUFFER, mVBO[COL_BUFFER]);
		glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(Vec4f), colors, GL_STATIC_DRAW);
		glEnableVertexAttribArray(COL_BUFFER);
		glVertexAttribPointer(COL_BUFFER, 4, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);	
	}

	Sprite::Sprite(const Vec3f& pos, u32 width, u32 height, Texture* texture,
					 const Vec4f& color, b8 posInCenter, Shader* shader): 
	mTexture(texture) 
	{
		mIsTransparent = false;
		mOwnShader = false;
		mModelMat = Matrix4f(1);
		mColor = color;
		mMoveAmount = {};
		mPos = pos;
		mWidth = width;
		mHeight = height;
		mScale = 1.0f;
		mPitch = 0.0f;
		mYaw = 0.0f;
		mRoll = 0.0f;
		if(!shader)
		{
			mShader = ShaderManager::CreateShader("basic");
		}
		else
		{
			mShader = shader;
		}
		initGlBuffers(mPos, mColor, posInCenter);
		
	}

	Sprite::Sprite(const Vec3f& pos, Texture* texture, b8 posInCenter, Shader* shader):
	 mTexture(texture)
	{
		mIsTransparent = false;
		mOwnShader = false;
		mModelMat = Matrix4f(1);
		mColor = Vec4f(1.0f, 1.0f, 1.0f, 1.0f);
		mMoveAmount = {};
		mPos = pos;
		mWidth = texture->getWidth();
		mHeight = texture->getHeight();
		mScale = 1.0f;
		mPitch = 0.0f;
		mYaw = 0.0f;
		mRoll = 0.0f;
		
		if(!shader)
		{
			mShader = new Shader("basic", SH_FRAGMENT_SHADER | SH_VERTEX_SHADER);
			mOwnShader = true;
		}
		else
		{
			mShader = shader;
			mOwnShader = false;
		}
		initGlBuffers(mPos, mColor, posInCenter);
	}

	Sprite::~Sprite()
	{
		glDeleteBuffers(NUM_BUFFERS, mVBO);
		glDeleteVertexArrays(1, &mVAO);
		
	}

	void Sprite::move(const Vec3f& vec)
	{
		mMoveAmount +=vec;
	}

	void Sprite::update()
	{
		
		Keyboard* keyboard = Keyboard::GetInstance();
		if(keyboard->IsPressed(KEY_Z))
		{
			scale(-0.02f);
		}
		if(keyboard->IsPressed(KEY_C))
		{
			scale( 0.02f);
		}
		if(keyboard->IsPressed(KEY_A))
		{
			move({-1.0f, 0.0f, 0.0f});
		}
		if(keyboard->IsPressed(KEY_D))
		{
			move({1.0f, 0.0f, 0.0f});
			//rotate(0.0f, 0.0f, 0.01f);
		}
		if(keyboard->IsPressed(KEY_W))
		{
			move({0.0f, -1.0f, 0.0f});
		}
		if(keyboard->IsPressed(KEY_S))
		{
			move({0.0f, 1.0f, 0.0f});
		}
		if(keyboard->IsPressed(KEY_Q))
		{
			move({0.0f, 0.0f, -0.1f });
		}
		if(keyboard->IsPressed(KEY_E))
		{
			move({0.0f, 0.0f, 0.1f });
		}
		if(keyboard->IsPressed(KEY_K))
		{
			DEBUG_OUT_INFO("Pos: [%f  %f  %f  %f]", mPos.x, mPos.y, mPos.z, mPos.w);
			DEBUG_OUT_INFO("Move by: [%f  %f  %f  %f]", mMoveAmount.x, mMoveAmount.y,
															 mMoveAmount.z, mMoveAmount.w);
			DEBUG_OUT_INFO("Scale: %f", mScale);
		}
	}

	void Sprite::SetTransparency(b8 transparent)
	{
		mIsTransparent = transparent;
	}

	void Sprite::setColor(const Vec4f& color)
	{
		mColor = color;
		Vec4f colors[] = 
		{
			mColor,
			mColor,
			mColor,
			mColor,
			mColor,
			mColor
		};
		glBindVertexArray(mVAO);
		glBindBuffer(GL_ARRAY_BUFFER, mVBO[COL_BUFFER]);
		glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(Vec4f), colors, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void Sprite::setTexture(Texture* tex)
	{
		mTexture = tex;
	}

	
	void Sprite::rotate(f32 pitch, f32 yaw, f32 roll)
	{
		mPitch += pitch;
		mYaw += yaw;
		mRoll += roll;
	}

	void Sprite::scale(f32 scale)
	{
		mScale = scale;
		mScale = ClampToZero(mScale);
	}

	void Sprite::draw(Renderer2D* renderer)
	{
		AUTO_TIMED_FUNCTION();
		if(mIsTransparent) glDepthMask(false);

		if(mTexture) mTexture->bind(0);
		mShader->Enable();
		mShader->SetUniform1i("hasTexture", hasTexture());
		mShader->SetUniformMat4("modelMat", getModelMat());
		mShader->SetUniformMat4("totalMovedMat", Matrix4f::translation(getCurrentPos()));
		mShader->SetUniformMat4("viewMat", renderer->mCamera->getViewMat());
		mShader->SetUniformMat4("projMat", renderer->mCamera->getProjMat());
		
		glBindVertexArray(mVAO);
				
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);

		if (mIsTransparent) glDepthMask(true);
		if(mTexture) mTexture->unbind(0);
		mShader->Disable();
	}

}