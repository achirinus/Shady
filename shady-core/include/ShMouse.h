#ifndef SHADY_MOUSE_H
#define SHADY_MOUSE_H

#include "Commons.h"

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
	};
}

#endif