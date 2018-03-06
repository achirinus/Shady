#ifndef SH_MEM_UTILS_H
#define SH_MEM_UTILS_H
#include "ShTypes.h"

namespace Shady
{
	#define ARRAY_COUNT(arr) (sizeof(arr)/ sizeof(arr[0]))
	
	void ZeroMem(void* mem, u64 size);
	s64 SwapEndian(s64 SizeInBigEndian);
	s32 SwapEndian(s32 SizeInBigEndian);
	s16 SwapEndian(s16 SizeInBigEndian);
}

#endif