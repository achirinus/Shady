#include "Console.h"
#include "Renderer2D.h"
#include "Rectangle.h"
#include "Line2D.h"
#include "ShadyApp.h"
#include "InputManager.h"

namespace Shady
{
	Console* Console::mInstance = nullptr;
	Console* Console::GetInstance()
	{
		if (!mInstance) mInstance = new Console();
		return mInstance;
	}

	Console::Console() :mIsOpen{ false }, mWidth{ 700 }, mHeight{500} {}

	void Console::Open()
	{
		mIsOpen = true;
	}

	void Console::Close()
	{
		mIsOpen = false;
	}

	void Console::Toggle()
	{
		FlipFlop(mIsOpen);
	}

	void Console::Init()
	{
		InputManager::GetInstance()->BindAction("ToggleConsole", ButtonAction::BA_RELEASED, this, IM_BFUNC(Console::Toggle));
	}

	void Console::Render()
	{
		if (mIsOpen)
		{
			Renderer2D::DrawRectangle({0.0f, 0.0f, 2.0f}, mWidth, mHeight, ColorVec::DarkGrey, true, ColorVec::Black);
		}
	}

	void Console::Update(f32 dt)
	{

	}
}

