#include "Win32Window.h"
#include <ShadyGL.h>

#include "ShMouse.h"
#include "ShKeyboard.h"
#include "Windowsx.h"
#include "Win32Utils.h"
#include "Vec4.h"

/*
	Win32Window is mixed up win OpenGL. Take care of this somehow, sometime...
	AND DELETE THIS AFTER YOU TAKE CARE OF IT!!!!!
*/


namespace Shady
{
	LRESULT CALLBACK Win32Window::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		
		Win32Window* window = reinterpret_cast<Win32Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
		LRESULT result = 0;
		switch(uMsg)
		{
			case WM_CLOSE:
			{
				window->mIsOpen = false;
				//TODO Check if I should really destroy the contexts here
				//wglMakeCurrent(window->mDC, NULL);
				//wglDeleteContext(window->mGlrc);
				//ReleaseDC(window->mHwnd, window->mDC);
			}break;
			case WM_DESTROY:
			{
				PostQuitMessage(0);
			}break;
			case WM_PAINT:
			{
				PAINTSTRUCT paint;

				HDC dc = BeginPaint(hwnd, &paint);
				EndPaint(hwnd, &paint);
				//ReleaseDC(hwnd, dc);

			}break;
			
			case WM_SYSCOMMAND:
			{
				switch(wParam)
				{
					case SC_MINIMIZE:
					{
						window->Minimize();
						//result = DefWindowProc(hwnd, uMsg, wParam, lParam);
					}break;
					case SC_MAXIMIZE:
					{
						window->Maximize();
						//result = DefWindowProc(hwnd, uMsg, wParam, lParam);
					}break;
					default:
					result = DefWindowProc(hwnd, uMsg, wParam, lParam);
				}
			}break;

			case WM_TIMER:
			{
				
			}break;
			case WM_ACTIVATEAPP:
			{
				if(wParam == TRUE)
				{
					window->mIsActive = true;
				}
				else
				{
					window->mIsActive = false;
				}
			}break;
			case WM_MOVE:
			{
				window->mXPos = (s16) LOWORD(lParam);
				window->mYPos = (s16) HIWORD(lParam);
			}break;
			case WM_SIZE:
			{
				if(wParam == SIZE_RESTORED)
				{
					window->mClientWidth = (s16) LOWORD(lParam);
					window->mClientHeight = (s16) HIWORD(lParam);
					RECT wndRect;
					GetWindowRect(hwnd, &wndRect);
					window->mWidth = wndRect.right - wndRect.left;
					window->mHeight = wndRect.bottom - wndRect.top;
					if(IsGlValidFunc(glViewport))
					{
						glViewport(0, 0, window->mClientWidth,window->mClientHeight);
					}
				}
			}break;
			case WM_CREATE:
			{
				CREATESTRUCT* cs = reinterpret_cast<CREATESTRUCT*>(lParam);
				RECT abd;
				GetClientRect(hwnd, &abd);
				
				Win32Window* window = reinterpret_cast<Win32Window*>(cs->lpCreateParams);
				SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)window);
				window->mClientWidth = abd.right - abd.left;
				window->mClientHeight = abd.bottom - abd.top;
				window->mXPos = cs->x;
				window->mYPos = cs->y;
				window->mWidth = cs->cx;
				window->mHeight = cs->cy;

				//window->mCurrentCursor = LoadCursor(NULL, IDC_ARROW);
				SetCursor(window->mCurrentCursor);
				Shady::Win32::CheckLastError();
				//BringWindowToTop(hwnd);
			}break;
			case WM_LBUTTONDOWN:
			{
				Mouse* mouse = Mouse::GetInstance();
				mouse->m1 = true;
				
			}break;
			case WM_LBUTTONUP:
			{
				Mouse* mouse = Mouse::GetInstance();
				mouse->m1 = false;
			}break;
			case WM_RBUTTONDOWN:
			{
				Mouse* mouse = Mouse::GetInstance();
				mouse->m2 = true;
			}break;
			case WM_RBUTTONUP:
			{
				Mouse* mouse = Mouse::GetInstance();
				mouse->m2 = false;
			}break;
			case WM_MBUTTONDOWN:
			{
				Mouse* mouse = Mouse::GetInstance();
				mouse->m3 = true;
			}break;
			case WM_MBUTTONUP:
			{
				Mouse* mouse = Mouse::GetInstance();
				mouse->m3 = false;
			}break;
			case WM_MOUSEMOVE:
			{
				Mouse* mouse = Mouse::GetInstance();
				mouse->xPos = GET_X_LPARAM(lParam);
				mouse->yPos = GET_Y_LPARAM(lParam);
			}break;
			case WM_KEYDOWN:
			{
				Keyboard* keyboard = Keyboard::GetInstance();
				keyboard->Set((Shady::InputKey)wParam, true);
			}break;
			case WM_KEYUP:
			{
				Keyboard* keyboard = Keyboard::GetInstance();
				keyboard->Set((Shady::InputKey)wParam, false);
			}break;
			default:
			{
				result = DefWindowProc(hwnd, uMsg, wParam, lParam);
			}break;

		}
		return result;
	}



	Win32Window::Win32Window(const c8* title, s16 width, s16 height): Window(title, width, height),
						mIsOpen(false), mHwnd(NULL), mInstance(NULL), mIsActive(false), mGlrc(NULL)
	{
		mInstance = GetModuleHandle(NULL);

		//mCurrentCursor = (HCURSOR)LoadImageA(NULL, "cursor.cur", IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE | LR_SHARED);
		Win32::CheckLastError();
		HICON NewIcon = (HICON)LoadImageA(NULL, "TestIcoFile.ico", IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE | LR_SHARED);
		Win32::CheckLastError();
		WNDCLASS wc = {};
		wc.style = CS_OWNDC;
		wc.lpfnWndProc = WindowProc;
		wc.hInstance = mInstance;
		wc.lpszClassName = TEXT(WINDOW_CLASS_NAME);
		wc.hIcon = NewIcon;
		

		if(RegisterClass(&wc))
		{
			mHwnd = CreateWindowExA(0, WINDOW_CLASS_NAME, title,  
									WS_OVERLAPPEDWINDOW|WS_VISIBLE,
									 CW_USEDEFAULT, CW_USEDEFAULT,SH_DEFAULT_WINDOW_WIDTH, 
									 SH_DEFAULT_WINDOW_HEIGHT, NULL, NULL, mInstance, this);
			if(mHwnd)
			{
				mIsOpen = true;	
				mDC = GetDC(mHwnd);
				mGlrc = Win32GlInit(mDC, &mOpenglInfo);

				SetFocus(mHwnd);
				glViewport_(0,0, mClientWidth, mClientHeight);
			}
		}
		else
		{
			DEBUG_OUT_ERR("Window creation failed!");
		}
	}

	void* Win32Window::GetPlatformPointer()
	{
		return mHwnd;		
	}

	void Win32Window::Show()
	{
		ShowWindow(mHwnd, SW_SHOW);
		Shady::Win32::CheckLastError();
	}

	void Win32Window::Hide()
	{
		ShowWindow(mHwnd, SW_HIDE);
		Shady::Win32::CheckLastError();
	}

	void Win32Window::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Win32Window::Minimize()
	{
		ShowWindow(mHwnd, SW_MINIMIZE);
		Shady::Win32::CheckLastError();
		mFullScreen = false;
	}

	void Win32Window::Maximize()
	{
		ShowWindow(mHwnd, SW_MAXIMIZE);
		Shady::Win32::CheckLastError();
		mFullScreen = true;
	}

	void Win32Window::Restore()
	{
		ShowWindow(mHwnd, SW_RESTORE);
		Shady::Win32::CheckLastError();
	}

	bool Win32Window::IsActive()
	{
		return mIsActive;
	}

	bool Win32Window::IsFullScreen()
	{
		return mFullScreen;
	}

	void Win32Window::SetTitle(const c8* title)
	{
		SetWindowTextA(mHwnd, title);
		Shady::Win32::CheckLastError();
	}


	void Win32Window::EnableVSync()
	{
		if(mOpenglInfo.swapControl)
		{
			wglSwapIntervalEXT(1);
		}
	}
	void Win32Window::DisableVSync()
	{
		if(mOpenglInfo.swapControl)
		{
			wglSwapIntervalEXT(0);
		}
	}

	String Win32Window::GetTitle()
	{
		c8 temp[256];
		GetWindowTextA(mHwnd, temp, 256);
		Shady::Win32::CheckLastError();
		return String(temp);
	}

	void Win32Window::SetCursorVisibility(b8 visible)
	{
		//Windows ShowCursor(bool) increments or decrements a display counter and
		//it hides the cursor only if the counter is < 0 so if SetCursorVisibility is
		//called 3 times with true and then is called with false, the cursor will not be
		//hidden unless I do this.
		if(visible)
		{
			while(ShowCursor(visible) < 0) {} 
		}
		else
		{
			while(ShowCursor(visible) >= 0) {}
		}
		Shady::Win32::CheckLastError();
	}
	void Win32Window::Update()
	{
		while(PeekMessage(&mMessage, mHwnd, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&mMessage);
			DispatchMessage(&mMessage);
		}
	}

	void Win32Window::SwapBuffers()
	{
		::SwapBuffers(mDC);
	}

	b8 Win32Window::IsOpen()
	{
		return mIsOpen;
	}

	void Win32Window::SetBackgroundColor(const Vec4f& col)
	{
		glClearColor(col.r, col.g, col.b, col.a);
	}

	Win32Window::~Win32Window()
	{
	
	}

}