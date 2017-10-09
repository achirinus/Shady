#include "ShMouse.h"

namespace Shady
{

	Mouse* Mouse::sInstance = 0;

	inline Mouse* Mouse::getInstance()
	{
		if(!sInstance)
		{
			sInstance = new Mouse();
		}

		return sInstance;
	}
}