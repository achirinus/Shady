#include "Renderer2D.h"
#include "ShMouse.h"

namespace Shady
{
	void Renderer2D::submit(Renderable2D* sprite)
	{
		mSprites.push(sprite);
	}

	void Renderer2D::render()
	{
			
		
		while(Renderable2D* sprite = mSprites.pop())
		{
			sprite->mShader->enable();
			sprite->mShader->setUniformMat4("viewMat", mCamera->getViewMat());
			sprite->mShader->setUniformMat4("projMat", mCamera->getProjMat());
			
			sprite->draw();
			sprite->mShader->disable();
		}
	}
}