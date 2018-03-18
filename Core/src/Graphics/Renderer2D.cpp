#include "Renderer2D.h"
#include "ShMouse.h"
#include "Rectangle.h"
#include "ShadyApp.h"
#include "Renderable2D.h"
#include "DebugHelper.h"
namespace Shady
{
	Renderer2D* Renderer2D::mInstance = nullptr;

	Renderer2D::Renderer2D() : mSprites{}, mLifeTimeSprites{}
	{
		ShadyApp* app = ShadyApp::GetInstance();
		mCamera = new Camera2D(Vec3f(), app->mMainWindow->mClientWidth, app->mMainWindow->mClientHeight);
	}
	Renderer2D* Renderer2D::GetInstance()
	{
		if (!mInstance) mInstance = new Renderer2D();
		return mInstance;
	}

	void Renderer2D::DrawRectangle(u32 x, u32 y, u32 width, u32 height, Vec4f color, b8 outlined, Vec4f lineCol)
	{
		Renderer2D::GetInstance()->_DrawRectangle({ (f32)x, (f32)y, 0.0f }, width, height, color, outlined, lineCol);
	}

	void Renderer2D::DrawRectangle(Vec3f pos, u32 width, u32 height, Vec4f color, b8 outlined, Vec4f lineCol)
	{
		Renderer2D::GetInstance()->_DrawRectangle(pos, width, height, color, outlined, lineCol);
	}

	void Renderer2D::_DrawRectangle(Vec3f pos, u32 width, u32 height, Vec4f color, b8 outlined, Vec4f lineCol)
	{
		Rectangle* rect = new Rectangle(pos, width, height, true, outlined, color,2, lineCol);
		Submit(rect);
	}

	void Renderer2D::DrawText(const char* text, u32 size, u32 x, u32 y, Vec4f color)
	{
		Renderer2D::GetInstance()->_DrawText(text, size, x, y, color);
	}

	void Renderer2D::DrawText(const char* text, u32 size, Vec3f pos, Vec4f color)
	{
		Renderer2D::GetInstance()->_DrawText(text, size, pos, color);
	}

	void Renderer2D::_DrawText(const c8* text, u32 size, u32 x, u32 y, Vec4f color)
	{
		Text2D* sprite = ShadyApp::GetInstance()->currentFont->GetText(Vec3f(x, y, 0.0f), text, size);
		sprite->SetColor(color);
		Submit(sprite);
	}

	void Renderer2D::_DrawText(const c8* text, u32 size, Vec3f pos, Vec4f color)
	{
		Text2D* sprite = ShadyApp::GetInstance()->currentFont->GetText(pos, text, size);
		sprite->SetColor(color);
		Submit(sprite);
	}

	void Renderer2D::Submit(Renderable2D* sprite)
	{
		mSprites.push(sprite);
	}

	void Renderer2D::Submit(Renderable2D* sprite, f32 lifeTime)
	{
		sprite->mLifeTime = lifeTime;
		if (lifeTime > 0.f)
		{
			mLifeTimeSprites.Add(sprite);
		}
	}

	void Renderer2D::Render()
	{
		AUTO_TIMED_FUNCTION();
		while(mSprites.size())
		{
			Renderable2D* sprite = mSprites.pop();
			sprite->draw(this);
			delete sprite;
		}
		for(u32 spriteIndex = 0; spriteIndex < mLifeTimeSprites.Size(); spriteIndex++)
		{
			Renderable2D* sprite = mLifeTimeSprites[spriteIndex];
			sprite->draw(this);
		}
	}

	void Renderer2D::Update(f32 dt)
	{
		AUTO_TIMED_FUNCTION()
		mCamera->update(dt);

		for (u32 spriteIndex = 0; spriteIndex < mLifeTimeSprites.Size(); spriteIndex++)
		{
			Renderable2D* sprite = mLifeTimeSprites[spriteIndex];
			sprite->mLifeTime -= dt / 1000.0f;
			if (sprite->mLifeTime <= 0.0f)
			{
				mLifeTimeSprites.Remove(spriteIndex);
				//TODO Figure out if objects should be destroyed here.
				delete sprite;
			}
		}
	}

	
}