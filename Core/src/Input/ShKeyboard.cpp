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
				c8 c = 0;
				if (IsLetter((c8)key))
				{
					c = key;
					if (!IsCaps())
					{
						c = key + 32;
					}
				}
				listener->OnKeyPressed(key, c);
			}
			else
			{
				listener->OnKeyReleased(key);
			}
		}
		
	}

	b8 Keyboard::IsPrintable(InputKey key)
	{
		if ((key > InputKey::KEY_0) && (key < InputKey::KEY_Z))
		{
			return true;
		}
		return false;
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
}