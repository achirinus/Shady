#ifndef SH_WIN32_WINDOW
#define SH_WIN32_WINDOW

#include "Window.h"
#include <Windows.h>

namespace Shady
{

#define WINDOW_CLASS_NAME "SHADY WINDOW"

	struct Win32Window: public Window
	{
		b8 mIsOpen;
		b8 mIsActive;
		HWND mHwnd;
		HDC mDC;
		HINSTANCE mInstance;
		HGLRC mGlDC;
		MSG mMessage;
		Win32Window(const c8* title = SH_DEFAULT_WINDOW_TITLE, 
				s16 width = SH_DEFAULT_WINDOW_WIDTH,
				s16 height = SH_DEFAULT_WINDOW_HEIGHT);

		virtual void update();
		virtual void swapBuffers();
		virtual void clear();
		virtual b8 isOpen();
		virtual void show();
		virtual void hide();
		virtual void minimize();
		virtual void maximize();
		virtual void restore();
		virtual bool isActive();
		virtual void* getPlatformPointer();
		virtual ~Win32Window();
		static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	};
}

#endif