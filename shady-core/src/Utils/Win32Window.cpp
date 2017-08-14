#include "Win32Window.h"
#include <glew.h>
#include <wglew.h>
#include "ShMouse.h"
#include "ShKeyboard.h"
#include "Windowsx.h"

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
				wglMakeCurrent(window->mDC, NULL);
				wglDeleteContext(window->mGlrc);
				ReleaseDC(window->mHwnd, window->mDC);
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
						window->minimize();
						//result = DefWindowProc(hwnd, uMsg, wParam, lParam);
					}break;
					case SC_MAXIMIZE:
					{
						window->maximize();
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

				}
			}break;
			case WM_CREATE:
			{
				CREATESTRUCT* cs = reinterpret_cast<CREATESTRUCT*>(lParam);
				RECT abd;
				GetClientRect(hwnd, &abd);
				Win32Window* window = reinterpret_cast<Win32Window*>(cs->lpCreateParams);
				SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)window);
				window->mXPos = cs->x;
				window->mYPos = cs->y;
				window->mWidth = cs->cx;
				window->mHeight = cs->cy;

			}break;
			case WM_LBUTTONDOWN:
			{
				Mouse* mouse = Mouse::getInstance();
				mouse->m1 = true;
			}break;
			case WM_LBUTTONUP:
			{
				Mouse* mouse = Mouse::getInstance();
				mouse->m1 = false;
			}break;
			case WM_RBUTTONDOWN:
			{
				Mouse* mouse = Mouse::getInstance();
				mouse->m2 = true;
			}break;
			case WM_RBUTTONUP:
			{
				Mouse* mouse = Mouse::getInstance();
				mouse->m2 = false;
			}break;
			case WM_MBUTTONDOWN:
			{
				Mouse* mouse = Mouse::getInstance();
				mouse->m3 = true;
			}break;
			case WM_MBUTTONUP:
			{
				Mouse* mouse = Mouse::getInstance();
				mouse->m3 = false;
			}break;
			case WM_MOUSEMOVE:
			{
				Mouse* mouse = Mouse::getInstance();
				mouse->xPos = GET_X_LPARAM(lParam);
				mouse->yPos = GET_Y_LPARAM(lParam);
			}break;
			case WM_KEYDOWN:
			{
				Keyboard* keyboard = Keyboard::getInstance();
				keyboard->set((Shady::Key)wParam, true);
			}break;
			case WM_KEYUP:
			{
				Keyboard* keyboard = Keyboard::getInstance();
				keyboard->set((Shady::Key)wParam, false);
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

		WNDCLASS wc = {};
		wc.style = CS_OWNDC;
		wc.lpfnWndProc = WindowProc;
		wc.hInstance = mInstance;
		wc.lpszClassName = TEXT(WINDOW_CLASS_NAME);

		if(RegisterClass(&wc))
		{
			mHwnd = CreateWindowExA(0, WINDOW_CLASS_NAME, title,  WS_OVERLAPPEDWINDOW|WS_VISIBLE,
									 CW_USEDEFAULT, CW_USEDEFAULT,SH_DEFAULT_WINDOW_WIDTH, 
									 SH_DEFAULT_WINDOW_HEIGHT, NULL, NULL, mInstance, this);
			

			if(mHwnd)
			{
				mIsOpen = true;	
				mDC = GetDC(mHwnd);
				mGlrc = Win32GlInit(mDC, &mOpenglInfo);
				
				glClearColor(1.0f, 0.5f, 0.5f, 1.0f);
				glViewport(0,0, SH_DEFAULT_WINDOW_WIDTH, SH_DEFAULT_WINDOW_HEIGHT);
				//glEnable(GL_CULL_FACE); 
				glEnable(GL_BLEND);
				glEnable(GL_LINE_SMOOTH); //Antialiasing				
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				
			}
		}
		else
		{
			DEBUG_OUT_ERR("Window creation failed!");
		}

		
	}

	void* Win32Window::getPlatformPointer()
	{
		return mHwnd;		
	}

	void Win32Window::show()
	{
		ShowWindow(mHwnd, SW_SHOW);
	}

	void Win32Window::hide()
	{
		ShowWindow(mHwnd, SW_HIDE);
	}

	void Win32Window::clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Win32Window::minimize()
	{
		ShowWindow(mHwnd, SW_MINIMIZE);
		mFullScreen = false;
	}

	void Win32Window::maximize()
	{
		ShowWindow(mHwnd, SW_MAXIMIZE);
		mFullScreen = true;
	}

	void Win32Window::restore()
	{
		ShowWindow(mHwnd, SW_RESTORE);
	}

	bool Win32Window::isActive()
	{
		return mIsActive;
	}

	bool Win32Window::isFullScreen()
	{
		return mFullScreen;
	}

	void Win32Window::setTitle(const c8* title)
	{
		SetWindowTextA(mHwnd, title);
	}

	void Win32Window::enableVSync()
	{
		if(mOpenglInfo.swapControl)
		{
			wglSwapIntervalEXT(1);
		}
	}
	void Win32Window::disableVSync()
	{
		wglSwapIntervalEXT(0);
	}

	void Win32Window::update()
	{
		while(PeekMessage(&mMessage, mHwnd, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&mMessage);
			DispatchMessage(&mMessage);
		}
	}

	void Win32Window::swapBuffers()
	{
		SwapBuffers(mDC);
	}

	b8 Win32Window::isOpen()
	{
		return mIsOpen;
	}

	Win32Window::~Win32Window()
	{
	
	
	}

}