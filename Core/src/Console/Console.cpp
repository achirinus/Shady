#include "Console.h"
#include "Renderer2D.h"
#include "Rectangle.h"
#include "Line2D.h"
#include "ShadyApp.h"
#include "InputManager.h"
#include "ShMouse.h"
#include "ShKeyboard.h"
#include "MemUtils.h"
#include "ShMath.h"
#include "ShFont.h"

#define EDIT_TEXT_HEIGHT 25
#define CONSOLE_TEXT_HEIGHT 20
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
		mCursorColor = ColorVec::Cyan;
		mMarginBoundOff = 5;
		mBeginResize = false;
		mCursor = 0;
		mTimeSinceOpen = 0.0f;
		
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
			Vec3f cursorPos = mEditTextPos + Vec3f{ 2, 3, -0.3f };
			Renderer2D::DrawRectangle(mPos, mWidth, mHeight, ColorVec::DarkGrey, true, ColorVec::Pink);
			Renderer2D::DrawEmptyRectangle(mEditTextPos, mWidth - 6, EDIT_TEXT_HEIGHT, ColorVec::WhiteGrey);
			if (mInputStr.Size())
			{
				Text2D* text = ShadyApp::GetInstance()->currentFont->GetText({ mEditTextPos.x + 3, mEditTextPos.y + 5, mEditTextPos.z }, mInputStr.CStr(), CONSOLE_TEXT_HEIGHT);
				Renderer2D::GetInstance()->Submit(text);
				cursorPos.x += (f32)text->mWidth;
				Renderer2D::DrawLine(cursorPos, cursorPos + Vec3f{0.0f , CONSOLE_TEXT_HEIGHT, 0.0f }, mCursorColor);
			}
			else
			{
				
				Renderer2D::DrawLine(cursorPos, cursorPos + Vec3f{0.0f, CONSOLE_TEXT_HEIGHT, 0.0f}, mCursorColor);
			}
			
		}
	}

	void Console::Update(f32 dt)
	{
		Mouse* mouse = Mouse::GetInstance();
		Vec2f CursorPos = mouse->GetCursorPosition();
		u32 Right = mPos.x + mWidth;
		u32 Bot = mPos.y + mHeight;
		if (mIsOpen)
		{
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
			mTimeSinceOpen += dt * 0.02;
			mCursorColor.a = Sin(mTimeSinceOpen);
		} // Is open
		
	}

	void Console::Log(const c8* str)
	{

	}

	void Console::OnKeyPressed(InputKey key, c8 c)
	{
		if (mIsOpen)
		{
			if (Keyboard::GetInstance()->IsPrintable(key))
			{
				mInputStr += c;
				mCursor++;
			}
			else if (InputKey::KEY_BACK)
			{
				mInputStr--;
				mCursor--;
				mCursor = ClampLow(mCursor, 0);
			}
		}
	}

	void Console::OnKeyReleased(InputKey key)
	{

	}
}

