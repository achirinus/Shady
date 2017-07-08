#include "ShKeyboard.h"


namespace Shady
{

	Keyboard* Keyboard::sInstance = 0;

	inline Keyboard* Keyboard::getInstance()
	{
		if(!sInstance)
		{
			sInstance = new Keyboard();
		}
		return sInstance;
	}

	bool Keyboard::isCombo(s32 numOfKeys ...)
	{
		SH_ASSERT(numOfKeys <= SHADY_MAX_KEY_COMBO);
		va_list list;
		va_start(list, numOfKeys);
		bool result = false;

		for(s32 i = 0; i < numOfKeys; i++)
		{
			s32 keyIndex = va_arg(list, s32);
			bool val = mKeyStates[keyIndex];
			if(!val) return false;
			result = true;
		}
		return result;
	}

	bool Keyboard::isPressed(Key key)
	{
		return mKeyStates[key];
	}

	void Keyboard::set(Key key, bool value)
	{
		mKeyStates[key] = value;
	}
}