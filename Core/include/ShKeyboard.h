#ifndef SHADY_KEYBOARD_H
#define SHADY_KEYBOARD_H

#include "Commons.h"
#include "InputKey.h"
#include "ShArray.h"
#include <initializer_list>
#define SHADY_MAX_KEY_COMBO 5

namespace Shady
{
	
	struct KeyListener
	{
		virtual void OnKeyPressed(InputKey key, c8 c) {}
		virtual void OnKeyReleased(InputKey key) {}
	};

	class Keyboard
	{
	private:
		static Keyboard* sInstance;
		Array<KeyListener*> mListeners;
		bool mKeyStates[InputKey::MAX_KEYS_SUPPORTED];
		Keyboard() { for(s32 index = 0; index < InputKey::MAX_KEYS_SUPPORTED; index++) mKeyStates[index] = false;}
	public:
		static Keyboard* GetInstance();
		void Set(InputKey key, bool value);
		bool IsPressed(InputKey key);
		bool IsCombo(s32 numOfKeys ...);
		bool IsCombo(std::initializer_list<s32>);
		c8 InputKeyToAscii(InputKey key);
		b8 IsShiftPressed();
		b8 IsCursorControl(InputKey key); //TAB, SPACE, ENTER, BACKSPACE, LEFT, RIGHT, UP, DOWN, DEL, INS, HOME, END
		bool IsPrintable(InputKey key);
		void Register(KeyListener* lis);
		void UnRegister(KeyListener* lis);
		bool IsCaps();
	};
}

#endif