#ifndef SH_MEM_UTILS_H
#define SH_MEM_UTILS_H
#include "ShTypes.h"

namespace Shady
{
	#define ARRAY_COUNT(arr) (sizeof(arr)/ sizeof(arr[0]))
	
	void zeroMemory(void* mem, u64 size);
}

#endif