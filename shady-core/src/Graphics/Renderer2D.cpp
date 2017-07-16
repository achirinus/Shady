#include "Renderer2D.h"
#include "ShMouse.h"

namespace Shady
{
	void Renderer2D::submit(Sprite* sprite)
	{
		mSprites.push(sprite);
	}

	void Renderer2D::render()
	{
		mShader.enable();
		Mouse* mouse = Mouse::getInstance();
		mShader.setUniform2f("mousePos", Vec2f((f32)mouse->xPos, (f32)mouse->yPos));	
		mShader.setUniformMat4("viewMat", mCamera->getViewMat());
		mShader.setUniformMat4("projMat", mCamera->getProjMat());
		while(Sprite* sprite = mSprites.pop())
		{
			mShader.setUniform1i("hasTexture", sprite->hasTexture());
			mShader.setUniformMat4("modelMat", sprite->getModelMat());
			mShader.setUniformMat4("totalMovedMat", Matrix4f::translation(sprite->getCurrentPos()));
			Vec4f vertices[]
			{
				{sprite->mPos.x, sprite->mPos.y, sprite->mPos.z, 1.0f},
				{sprite->mPos.x + sprite->mWidth, sprite->mPos.y, sprite->mPos.z, 1.0f},
				{sprite->mPos.x + sprite->mWidth, sprite->mPos.y + sprite->mHeight, sprite->mPos.z, 1.0f},
				{sprite->mPos.x, sprite->mPos.y + sprite->mHeight, sprite->mPos.z, 1.0f}
			};
			/*
			for(int i = 0; i < 4; i++)
			{
				Matrix4f camMat = mCamera->getViewMat();
				Matrix4f modelMat = sprite->getModelMat(); 
				Matrix4f bothMats = camMat * modelMat;
				Vec4f result = bothMats * vertices[i];
				DEBUG_OUT_INFO("%f, %f, %f, %f\n", result.x, result.y, result.z, result.w);
			}
			*/
			sprite->draw();
		}
		mShader.disable();
	}
}