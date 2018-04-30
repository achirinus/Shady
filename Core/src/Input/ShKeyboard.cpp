#include "ShKeyboard.h"
#include <initializer_list>
#include "StringUtils.h"



namespace Shady
{

	Keyboard* Keyboard::sInstance = 0;

	Keyboard* Keyboard::GetInstance()
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
		for (KeyListener* listener : mListeners)
		{
			if (value)
			{
				listener->OnKeyPressed(key, InputKeyToAscii(key));
			}
			else
			{
				listener->OnKeyReleased(key);
			}
		}
		
	}

	b8 Keyboard::IsShiftPressed()
	{
		return ((mKeyStates[InputKey::KEY_LSHIFT]) || (mKeyStates[InputKey::KEY_RSHIFT]));
	}

	b8 Keyboard::IsCursorControl(InputKey key)
	{
		switch (key)
		{
		case InputKey::KEY_TAB:
		case InputKey::KEY_ENTER:
		case InputKey::KEY_SPACE:
		case InputKey::KEY_HOME:
		case InputKey::KEY_LEFT:
		case InputKey::KEY_RIGHT:
		case InputKey::KEY_END:
		case InputKey::KEY_INS:
		case InputKey::KEY_DEL:
			return true;
			break;
		default:
			return false;
		}
		return true;
	}

	b8 Keyboard::IsPrintable(InputKey key)
	{
		switch (key)
		{
		case InputKey::KEY_ESC:
		case InputKey::KEY_TAB:
		case InputKey::KEY_ENTER:
		case InputKey::KEY_CONTROL:
		case InputKey::KEY_LSHIFT:
		case InputKey::KEY_RSHIFT: 
		case InputKey::KEY_ALT: 
		case InputKey::KEY_CAPS: 
		case InputKey::KEY_HOME:
		case InputKey::KEY_UP: 
		case InputKey::KEY_PGUP:
		case InputKey::KEY_LEFT:
		case InputKey::KEY_RIGHT:
		case InputKey::KEY_END:
		case InputKey::KEY_DOWN: 
		case InputKey::KEY_PGDOWN:
		case InputKey::KEY_INS:
		case InputKey::KEY_DEL: 
		case InputKey::MOUSE_X:
		case InputKey::MOUSE_Y:
		case InputKey::MOUSE_LEFT:
		case InputKey::MOUSE_RIGHT:
		case InputKey::MOUSE_MIDDLE:
			return false;
			break;
		default:
			return true; 
		}
		return true;
	}

	void Keyboard::Register(KeyListener* lis)
	{
		mListeners.Add(lis);
	}

	void Keyboard::UnRegister(KeyListener* lis)
	{
		u32 index = mListeners.FindFirstIndex(lis);
		if (index >= 0)
		{
			mListeners.Remove(index);
		}
	}

	b8 Keyboard::IsCaps()
	{
		return GetKeyState(VK_CAPITAL) && 0x0001;
	}

	c8 Keyboard::InputKeyToAscii(InputKey key)
	{
		c8 result = 0;
		b8 Shift = IsShiftPressed();
		b8 Caps = IsCaps();
		switch (key)
		{

		case InputKey::KEY_1:
		{
			if (Shift)
			{
				result = '!';
			}
			else
			{
				result = '1';
			}
		}break;
		case InputKey::KEY_2:
		{
			if (Shift)
			{
				result = '@';
			}
			else
			{
				result = '2';
			}
		}break;
		case InputKey::KEY_3:
		{
			if (Shift)
			{
				result = '#';
			}
			else
			{
				result = '3';
			}
		}break;
		case InputKey::KEY_4:
		{
			if (Shift)
			{
				result = '$';
			}
			else
			{
				result = '4';
			}
		}break;
		case InputKey::KEY_5:
		{
			if (Shift)
			{
				result = '%';
			}
			else
			{
				result = '5';
			}
		}break;
		case InputKey::KEY_6:
		{
			if (Shift)
			{
				result = '^';
			}
			else
			{
				result = '6';
			}
		}break;
		case InputKey::KEY_7:
		{
			if (Shift)
			{
				result = '&';
			}
			else
			{
				result = '7';
			}
		}break;
		case InputKey::KEY_8:
		{
			if (Shift)
			{
				result = '*';
			}
			else
			{
				result = '8';
			}
		}break;
		case InputKey::KEY_9:
		{
			if (Shift)
			{
				result = '(';
			}
			else
			{
				result = '9';
			}
		}break;
		case InputKey::KEY_0:
		{
			if (Shift)
			{
				result = ')';
			}
			else
			{
				result = '0';
			}
		}break;
		case InputKey::KEY_UNDERSCORE:
		{
			if (Shift)
			{
				result = '_';
			}
			else
			{
				result = '-';
			}
		}break;
		case InputKey::KEY_EQUAL:
		{
			if (Shift)
			{
				result = '+';
			}
			else
			{
				result = '=';
			}
		}break;
		case InputKey::KEY_Q:
		{
			if (Caps)
			{
				if (Shift)
				{
					result = 'q';
				}
				else
				{
					result = 'Q';
				}
			}
			else
			{
				if (Shift)
				{
					result = 'Q';
				}
				else
				{
					result = 'q';
				}
			}
		}break;
		case InputKey::KEY_W:
		{
			if (Caps)
			{
				if (Shift)
				{
					result = 'w';
				}
				else
				{
					result = 'W';
				}
			}
			else
			{
				if (Shift)
				{
					result = 'W';
				}
				else
				{
					result = 'w';
				}
			}
		}break;
		case InputKey::KEY_E:
		{
			if (Caps)
			{
				if (Shift)
				{
					result = 'e';
				}
				else
				{
					result = 'E';
				}
			}
			else
			{
				if (Shift)
				{
					result = 'E';
				}
				else
				{
					result = 'e';
				}
			}
		}break;
		case InputKey::KEY_R:
		{
			if (Caps)
			{
				if (Shift)
				{
					result = 'r';
				}
				else
				{
					result = 'R';
				}
			}
			else
			{
				if (Shift)
				{
					result = 'R';
				}
				else
				{
					result = 'r';
				}
			}
		}break;
		case InputKey::KEY_T:
		{
			if (Caps)
			{
				if (Shift)
				{
					result = 't';
				}
				else
				{
					result = 'T';
				}
			}
			else
			{
				if (Shift)
				{
					result = 'T';
				}
				else
				{
					result = 't';
				}
			}
		}break;
		case InputKey::KEY_Y:
		{
			if (Caps)
			{
				if (Shift)
				{
					result = 'y';
				}
				else
				{
					result = 'Y';
				}
			}
			else
			{
				if (Shift)
				{
					result = 'Y';
				}
				else
				{
					result = 'y';
				}
			}
		}break;
		case InputKey::KEY_U:
		{
			if (Caps)
			{
				if (Shift)
				{
					result = 'u';
				}
				else
				{
					result = 'U';
				}
			}
			else
			{
				if (Shift)
				{
					result = 'U';
				}
				else
				{
					result = 'u';
				}
			}
		}break;
		case InputKey::KEY_I:
		{
			if (Caps)
			{
				if (Shift)
				{
					result = 'i';
				}
				else
				{
					result = 'I';
				}
			}
			else
			{
				if (Shift)
				{
					result = 'I';
				}
				else
				{
					result = 'i';
				}
			}
		}break;
		case InputKey::KEY_O:
		{
			if (Caps)
			{
				if (Shift)
				{
					result = 'o';
				}
				else
				{
					result = 'O';
				}
			}
			else
			{
				if (Shift)
				{
					result = 'O';
				}
				else
				{
					result = 'o';
				}
			}
		}break;
		case InputKey::KEY_P:
		{
			if (Caps)
			{
				if (Shift)
				{
					result = 'p';
				}
				else
				{
					result = 'P';
				}
			}
			else
			{
				if (Shift)
				{
					result = 'P';
				}
				else
				{
					result = 'p';
				}
			}
		}break;
		case InputKey::KEY_LEFTBRACKET:
		{
			if (Shift)
			{
				result = '{';
			}
			else
			{
				result = '[';
			}
		}break;
		case InputKey::KEY_RIGHTBRACKET:
		{
			if (Shift)
			{
				result = '}';
			}
			else
			{
				result = ']';
			}
		}break;
		case InputKey::KEY_A:
		{
			if (Caps)
			{
				if (Shift)
				{
					result = 'a';
				}
				else
				{
					result = 'A';
				}
			}
			else
			{
				if (Shift)
				{
					result = 'A';
				}
				else
				{
					result = 'a';
				}
			}
		}break;
		case InputKey::KEY_S:
		{
			if (Caps)
			{
				if (Shift)
				{
					result = 's';
				}
				else
				{
					result = 'S';
				}
			}
			else
			{
				if (Shift)
				{
					result = 'S';
				}
				else
				{
					result = 's';
				}
			}
		}break;
		case InputKey::KEY_D:
		{
			if (Caps)
			{
				if (Shift)
				{
					result = 'd';
				}
				else
				{
					result = 'D';
				}
			}
			else
			{
				if (Shift)
				{
					result = 'D';
				}
				else
				{
					result = 'd';
				}
			}
		}break;
		case InputKey::KEY_F:
		{
			if (Caps)
			{
				if (Shift)
				{
					result = 'f';
				}
				else
				{
					result = 'F';
				}
			}
			else
			{
				if (Shift)
				{
					result = 'F';
				}
				else
				{
					result = 'f';
				}
			}
		}break;
		case InputKey::KEY_G:
		{
			if (Caps)
			{
				if (Shift)
				{
					result = 'g';
				}
				else
				{
					result = 'G';
				}
			}
			else
			{
				if (Shift)
				{
					result = 'G';
				}
				else
				{
					result = 'g';
				}
			}
		}break;
		case InputKey::KEY_H:
		{
			if (Caps)
			{
				if (Shift)
				{
					result = 'h';
				}
				else
				{
					result = 'H';
				}
			}
			else
			{
				if (Shift)
				{
					result = 'H';
				}
				else
				{
					result = 'h';
				}
			}
		}break;
		case InputKey::KEY_J:
		{
			if (Caps)
			{
				if (Shift)
				{
					result = 'j';
				}
				else
				{
					result = 'J';
				}
			}
			else
			{
				if (Shift)
				{
					result = 'J';
				}
				else
				{
					result = 'j';
				}
			}
		}break;
		case InputKey::KEY_K:
		{
			if (Caps)
			{
				if (Shift)
				{
					result = 'k';
				}
				else
				{
					result = 'K';
				}
			}
			else
			{
				if (Shift)
				{
					result = 'K';
				}
				else
				{
					result = 'k';
				}
			}
		}break;
		case InputKey::KEY_L:
		{
			if (Caps)
			{
				if (Shift)
				{
					result = 'l';
				}
				else
				{
					result = 'L';
				}
			}
			else
			{
				if (Shift)
				{
					result = 'L';
				}
				else
				{
					result = 'l';
				}
			}
		}break;
		case InputKey::KEY_SEMICOLON:
		{
			if (Shift)
			{
				result = ':';
			}
			else
			{
				result = ';';
			}
		}break;
		case InputKey::KEY_QUOTE:
		{
			if (Shift)
			{
				result = '"';
			}
			else
			{
				result = '\'';
			}
		}break;
		case InputKey::KEY_TILDA:
		{
			if (Shift)
			{
				result = '~';
			}
			else
			{
				result = '`';
			}
		}break;
		case InputKey::KEY_BACKSLASH:
		{
			if (Shift)
			{
				result = '|';
			}
			else
			{
				result = '\\';
			}
		}break;
		case InputKey::KEY_Z:
		{
			if (Caps)
			{
				if (Shift)
				{
					result = 'z';
				}
				else
				{
					result = 'Z';
				}
			}
			else
			{
				if (Shift)
				{
					result = 'Z';
				}
				else
				{
					result = 'z';
				}
			}
		}break;
		case InputKey::KEY_X:
		{
			if (Caps)
			{
				if (Shift)
				{
					result = 'x';
				}
				else
				{
					result = 'X';
				}
			}
			else
			{
				if (Shift)
				{
					result = 'X';
				}
				else
				{
					result = 'x';
				}
			}
		}break;
		case InputKey::KEY_C:
		{
			if (Caps)
			{
				if (Shift)
				{
					result = 'c';
				}
				else
				{
					result = 'C';
				}
			}
			else
			{
				if (Shift)
				{
					result = 'C';
				}
				else
				{
					result = 'c';
				}
			}
		}break;
		case InputKey::KEY_V:
		{
			if (Caps)
			{
				if (Shift)
				{
					result = 'v';
				}
				else
				{
					result = 'V';
				}
			}
			else
			{
				if (Shift)
				{
					result = 'V';
				}
				else
				{
					result = 'v';
				}
			}
		}break;
		case InputKey::KEY_B:
		{
			if (Caps)
			{
				if (Shift)
				{
					result = 'b';
				}
				else
				{
					result = 'B';
				}
			}
			else
			{
				if (Shift)
				{
					result = 'B';
				}
				else
				{
					result = 'b';
				}
			}
		}break;
		case InputKey::KEY_N:
		{
			if (Caps)
			{
				if (Shift)
				{
					result = 'n';
				}
				else
				{
					result = 'N';
				}
			}
			else
			{
				if (Shift)
				{
					result = 'N';
				}
				else
				{
					result = 'n';
				}
			}
		}break;
		case InputKey::KEY_M:
		{
			if (Caps)
			{
				if (Shift)
				{
					result = 'm';
				}
				else
				{
					result = 'M';
				}
			}
			else
			{
				if (Shift)
				{
					result = 'M';
				}
				else
				{
					result = 'm';
				}
			}
		}break;
		case InputKey::KEY_COMMA:
		{
			if (Shift)
			{
				result = '<';
			}
			else
			{
				result = ',';
			}
		}break;
		case InputKey::KEY_DOT:
		{
			if (Shift)
			{
				result = '>';
			}
			else
			{
				result = '.';
			}
		}break;
		case InputKey::KEY_FORWARDSLASH:
		{
			if (Shift)
			{
				result = '?';
			}
			else
			{
				result = '/';
			}
		}break;
		case InputKey::KEY_SPACE:
		{
			result = ' ';
		}break;
		default:
			result = 0;
			break;
		}
		return result;
	}
}