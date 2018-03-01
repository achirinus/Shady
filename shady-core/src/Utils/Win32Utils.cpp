#include "Win32Utils.h"
#include "Windows.h"
#include "ConsoleOut.h"

namespace Shady
{
	namespace Win32
	{
		void CheckLastError()
		{
			DWORD ErrId = GetLastError();
			if(ErrId)
			{
				LPCSTR buffer = NULL;
				FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER |
							FORMAT_MESSAGE_IGNORE_INSERTS, NULL, ErrId, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
							(LPSTR)&buffer, 0, NULL);
				DEBUG_OUT_ERR(buffer);
			}
		}
	}
}