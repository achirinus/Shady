#ifndef SH_CAMERA_2D_H
#define SH_CAMERA_2D_H

#include "Commons.h"
#include "Matrix4f.h"
#include "Vec3.h"
#include "ShKeyboard.h"


namespace Shady
{
	class Camera2D
	{
	private:
		Matrix4f mViewMat;
		Matrix4f mProjMat;
		Vec3f mPos;
		u32 mWidth;
		u32 mHeight;
		f32 mSpeed;
		b8 mLockedInPlace;
	public:
		Camera2D() = default;
		Camera2D(const Vec3f& pos, u32 mWidth, u32 mHeight, f32 speed = 0.2f);
		~Camera2D() {}
		Matrix4f getViewMat() { return mViewMat;}
		Matrix4f getProjMat() {return mProjMat;}
		Matrix4f getProjViewMat() { return mProjMat * mViewMat;}
		void update(f32 dt);
		void lockPosition();
		void unlockPosition();
	};
}

#endif