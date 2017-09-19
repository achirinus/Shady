#ifndef SH_WINDOW
#define SH_WINDOW

#include <Commons.h>
#include "ShadyGL.h"
#include "ShString.h"

#define SH_DEFAULT_WINDOW_WIDTH 1280
#define SH_DEFAULT_WINDOW_HEIGHT 720
#define SH_DEFAULT_WINDOW_TITLE "Shady"

namespace Shady
{
	struct SH_INTERFACE Window
	{
		Window(const c8* title = SH_DEFAULT_WINDOW_TITLE, 
				s16 width = SH_DEFAULT_WINDOW_WIDTH,
				s16 height = SH_DEFAULT_WINDOW_HEIGHT): 
				mHeight(height), mWidth(width), mXPos(0), 
				mYPos(0), mClientWidth(0),
				mClientHeight(0), mFullScreen(0), mOpenglInfo()
				{}

		s16 mWidth;
		s16 mHeight;
		s16 mXPos;
		s16 mYPos;
		s16 mClientWidth;
		s16 mClientHeight;
		b8 mFullScreen;
		OpenglInfo mOpenglInfo;
		
		virtual void update() = 0;
		virtual void swapBuffers() = 0;
		virtual void clear() = 0;
		virtual b8 isOpen() = 0;
		virtual void show() = 0;
		virtual void hide() = 0;
		virtual void minimize() = 0;
		virtual void maximize() = 0;
		virtual void restore() = 0;
		virtual bool isActive() = 0;
		virtual bool isFullScreen() = 0;
		virtual void enableVSync() = 0;
		virtual void disableVSync() = 0;
		virtual void setTitle(const c8* title) = 0;
		virtual String getTitle() = 0;
		virtual ~Window() {};
		virtual void* getPlatformPointer() = 0;
	};
}

#endif