#include "Camera2D.h"
#include "ShadyApp.h"
namespace Shady
{
	Camera2D::Camera2D(const Vec3f& pos, u32 width, u32 height, f32 speed):
	mPos(pos), mWidth(width), mHeight(height), mViewMat(1), mProjMat(1), mSpeed(speed)
	{

	}

	void Camera2D::update()
	{
		Keyboard* keyboard = Keyboard::getInstance();
		ShadyApp* app = ShadyApp::getInstance();
		mWidth = app->mMainWindow->mWidth;
		mHeight = app->mMainWindow->mHeight;
		if(keyboard->isPressed(KEY_DOWN))
		{
			mPos.y += mSpeed;
			
		} 
		if(keyboard->isPressed(KEY_UP))
		{	
			mPos.y -= mSpeed;
			
		} 
		if(keyboard->isPressed(KEY_LEFT)) 
		{
			mPos.x -= mSpeed;
		}
		if(keyboard->isPressed(KEY_RIGHT)) 
		{
			mPos.x += mSpeed;
		}
		

		mProjMat = Matrix4f::ortho(0.0f, (f32)mWidth, 0.0f, (f32)mHeight, -1.0f, 1.0f);
		//mProjMat = Matrix4f::perspective(-(f32)mWidth/2, (f32)mWidth/2, -(f32)mHeight/2,
		//								 (f32)mHeight/2, 1.0f, -30.0f);
		//mProjMat = Matrix4f::perspective(0.0f, (f32)mWidth, 0.0f,(f32)mHeight, 1.0f, -30.0f);
		mViewMat = Matrix4f::translation(-mPos.x, -mPos.y, -mPos.z);
	}
}