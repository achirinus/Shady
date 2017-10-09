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
		static Keyboard* getInstance();
		void set(InputKey key, bool value);
		bool isPressed(InputKey key);
		bool isCombo(s32 numOfKeys ...);
	};
}

#endif