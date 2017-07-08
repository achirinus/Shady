#ifndef SHADY_APP_H
#define SHADY_APP_H

#include "Window.h"
#include "Commons.h"
#include "ShMouse.h"
#include "ShKeyboard.h"

namespace Shady
{
	class ShadyApp
	{
	private:
		static ShadyApp* sInstance;
		ShadyApp():mMainWindow(0), mMouse(0), mKeyboard(0) {}

		Window* mMainWindow;
		Mouse* mMouse;
		Keyboard* mKeyboard;

	public:
		static ShadyApp& getInstance();
		void start();
	};	
}

#endif