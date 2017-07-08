#include <ShadyApp.h>
#include "Win32Window.h"

namespace Shady
{
	ShadyApp* ShadyApp::sInstance = 0;

	inline ShadyApp& ShadyApp::getInstance()
	{
		if(!sInstance)
		{
			sInstance = new ShadyApp();
		}

		return *sInstance;
	}

	void ShadyApp::start()
	{
		mMainWindow = new Win32Window();
		mMouse = Mouse::getInstance();
		mKeyboard = Keyboard::getInstance();

		while (mMainWindow->isOpen())
		{
			mMainWindow->update();
			mMainWindow->clear();
		
			mMainWindow->swapBuffers();
		}
	}


}
