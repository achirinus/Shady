#include "Renderer2D.h"
#include "ShMouse.h"

namespace Shady
{
	void Renderer2D::submit(Renderable2D* sprite)
	{
		mSprites.push(sprite);
	}

	void Renderer2D::submit(Renderable2D* sprite, f32 lifeTime)
	{
		sprite->mLifeTime = lifeTime;
		mLifeTimeSprites.add(sprite);
	}

	void Renderer2D::render(f32 dt)
	{
			
		while(Renderable2D* sprite = mSprites.pop())
		{
			sprite->mShader->enable();
			sprite->mShader->setUniformMat4("viewMat", mCamera->getViewMat());
			sprite->mShader->setUniformMat4("projMat", mCamera->getProjMat());
			
			sprite->draw();
			sprite->mShader->disable();
		}
		for(u32 spriteIndex = 0; spriteIndex < mLifeTimeSprites.size(); spriteIndex++)
		{
			Renderable2D* sprite = mLifeTimeSprites[spriteIndex];

			sprite->mShader->enable();
			sprite->mShader->setUniformMat4("viewMat", mCamera->getViewMat());
			sprite->mShader->setUniformMat4("projMat", mCamera->getProjMat());
			
			sprite->draw();
			sprite->mShader->disable();
			
			sprite->mLifeTime -= dt/1000.0f;
			if(sprite->mLifeTime <= 0.0f)
			{
				mLifeTimeSprites.remove(spriteIndex);
				//TODO Figure out if objects should be destroyed here.
				delete sprite;
			}
		}
	}
}