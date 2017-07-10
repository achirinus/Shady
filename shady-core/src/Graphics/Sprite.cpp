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

	Sprite::Sprite(const Vec3f& pos, u32 width, u32 height)
	{
		mMoveAmount = {};
		mPos = pos;
		mWidth = width;
		mHeight = height;
		mScale = 1.0f;
		mPitch = 0.0f;
		mYaw = 0.0f;
		mRoll = 0.0f;

		Vec3f vertices[] = 
		{
			{pos.x, pos.y, pos.z},
			{pos.x + mWidth, pos.y, pos.z},
			{pos.x + mWidth, pos.y + mHeight, pos.z},
			{pos.x, pos.y + mHeight, pos.z}
		};

		glGenBuffers(1, &mVBO);
		glBindBuffer(GL_ARRAY_BUFFER, mVBO);
		glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Vec3f), vertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	}

	Sprite::~Sprite()
	{
		glDeleteBuffers(1, &mVBO);
	}

	void Sprite::move(const Vec3f& vec)
	{
		mMoveAmount +=vec;
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
	}

	void Sprite::draw()
	{
		glDrawArrays(GL_QUADS, 0, 4);
	}

}