#include "Sprite.h"

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

	Sprite::Sprite(const Vec3f& pos, u32 width, u32 height, Texture* texture, const Vec4f& color): 
	mTexture(texture),
	mModelMat(1)
	{
		mColor = color;
		mMoveAmount = {};
		mPos = pos;
		mWidth = width;
		mHeight = height;
		mScale = 1.0f;
		mPitch = 0.0f;
		mYaw = 0.0f;
		mRoll = 0.0f;

		/*
		Vec3f vertices[] = 
		{
			{pos.x, pos.y, pos.z},
			{pos.x, pos.y + mHeight, pos.z},
			{pos.x + mWidth, pos.y + mHeight, pos.z},
			{pos.x + mWidth, pos.y, pos.z}
		};
		*/
		
		// Vertices that set the position in the center of the sprite
		Vec3f vertices[] = 
		{
			{pos.x - width/2, pos.y - height/2, pos.z},
			{pos.x - width/2, pos.y + height/2, pos.z},
			{pos.x + width/2, pos.y + height/2, pos.z},
			{pos.x + width/2, pos.y - height/2, pos.z}
		};
		
		Vec2f texCoords[] = 
		{
			{0.0f, 0.0f},
			{0.0f, 1.0f},
			{1.0f, 1.0f},
			{1.0f, 0.0f}
		};

		Vec4f colors[] = 
		{
			mColor,
			mColor,
			mColor,
			mColor
		};

		
		glGenVertexArrays(1, &mVAO);
		glBindVertexArray(mVAO);
		glGenBuffers(NUM_BUFFERS, mVBO);
		glBindBuffer(GL_ARRAY_BUFFER, mVBO[POS_BUFFER]);
		glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Vec3f), vertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(POS_BUFFER);
		glVertexAttribPointer(POS_BUFFER, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindBuffer(GL_ARRAY_BUFFER, mVBO[TEX_BUFFER]);
		glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Vec2f), texCoords, GL_STATIC_DRAW);
		glEnableVertexAttribArray(TEX_BUFFER);
		glVertexAttribPointer(TEX_BUFFER, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		
		glBindBuffer(GL_ARRAY_BUFFER, mVBO[COL_BUFFER]);
		glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Vec4f), colors, GL_STATIC_DRAW);
		glEnableVertexAttribArray(COL_BUFFER);
		glVertexAttribPointer(COL_BUFFER, 4, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	Sprite::~Sprite()
	{
		glDeleteBuffers(2, mVBO);
		glDeleteVertexArrays(1, &mVAO);
		
	}

	void Sprite::move(const Vec3f& vec)
	{
		mMoveAmount +=vec;
	}

	void Sprite::update()
	{
		
		Keyboard* keyboard = Keyboard::getInstance();
		if(keyboard->isPressed(KEY_Z))
		{
			scale(-0.02f);
		}
		if(keyboard->isPressed(KEY_C))
		{
			scale( 0.02f);
		}
		if(keyboard->isPressed(KEY_A))
		{
			move({-1.0f, 0.0f, 0.0f});
		}
		if(keyboard->isPressed(KEY_D))
		{
			move({1.0f, 0.0f, 0.0f});
			//rotate(0.0f, 0.0f, 0.01f);
		}
		if(keyboard->isPressed(KEY_W))
		{
			move({0.0f, -1.0f, 0.0f});
		}
		if(keyboard->isPressed(KEY_S))
		{
			move({0.0f, 1.0f, 0.0f});
		}
		if(keyboard->isPressed(KEY_Q))
		{
			move({0.0f, 0.0f, -0.1f });
		}
		if(keyboard->isPressed(KEY_E))
		{
			move({0.0f, 0.0f, 0.1f });
		}
		if(keyboard->isPressed(KEY_K))
		{
			DEBUG_OUT_INFO("Pos: [%f  %f  %f  %f]", mPos.x, mPos.y, mPos.z, mPos.w);
			DEBUG_OUT_INFO("Move by: [%f  %f  %f  %f]", mMoveAmount.x, mMoveAmount.y,
															 mMoveAmount.z, mMoveAmount.w);
			DEBUG_OUT_INFO("Scale: %f", mScale);
		}
	}

	void Sprite::setColor(const Vec4f& color)
	{
		mColor = color;
		Vec4f colors[] = 
		{
			mColor,
			mColor,
			mColor,
			mColor
		};
		glBindVertexArray(mVAO);
		glBindBuffer(GL_ARRAY_BUFFER, mVBO[COL_BUFFER]);
		glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Vec4f), colors, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	
	void Sprite::rotate(f32 pitch, f32 yaw, f32 roll)
	{
		mPitch += pitch;
		mYaw += yaw;
		mRoll += roll;
	}

	void Sprite::scale(f32 scale)
	{
		mScale += scale;
		mScale = clampToZero(mScale);
	}

	void Sprite::draw()
	{
		if(mTexture) mTexture->bind(0);
		glBindVertexArray(mVAO);
		glDrawArrays(GL_QUADS, 0, 4);
		glBindVertexArray(0);
		if(mTexture) mTexture->unbind(0);
	}

}