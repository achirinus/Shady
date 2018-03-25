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


#define EDIT_TEXT_HEIGHT 25
#define CONSOLE_TEXT_HEIGHT 20
#define CONSOLE_LINE_SPACING 2
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
		mFont = ShadyApp::GetInstance()->currentFont;
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
				Text2D* text = mFont->GetText({ mEditTextPos.x + 3, mEditTextPos.y + 5, mEditTextPos.z }, mInputStr.CStr(), CONSOLE_TEXT_HEIGHT);
				Renderer2D::GetInstance()->Submit(text);
				if (mCursor > 0)
				{
					cursorPos.x = text->GetGlyphEndPos(mCursor - 1).x;
				}
				else
				{
					cursorPos.x = text->GetGlyphBeginPos(mCursor).x;
				}
				
				Renderer2D::DrawLine(cursorPos, cursorPos + Vec3f{0.0f , CONSOLE_TEXT_HEIGHT, 0.0f }, mCursorColor);
			}
			else
			{
				Renderer2D::DrawLine(cursorPos, cursorPos + Vec3f{0.0f, CONSOLE_TEXT_HEIGHT, 0.0f}, mCursorColor);
			}
			
			if (mLines.Size())
			{
				Vec3f DrawPos = mEditTextPos - Vec3f{0.f, CONSOLE_TEXT_HEIGHT + CONSOLE_LINE_SPACING, 0.0f};
				for (String& line : mLines)
				{
					if (u32 newLines = line.GetNumberOfLines())
					{
						DrawPos.y -= (newLines * (CONSOLE_TEXT_HEIGHT + CONSOLE_LINE_SPACING));
					}
					Renderer2D::DrawText(line.CStr(), CONSOLE_TEXT_HEIGHT, DrawPos);
					DrawPos.y -= CONSOLE_TEXT_HEIGHT + CONSOLE_LINE_SPACING;
				}
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
					if (mouse->GetState(InputKey::MOUSE_LEFT))
					{
						mBeginResize = true;
					}
				}
			}
			else
			{
				if (mouse->GetState(InputKey::MOUSE_LEFT))
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
		Vec2f TextDim = mFont->GetTextDim(str, CONSOLE_TEXT_HEIGHT);
		u32 MaxLines = mEditTextPos.y / (CONSOLE_TEXT_HEIGHT + CONSOLE_LINE_SPACING);
		String temp = str;

		//TODO Implement wrapping
		mLines.Push(temp);
		if (mLines.Size() > MaxLines) mLines.Pop(); //Maybe add this to the buffer
	}

	void Console::OnKeyPressed(InputKey key, c8 c)
	{
		if (!mIsOpen) return;
		
		if (c)
		{
			if (c == '`' || c == '~') return;

			Vec2f TextDim = mFont->GetTextDim(mInputStr.CStr(), CONSOLE_TEXT_HEIGHT);
			if (TextDim.x > (mWidth - CONSOLE_TEXT_HEIGHT)) return;

			if (mCursor < mInputStr.Size() && mInputStr.Size())
			{
				mInputStr.Insert(c, mCursor);
			}
			else
			{
				mInputStr += c;
			}
			mCursor++;
			
		}
		else
		{
			switch (key)
			{
				case InputKey::KEY_BACK:
				{
					mInputStr--;
					mCursor = ClampLow(--mCursor, 0);
				}break;
				case InputKey::KEY_LEFT:
				{
					mCursor = ClampLow(--mCursor, 0);
					
				}break;
				case InputKey::KEY_RIGHT:
				{
					mCursor = ClampHigh(++mCursor, mInputStr.Size());
					
				}break;
				case InputKey::KEY_ENTER:
				{
					mCursor = 0;
					Log(mInputStr.CStr());
					mInputStr = {};
				}break;
				
			}
			
		}
	}

	void Console::OnKeyReleased(InputKey key)
	{

	}
}

