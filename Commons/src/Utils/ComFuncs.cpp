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
		return (prev = !prev);
	}

	b8 IsBitSet(u64 num, u8 bit)
	{
		return (num & (1ULL << (bit-1)));
	}

	void SetBit(u64* num, u8 bit)
	{
		if (num) (*num) |= (1ULL << (bit - 1));
	}

	void UnSetBit(u64* num, u8 bit)
	{
		if (num) (*num) &= ~(1ULL << (bit - 1));
	}

	b8 IsBitSet(u32 num, u8 bit)
	{
		return (num & (1 << (bit - 1)));
	}

	void SetBit(u32* num, u8 bit)
	{
		if (num) (*num) |= (1 << (bit - 1));
	}

	void UnSetBit(u32* num, u8 bit)
	{
		if (num) (*num) &= ~(1 << (bit - 1));
	}

	u32 GetHighFrom64(u64 val)
	{
		return (u32)(val >> 32ULL);
	}

	u32 GetLowFrom64(u64 val)
	{
		return (u32)val;
	}
}