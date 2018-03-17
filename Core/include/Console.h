#ifndef SH_CONSOLE_H 
#define SH_CONSOLE_H

#include "Commons.h"
#include "ComFuncs.h"
#include "ShObject.h"
namespace Shady
{
	class Console : public Object
	{
		c8 mBuffer[MegaBytes(1)];
		c8* mCaret;
		static Console* mInstance;
		Console();
	public:
		b8 mIsOpen;
		u32 mWidth;
		u32 mHeight;

		static Console* GetInstance();

		void Open();
		void Close();
		void Toggle();
		void Init();
		void Render();
		void Update(f32 dt);
		void Log(const c8* str);
	};
}

#endif
