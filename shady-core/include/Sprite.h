#ifndef SH_SPRITE_H
#define SH_SPRITE_H

#include "Vec3.h"
#include "Matrix4f.h"
#include "Commons.h"
#include "String.h"

namespace Shady
{
	class Sprite
	{
	public:
		Vec3f mPos;
		Vec3f mMoveAmount;
		u32 mWidth;
		u32 mHeight;
		f32 mScale;
		f32 mPitch;
		f32 mYaw;
		f32 mRoll;
		GLuint mVBO;

		Sprite():mScale(1.0f), mPitch(0.0f), mYaw(0.0f), mRoll(1.0f), mPos() {}
		Sprite(const Vec3f& pos, u32 width, u32 height);
		~Sprite();

		Matrix4f getModelMat();
		void move(const Vec3f& vec);
		void rotate(f32 pitch, f32 yaw, f32 roll);
		void scale(f32 scale);
		void draw();
	};
}

#endif