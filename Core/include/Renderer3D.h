#ifndef SH_RENDERER_3D_H
#define	SH_RENDERER_3D_H

#include "Camera3D.h"
#include "ShQueue.h"
#include "Renderable3D.h"

namespace Shady
{

	class Renderer3D
	{
		Camera3D* mCam;
		Camera3D* mLastCam;

		Queue<Renderable3D*> mRenderQueue;
	public:
		Renderer3D(Camera3D* cam);
		~Renderer3D() = default;
		
		b8 changeCamera(Camera3D* cam = nullptr);
		void submit(Renderable3D* rend);
		void render(f32 dt);

	};
}

#endif