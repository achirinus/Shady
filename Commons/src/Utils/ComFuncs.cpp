#include "ComFuncs.h"

namespace Shady
{
	
	void ClearMem(void* mem, u64 size)
	{
		c8* temp = (c8*)mem;
		while(size--)
		{
			*temp++ = 0;
		}
	}

	bool FlipFlop(b8& prev)
	{
		return (prev != prev);
	}
}