#ifndef SH_RENDERER_2D_H
#define SH_RENDERER_2D_H

#include "Commons.h"
#include "ShQueue.h"
#include "Shader.h"
#include "Camera2D.h"
namespace Shady
{
	class Renderer2D
	{
	private:
		Queue<Sprite> mSprites;
		Shader mShader;
		Camera2D* mCamera;
	public:
		Renderer2D(Camera2D* camera): mShader("basic", SH_VERTEX_SHADER | SH_FRAGMENT_SHADER),
									 mCamera(camera), mSprites(){}
		
		void submit(Sprite* sprite);
		void render();
		~Renderer2D() {}
	};
}

#endif