#include "ComFuncs.h"

namespace Shady
{
	u64 operator "" _KB(u64 in)
	{
		return in << 10;
	}

	u64 operator "" _MB(u64 in)
	{
		return in << 20;
	}
	
	u64 operator "" _GB(u64 in)
	{
		return in << 30;
	}
}