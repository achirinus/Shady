#include "Commons.h"
#include <stdarg.h>
#include <Windows.h>
#include "StringUtils.h"

namespace Shady
{
	u64 operator "" _KB(u64 in)
	{
		return in * 1024;
	}

	u64 operator "" _MB(u64 in)
	{
		return in * 1024 * 1024;
	}
	
	u64 operator "" _GB(u64 in)
	{
		return in * 1024 * 1024 * 1024;
	}
}

