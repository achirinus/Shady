#include "ShRandom.h"
#include "ShMath.h"

namespace Shady
{
	Random::Random(u32 seed) : Seed{ seed }
	{
		if (!Seed) Seed = __rdtsc();
	}


	u32 Random::Get(u32 minValue, u32 maxValue)
	{
		u32 Temp = Seed;
		Temp ^= Temp << 13;
		Temp ^= Temp >> 17;
		Temp ^= Temp << 5;
		Seed = Temp;
		return (Temp % maxValue) + minValue;
	}
}