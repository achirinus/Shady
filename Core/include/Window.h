#ifndef SH_WIN32_WINDOW
#define SH_WIN32_WINDOW


#include "ShadyGL.h"
#include "Vec4.h"
#include "ShString.h"
#include <Commons.h>
#include <Windows.h>

namespace Shady
{

#define SH_DEFAULT_WINDOW_WIDTH 1280
#define SH_DEFAULT_WINDOW_HEIGHT 720
#define SH_DEFAULT_WINDOW_TITLE "Shady"
#define WINDOW_CLASS_NAME "SHADY WINDOW"
#define MAX_WINDOW_TITLE_SIZE 256

	struct Window {
		b8 mIsOpen;
		b8 mIsActive;
		s16 mWidth;
		s16 mHeight;
		s16 mXPos;
		s16 mYPos;
		s16 mClientWidth;
		s16 mClientHeight;
		b8 mFullScreen;
		c8 mTitle[MAX_WINDOW_TITLE_SIZE];
		Opengl* mOpenglInfo;
		HWND mHwnd;
		HDC mDC;
		HINSTANCE mInstance;
		HGLRC mGlrc;
		MSG mMessage;
		HCURSOR mCurrentCursor;
		Window(const c8* title = SH_DEFAULT_WINDOW_TITLE, 
				s16 width = SH_DEFAULT_WINDOW_WIDTH,
				s16 height = SH_DEFAULT_WINDOW_HEIGHT);

		void Update();
		void SwapBuffers();
		void Clear();
		b8 IsOpen();
		void SetBackgroundColor(const Vec4f& col);
		void Show();
		void Hide();
		void Minimize();
		void Maximize();
		void Restore();
		bool IsActive();
		bool IsFullScreen();
		void SetTitle(const c8* title);
		void EnableVSync();
		void DisableVSync();
		void* GetPlatformPointer();
		String GetTitle();
		void SetCursorVisibility(b8 visible);
		~Window();
		static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		
	};
}

#endif