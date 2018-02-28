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

	b8 Mouse::GetState(InputKey key)
	{
		b8 result = false;
		switch(key)
		{
			case MOUSE_LEFT:
			{
				result = (b8)m1;
			}break;
			case MOUSE_RIGHT:
			{
				result = (b8)m2;
			}break;
			case MOUSE_MIDDLE:
			{
				result = (b8)m3;
			}break;
		}
		return result;
	}

	f32 Mouse::GetValue(InputKey key)
	{
		f32 result = 0.0f;
		switch(key)
		{
			case MOUSE_X:
			{
				result = (f32)xPos;
			}break;
			case MOUSE_Y:
			{
				result = (f32)yPos;
			}break;
		}
		return result;
	}

	Vec2f Mouse::GetCursorPosition()
	{
		return {(f32)xPos, (f32)yPos};
	}
}