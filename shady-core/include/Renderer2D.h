#ifndef SH_RENDERER_2D_H
#define SH_RENDERER_2D_H

#include "Commons.h"
#include "ShQueue.h"
#include "Shader.h"
#include "Camera2D.h"
#include "Renderable2D.h"
namespace Shady
{
	class Renderer2D
	{
	private:
		Queue<Renderable2D*> mSprites;
		Array<Renderable2D*> mLifeTimeSprites;
		Camera2D* mCamera;
		
	public:
		Renderer2D(Camera2D* camera): mCamera(camera), mSprites(){}
		
		void submit(Renderable2D* sprite);
		void submit(Renderable2D* sprite, f32 lifeTime);
		void render(f32 dt);
		~Renderer2D() {}
	};
}

#endif