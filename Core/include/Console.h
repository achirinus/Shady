#ifndef SH_CONSOLE_H 
#define SH_CONSOLE_H

#include "Commons.h"
#include "ComFuncs.h"
#include "ShObject.h"
#include "Vec3.h"
#include "ShKeyboard.h"
#include "ShString.h"

namespace Shady
{
	class Console : public KeyListener
	{
		c8 mBuffer[MegaBytes(1)];
		String mInputStr;
		c8* mCaret;
		static Console* mInstance;
		Console();
	public:
		b8 mIsOpen;
		b8 mBeginResize;
		u32 mWidth;
		u32 mHeight;
		Vec3f mPos;
		Vec3f mEditTextPos;
		u32 mMarginBoundOff;

		static Console* GetInstance();

		void Open();
		void Close();
		static void Toggle();
		void Init();
		void Render();
		void Update(f32 dt);
		void Log(const c8* str);
		void OnKeyPressed(InputKey key) override;
		void OnKeyReleased(InputKey key) override;
	};
}

#endif
