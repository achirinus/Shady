#ifndef SHADY_KEYBOARD_H
#define SHADY_KEYBOARD_H

#include "Commons.h"
#include "InputKey.h"
#define SHADY_MAX_KEY_COMBO 5

namespace Shady
{
	
	class Keyboard
	{
	private:
		static Keyboard* sInstance;
		bool mKeyStates[MAX_KEYS_SUPPORTED];
		Keyboard() { for(s32 index = 0; index < MAX_KEYS_SUPPORTED; index++) mKeyStates[index] = false;}
	public:
		static Keyboard* GetInstance();
		void Set(InputKey key, bool value);
		bool IsPressed(InputKey key);
		bool IsCombo(s32 numOfKeys ...);
		bool IsCombo(std::initializer_list<s32>);
	};
}

#endif