#ifndef SH_SHRANDOM_H 
#define SH_SHRANDOM_H

#include "Commons.h"

namespace Shady
{
	struct Random
	{
		u32 Seed;

		explicit Random(u32 seed = 0);

		u32 Get(u32 minValue = 0, u32 maxValue = U32_MAX);
	};
}

#endif
