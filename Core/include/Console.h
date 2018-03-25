#ifndef SH_CONSOLE_H 
#define SH_CONSOLE_H

#include "Commons.h"
#include "ComFuncs.h"
#include "ShObject.h"
#include "Vec3.h"
#include "Vec4.h"
#include "ShKeyboard.h"
#include "ShString.h"
#include "ShQueue.h"
#include "ShFont.h"

namespace Shady
{
	class Console : public KeyListener
	{
		c8 mBuffer[MegaBytes(1)];
		Queue<String> mLines;
		String mInputStr;
		u32 mCursor;
		Font* mFont;
		static Console* mInstance;
		Console();
	public:
		b8 mIsOpen;
		b8 mBeginResize;
		u32 mWidth;
		u32 mHeight;
		Vec3f mPos;
		Vec3f mEditTextPos;
		Vec4f mCursorColor;
		u32 mMarginBoundOff;
		f32 mTimeSinceOpen; //For now only used for cursor blinking
		static Console* GetInstance();

		void Open();
		void Close();
		static void Toggle();
		void Init();
		void Render();
		void Update(f32 dt);
		void Log(const c8* str);
		void OnKeyPressed(InputKey key, c8 c) override;
		void OnKeyReleased(InputKey key) override;
	};
}

#endif
