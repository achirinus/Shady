#ifndef SH_CAMERA_3D_H
#define SH_CAMERA_3D_H

#include "Vec3.h"
#include "Matrix4f.h"
#include "Vec2.h"
#include "ShMath.h"
#include "ShObject.h"

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

		void UpdateMats();

	public:
		Camera3D() = default;
		Camera3D(Vec2f dim, Vec3f pos = {}, Vec3f rot = {});
		~Camera3D() = default;
		
		void Update(f32 dt);
		
		Matrix4f GetViewMat() { return mView;}
		Matrix4f GetProjMat() { return mProj;}

		void Lock(){ mLocked = true;}
		void Unlock() {mLocked = false;}
		void HandleYaw(f32 val);
		void HandlePitch(f32 val);
		void HandleMoveX(f32 val);
		void HandleMoveY(f32 val);



	};
}

#endif