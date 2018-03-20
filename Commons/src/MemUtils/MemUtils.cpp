#include "MemUtils.h"

namespace Shady
{
	void ZeroMem(void* mem, u64 size)
	{
		c8* tempMem = (c8*)mem;
		while(size--) *tempMem++ = 0;
	}

	s64 SwapEndian(s64 SizeInBigEndian)
	{
		s64 result = 0;
		result |= (SizeInBigEndian & 0xFF00000000000000) >> 56;
		result |= (SizeInBigEndian & 0x00FF000000000000) >> 32;
		result |= (SizeInBigEndian & 0x0000FF0000000000) >> 24;
		result |= (SizeInBigEndian & 0x000000FF00000000) >> 8;
		result |= (SizeInBigEndian & 0x00000000FF000000) << 8;
		result |= (SizeInBigEndian & 0x0000000000FF0000) << 24;
		result |= (SizeInBigEndian & 0x000000000000FF00) << 32;
		result |= (SizeInBigEndian & 0x00000000000000FF) << 56;
		return result;
	}

	s32 SwapEndian(s32 SizeInBigEndian)
	{
		s32 result = 0;
		result |= (SizeInBigEndian & 0xFF000000) >> 24;
		result |= (SizeInBigEndian & 0x00FF0000) >> 8;
		result |= (SizeInBigEndian & 0x0000FF00) << 8;
		result |= (SizeInBigEndian & 0x000000FF) << 24;
		return result;
	}
	s16 SwapEndian(s16 SizeInBigEndian)
	{
		s32 result = 0;
		result |= (SizeInBigEndian & 0xFF00) >> 8;
		result |= (SizeInBigEndian & 0x00FF) << 8;
		return result;
	}	

	u32 GetValueFromBitRange(u32 num, c8 bit1, c8 bit2)
	{
		u32 val = 0;
		for (c8 i = 0; i <= (bit2 - bit1); i++)
		{
			val |= 1 << i;
		}
		u32 Temp = num >> bit1;
		return (Temp & val);
	}
}