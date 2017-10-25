#include "ShMouse.h"

namespace Shady
{

	Mouse* Mouse::sInstance = 0;

	inline Mouse* Mouse::GetInstance()
	{
		if(!sInstance)
		{
			sInstance = new Mouse();
		}

		return sInstance;
	}
}