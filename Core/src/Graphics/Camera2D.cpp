#include "Camera2D.h"
#include "ShadyApp.h"
namespace Shady
{
	Camera2D::Camera2D(const Vec3f& pos, u32 width, u32 height, f32 speed):
	mPos(pos), mWidth(width), mHeight(height), mViewMat(1), mProjMat(1), mSpeed{speed}, 
	mLockedInPlace(true)
	{

	}

	void Camera2D::update(f32 dt)
	{
		if(!mLockedInPlace)
		{
			Keyboard* keyboard = Keyboard::GetInstance();
			ShadyApp* app = ShadyApp::GetInstance();
			mWidth = app->mMainWindow->mClientWidth;
			mHeight = app->mMainWindow->mClientHeight;
			if(keyboard->IsPressed(KEY_DOWN))
			{
				mPos.y += mSpeed;
				
			} 
			if(keyboard->IsPressed(KEY_UP))
			{	
				mPos.y -= mSpeed;
				
			} 
			if(keyboard->IsPressed(KEY_LEFT)) 
			{
				mPos.x -= mSpeed;
			}
			if(keyboard->IsPressed(KEY_RIGHT)) 
			{
				mPos.x += mSpeed;
			}	
		}
		
		mProjMat = Matrix4f::ortho(0.0f, (f32)mWidth, 0.0f, (f32)mHeight, 10.0f, -10.0f);
		//mProjMat = Matrix4f::perspective(0, (f32)mWidth, 0, (f32)mHeight, 0.1f, 2.0f);
		
		//mProjMat = Matrix4f::perspective(0.0f, (f32)mWidth, 0.0f,(f32)mHeight, 1.0f, -30.0f);
		mViewMat = Matrix4f::translation(-mPos.x, -mPos.y, -mPos.z);
	}

	void Camera2D::lockPosition()
	{
		mLockedInPlace = true;
	}

	void Camera2D::unlockPosition()
	{
		mLockedInPlace = false;
	}

} // namespace Shady