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

	Console::Console() {}

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

	void Console::Render()
	{

	}

	void Console::Update(f32 dt)
	{

	}
}

