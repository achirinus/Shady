#ifndef SH_COM_FUNCS_H
#define SH_COM_FUNCS_H

#include "ShTypes.h"

namespace Shady
{
	#define SCAST(expr, type) static_cast<type>(expr)
	#define DCAST(expr, type) dynamic_cast<type>(expr)
	#define RCAST(expr, type) reinterpret_cast<type>(expr)
	#define CCAST(expr, type) const_cast<type>(expr)
	
	template <typename T>
	void Swap(T& left, T& right)
	{
		T temp = left;
		left = right;
		right = temp;
	}

	template<typename T>
	T&& Move(T& obj)
	{
		return static_cast<T&&>(obj);
	}

	void ClearMem(void* mem, u64 size);

	u64 operator "" _KB(u64 in);
	u64 operator "" _MB(u64 in);
	u64 operator "" _GB(u64 in);
	
}

#endif