#include "Camera2D.h"

namespace Shady
{
	Camera2D::Camera2D(const Vec3f& pos, u32 width, u32 height, f32 speed):
	mPos(pos), mWidth(width), mHeight(height), mViewMat(1), mSpeed(speed)
	{

	}

	void Camera2D::update()
	{
		static float zz = 0.0f;
		Keyboard* keyboard = Keyboard::getInstance();

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
			mPos.x += mSpeed;
		}
		if(keyboard->isPressed(KEY_RIGHT)) 
		{
			mPos.x -= mSpeed;
		}
		
		mViewMat = Matrix4f::ortho(0.0f, (f32)mWidth, 0.0f, (f32)mHeight, -1.0f, 1.0f);
		//mViewMat = Matrix4f::perspectiveFov(70.0f, 16.0f/10.0f, zz, 50.0f);
		mViewMat *= Matrix4f::translation(-mPos.x, -mPos.y, -mPos.z);
	}
}