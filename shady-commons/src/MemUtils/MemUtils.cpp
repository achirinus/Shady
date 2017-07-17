#include "MemUtils.h"

namespace Shady
{
	void zeroMemory(void* mem, u64 size)
	{
		c8* tempMem = (c8*)mem;
		while(size--) *tempMem++ = 0;
	}
}