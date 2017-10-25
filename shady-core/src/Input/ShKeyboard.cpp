#include "ShKeyboard.h"
#include <initializer_list>

namespace Shady
{

	Keyboard* Keyboard::sInstance = 0;

	inline Keyboard* Keyboard::GetInstance()
	{
		if(!sInstance)
		{
			sInstance = new Keyboard();
		}
		return sInstance;
	}

	bool Keyboard::IsCombo(s32 numOfKeys ...)
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
		va_end(list);
		
		return result;
	}

	bool Keyboard::IsCombo(std::initializer_list<s32> list)
	{
		u32 numOfKeys = list.size();

		SH_ASSERT(numOfKeys <= SHADY_MAX_KEY_COMBO);
		
		bool result = false;

		auto it = list.begin();

		for(s32 i = 0; i < numOfKeys; i++, it++)
		{
			s32 keyIndex = *it;
			bool val = mKeyStates[keyIndex];
			if(!val) return false;
			result = true;
		}
		return result;
	}

	bool Keyboard::IsPressed(InputKey key)
	{
		return mKeyStates[key];
	}

	void Keyboard::Set(InputKey key, bool value)
	{
		mKeyStates[key] = value;
	}
}