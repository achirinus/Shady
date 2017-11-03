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
		mLifeTimeSprites.Add(sprite);
	}

	void Renderer2D::render(f32 dt)
	{
			
		while(mSprites.size())
		{
			Renderable2D* sprite = mSprites.pop();
			for(s32 index = 0; index < sprite->mShaders.Size(); index++)
			{
				sprite->mShaders[index]->Enable();
				sprite->mShaders[index]->SetUniformMat4("viewMat", mCamera->getViewMat());
				sprite->mShaders[index]->SetUniformMat4("projMat", mCamera->getProjMat());
			}
			
			sprite->draw();
			for(s32 index = 0; index < sprite->mShaders.Size(); index++)
			{
				sprite->mShaders[index]->Disable();
			}
			delete sprite;
		}
		for(u32 spriteIndex = 0; spriteIndex < mLifeTimeSprites.Size(); spriteIndex++)
		{
			Renderable2D* sprite = mLifeTimeSprites[spriteIndex];

			for(s32 index = 0; index < sprite->mShaders.Size(); index++)
			{
				sprite->mShaders[index]->Enable();
				sprite->mShaders[index]->SetUniformMat4("viewMat", mCamera->getViewMat());
				sprite->mShaders[index]->SetUniformMat4("projMat", mCamera->getProjMat());
			}
			
			sprite->draw();
			for(s32 index = 0; index < sprite->mShaders.Size(); index++)
			{
				sprite->mShaders[index]->Disable();
			}

			
			sprite->mLifeTime -= dt/1000.0f;
			if(sprite->mLifeTime <= 0.0f)
			{
				mLifeTimeSprites.Remove(spriteIndex);
				//TODO Figure out if objects should be destroyed here.
				delete sprite;
			}
		}
	}
}