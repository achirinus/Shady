#ifndef SH_MEM_UTILS_H
#define SH_MEM_UTILS_H
#include "ShTypes.h"

namespace Shady
{
	#define ARRAY_COUNT(arr) (sizeof(arr)/ sizeof(arr[0]))
	#define MEM_ALIGN_TYPE(buf, align, type) (type)(((u32)buf + (align - 1)) & ~(u32)(align - 1))
	#define MEM_ALIGN(buf, align) MEM_ALIGN_TYPE(buf, align, void*) 

	void ZeroMem(void* mem, u64 size);
	s64 SwapEndian(s64 SizeInBigEndian);
	s32 SwapEndian(s32 SizeInBigEndian);
	s16 SwapEndian(s16 SizeInBigEndian);
	u32 GetValueFromBitRange(u32 num, c8 bit1, c8 bit2);
}

#endif