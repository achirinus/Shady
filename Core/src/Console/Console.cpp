#include "Console.h"
#include "Renderer2D.h"
#include "Rectangle.h"
#include "Line2D.h"
#include "ShadyApp.h"
#include "InputManager.h"
#include "ShMouse.h"
#include "ShKeyboard.h"
#include "MemUtils.h"

#define EDIT_TEXT_HEIGHT 30

namespace Shady
{
	Console* Console::mInstance = nullptr;
	Console* Console::GetInstance()
	{
		if (!mInstance) mInstance = new Console();
		return mInstance;
	}

	Console::Console() :mIsOpen{ false }, mWidth{ 700 }, mHeight{500} 
	{
		mPos = { 0.0f, 0.0f, -1.0f }; //World Space
		mEditTextPos = { 2.0f, (f32)(mHeight - (EDIT_TEXT_HEIGHT + 4)), -0.2f }; // This is in console space
		mEditTextPos += mPos;
		mMarginBoundOff = 5;
		mBeginResize = false;

		
		ZeroMem(mBuffer, MegaBytes(1));
	}

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
		FlipFlop(Console::GetInstance()->mIsOpen);
	}

	void Console::Init()
	{
		InputManager::GetInstance()->BindAction("ToggleConsole", ButtonAction::BA_RELEASED, &Console::Toggle);
		Keyboard::GetInstance()->Register(this);
	}

	void Console::Render()
	{
		if (mIsOpen)
		{
			Renderer2D::DrawRectangle(mPos, mWidth, mHeight, ColorVec::DarkGrey, true, ColorVec::Pink);
			Renderer2D::DrawEmptyRectangle(mEditTextPos, mWidth - 6, EDIT_TEXT_HEIGHT, ColorVec::WhiteGrey);
			if (mInputStr.Size())
			{
				Renderer2D::DrawText(mInputStr.CStr(), 25, { mEditTextPos.x + 3, mEditTextPos.y + 3, mEditTextPos.z }, ColorVec::White);
			}
			
		}
	}

	void Console::Update(f32 dt)
	{
		Mouse* mouse = Mouse::GetInstance();
		Vec2f CursorPos = mouse->GetCursorPosition();
		u32 Right = mPos.x + mWidth;
		u32 Bot = mPos.y + mHeight;
		
		//Check If cursor in corner
		if (!mBeginResize)
		{
			if ((CursorPos.x < Right) && (CursorPos.x > (Right - mMarginBoundOff)) &&
				(CursorPos.y < Bot) && (CursorPos.y) > (Bot - mMarginBoundOff))
			{
				if (mouse->GetState(MOUSE_LEFT))
				{
					mBeginResize = true;
				}
			}
		}
		else
		{
			if (mouse->GetState(MOUSE_LEFT))
			{
				Vec2f newSize = mouse->GetCursorPosition();
				mWidth = newSize.x;
				mHeight = newSize.y;
				mEditTextPos.y = mHeight - (EDIT_TEXT_HEIGHT + 2);
			}
			else
			{
				mBeginResize = false;
			}
		}

		//For now i dont' care about focus, just get input for keyboard 
		//if console is opened
		
	}

	void Console::Log(const c8* str)
	{

	}

	void Console::OnKeyPressed(InputKey key)
	{
		if (mIsOpen)
		{
			if (Keyboard::GetInstance()->IsPrintable(key))
			{
				mInputStr += c8(key);
			}
		}
	}

	void Console::OnKeyReleased(InputKey key)
	{

	}
}

