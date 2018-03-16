#ifndef SH_CONSOLE_H 
#define SH_CONSOLE_H

#include "Commons.h"
#include "ComFuncs.h"
namespace Shady
{
	class Console
	{
		c8 mBuffer[MegaBytes(1)];
		c8* mCaret;
		static Console* mInstance;
		Console();
	public:
		b8 mIsOpen;
		
		static Console* GetInstance();

		void Open();
		void Close();
		void Toggle();
		void Render();
		void Update(f32 dt);
	};
}

#endif
