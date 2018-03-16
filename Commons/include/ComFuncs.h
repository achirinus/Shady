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

	//TODO decide on this.
	//-1 if Left is bigger, 1 if Right is bigger, 0 otherwise
	template<typename T>
	s32 Compare(const T& left, const T& right)
	{
		if(left > right) return -1;
		if(left < right) return 1;
		return 0;
	}

	void ClearMem(void* mem, u64 size);


	//template<typename Bytes, typename LeftShiftBits>
	//auto _BytesToMoreBytes() { return Bytes << LeftShiftBits; }
	
#define MegaBytes(InBytes) (InBytes << 20)

	bool FlipFlop(b8& prev);
}

#endif