#include "Camera3D.h"
#include "InputManager.h"

namespace Shady
{

	Camera3D::Camera3D(Vec2f dim, Vec3f pos, Vec3f rot) :
		mWidth{dim.x}, mHeight{dim.y}, mPos{pos}, mRot{rot},
		mView{1}, mProj{1}
	{
		updateMats();

		
		InputManager::getInstance()->bindAction("cameraLock", BA_PRESSED, this, IM_BFUNC(Camera3D::unlock));
		InputManager::getInstance()->bindAction("cameraLock", BA_RELEASED, this, IM_BFUNC(Camera3D::lock));
		InputManager::getInstance()->bindAxis("yaw", this, IM_AFUNC(Camera3D::handleYaw));
		InputManager::getInstance()->bindAxis("pitch", this, IM_AFUNC(Camera3D::handlePitch));
		InputManager::getInstance()->bindAxis("moveX", this, IM_AFUNC(Camera3D::handleMoveX));
		InputManager::getInstance()->bindAxis("moveY", this, IM_AFUNC(Camera3D::handleMoveY));

	}

	void Camera3D::updateMats()
	{
		mView = Matrix4f{1};
		mView = Matrix4f::translation(-mPos.x, -mPos.y, -mPos.z);
		mView.rotX(toRadians(mRot.x));
		mView.rotY(toRadians(mRot.y));

		mProj = Matrix4f::perspective(-mWidth/2.0f, mWidth/2.0f, -mHeight/2.0f, mHeight/2.0f, 1.0f, -150.0f);
	}


	void Camera3D::handleYaw(f32 val)
	{
		if(!mLocked) mRot.y += val;
	}

	void Camera3D::handlePitch(f32 val)
	{
		if(!mLocked) mRot.x += val;
	}

	void Camera3D::handleMoveX(f32 val)
	{
		if(!mLocked) mPos.x += val;
	}

	void Camera3D::handleMoveY(f32 val)
	{
		if(!mLocked) mPos.z += val;
	}

	void Camera3D::update(f32 dt)
	{
		updateMats();

	}
}