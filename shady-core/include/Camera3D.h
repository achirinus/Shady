#ifndef SH_CAMERA_3D_H
#define SH_CAMERA_3D_H

#include "Vec3.h"
#include "Matrix4f.h"
#include "Vec2.h"
#include "ShMath.h"

namespace Shady
{

	class Camera3D : public Object
	{
		Vec3f mPos;
		Vec3f mRot; 
		f32 mWidth;
		f32 mHeight;
		Matrix4f mView;
		Matrix4f mProj;
		b8 mLocked;

		void updateMats();

	public:
		Camera3D() = default;
		Camera3D(Vec2f dim, Vec3f pos = {}, Vec3f rot = {});
		~Camera3D() = default;
		
		void update(f32 dt);
		
		Matrix4f getViewMat() { return mView;}
		Matrix4f getProjMat() { return mProj;}

		void lock(){ mLocked = true;}
		void unlock() {mLocked = false;}
		void handleYaw(f32 val);
		void handlePitch(f32 val);
		void handleMoveX(f32 val);
		void handleMoveY(f32 val);



	};
}

#endif