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
		Vec3f mPos;
		u32 mWidth;
		u32 mHeight;
		f32 mSpeed;
	public:
		Camera2D() = default;
		Camera2D(const Vec3f& pos, u32 mWidth, u32 mHeight, f32 speed = 0.2f);
		~Camera2D() {}
		Matrix4f getViewMat() { return mViewMat;}
		void update();
	};
}

#endif