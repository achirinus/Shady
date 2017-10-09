#ifndef SHADY_MOUSE_H
#define SHADY_MOUSE_H

#include "Commons.h"
#include "InputKey.h"
namespace Shady
{
	class Mouse
	{
	private:
		static Mouse* sInstance;
		Mouse(): xPos(0), yPos(0), m1(false), m2(false),
				m3(false), m4(false) {}

	public:
		static Mouse* getInstance();
		s32 xPos;
		s32 yPos;
		b32 m1;
		b32 m2;
		b32 m3;
		b32 m4;
		b32 m5;

		b8 getState(InputKey key)
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

		f32 getValue(InputKey key)
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
	};
}

#endif