#include "Camera3D.h"
#include "InputManager.h"

namespace Shady
{

	Camera3D::Camera3D(Vec2f dim, Vec3f pos, Vec3f rot) :
		mWidth{dim.x}, mHeight{dim.y}, mPos{pos}, mRot{rot},
		mView{1}, mProj{1}
	{
		UpdateMats();

		
		InputManager::GetInstance()->BindAction("cameraLock", BA_PRESSED, this, IM_BFUNC(Camera3D::Unlock));
		InputManager::GetInstance()->BindAction("cameraLock", BA_RELEASED, this, IM_BFUNC(Camera3D::Lock));
		InputManager::GetInstance()->BindAxis("yaw", this, IM_AFUNC(Camera3D::HandleYaw));
		InputManager::GetInstance()->BindAxis("pitch", this, IM_AFUNC(Camera3D::HandlePitch));
		InputManager::GetInstance()->BindAxis("moveX", this, IM_AFUNC(Camera3D::HandleMoveX));
		InputManager::GetInstance()->BindAxis("moveY", this, IM_AFUNC(Camera3D::HandleMoveY));

	}

	void Camera3D::UpdateMats()
	{
		mView = Matrix4f{1};
		mView = Matrix4f::translation(-mPos.x, -mPos.y, -mPos.z);
		mView.rotX(toRadians(mRot.x));
		mView.rotY(toRadians(mRot.y));

		mProj = Matrix4f::perspective(-mWidth/2.0f, mWidth/2.0f, -mHeight/2.0f, mHeight/2.0f, 1.0f, -150.0f);
	}


	void Camera3D::HandleYaw(f32 val)
	{
		if(!mLocked) mRot.y += val;
	}

	void Camera3D::HandlePitch(f32 val)
	{
		if(!mLocked) mRot.x += val;
	}

	void Camera3D::HandleMoveX(f32 val)
	{
		if(!mLocked) mPos.x += val;
	}

	void Camera3D::HandleMoveY(f32 val)
	{
		if(!mLocked) mPos.z += val;
	}

	void Camera3D::Update(f32 dt)
	{
		UpdateMats();

	}
}