#ifndef SH_RENDERER_2D_H
#define SH_RENDERER_2D_H

#include "Commons.h"
#include "ShQueue.h"
#include "Shader.h"
#include "Camera2D.h"

#include "ColorVec.h"
namespace Shady
{
	class Renderable2D;


	class Renderer2D
	{
	private:
		Queue<Renderable2D*> mSprites;
		Array<Renderable2D*> mLifeTimeSprites;
		Renderer2D();
		static Renderer2D* mInstance;

		void DrawSprite(Renderable2D* sprite);
		void _DrawRectangle(u32 x, u32 y, u32 width, u32 height, Vec4f color = ColorVec::Red);
		void _DrawText(const char* text, u32 size, u32 x, u32 y, Vec4f color = ColorVec::White);
	public:
		Camera2D* mCamera;

		static Renderer2D* GetInstance();
		static void DrawRectangle(u32 x, u32 y, u32 width, u32 height, Vec4f color = ColorVec::Red);
		static void DrawText(const c8* text, u32 size, u32 x, u32 y, Vec4f color = ColorVec::White);
		void Submit(Renderable2D* sprite);
		void Submit(Renderable2D* sprite, f32 lifeTime);
		void Render();
		void Update(f32 dt);
		~Renderer2D() {}
	};
}

#endif