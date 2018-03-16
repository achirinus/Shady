#ifndef SH_WIN32_WINDOW
#define SH_WIN32_WINDOW

#include "Window.h"
#include "ShadyGL.h"
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
		HGLRC mGlrc;
		MSG mMessage;
		HCURSOR mCurrentCursor;
		Win32Window(const c8* title = SH_DEFAULT_WINDOW_TITLE, 
				s16 width = SH_DEFAULT_WINDOW_WIDTH,
				s16 height = SH_DEFAULT_WINDOW_HEIGHT);

		virtual void Update();
		virtual void SwapBuffers();
		virtual void Clear();
		virtual b8 IsOpen();
		virtual void SetBackgroundColor(const Vec4f& col);
		virtual void Show();
		virtual void Hide();
		virtual void Minimize();
		virtual void Maximize();
		virtual void Restore();
		virtual bool IsActive();
		virtual bool IsFullScreen();
		virtual void SetTitle(const c8* title);
		virtual void EnableVSync();
		virtual void DisableVSync();
		virtual void* GetPlatformPointer();
		virtual String GetTitle();
		virtual void SetCursorVisibility(b8 visible);
		virtual ~Win32Window();
		static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		static VOID CALLBACK renderTimerProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);
		static VOID CALLBACK updateTimerProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);
	};
}

#endif