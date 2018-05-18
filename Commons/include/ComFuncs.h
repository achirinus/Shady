#ifndef SH_COM_FUNCS_H
#define SH_COM_FUNCS_H

#include "ShTypes.h"

namespace Shady
{
	#define SCAST(expr, type) static_cast<type>(expr)
	#define DCAST(expr, type) dynamic_cast<type>(expr)
	#define RCAST(expr, type) reinterpret_cast<type>(expr)
	#define CCAST(expr, type) const_cast<type>(expr)

	#define C_ARRAY_SIZE(Arr) sizeof(Arr) / sizeof(Arr[0])
	
	template<typename T>
	T&& Move(T& obj)
	{
		return static_cast<T&&>(obj);
	}

	template <typename T>
	void Swap(T& left, T& right)
	{
		T temp = left;
		left = right;
		right = temp;
	}

	template<typename T>
	void MoveSwap(T& left, T& right)
	{
		T temp = Move(left);
		left = Move(right);
		right = Move(temp);
	}

	//TODO decide on this.
	//-1 if Left is bigger, 1 if Right is bigger, 0 otherwise
	template<typename T>
	s32 Compare(const T& left, const T& right)
	{
		if(left < right) return 1;
		if(right < left) return -1;
		return 0;
	}

	template<typename T>
	void InsertionSort(T* arr, s32 count)
	{
		for (int i = 0; i < count; ++i)
		{
			T temp = Move(arr[i]);
			int j = i;
			for (;(j > 0) && (arr[j - 1] > temp); --j)
			{
				arr[j] = Move(arr[j-1]);
			}
			arr[j] = Move(temp);
		}
	}

	template<typename Iterator, typename Comp>
	void InsertionSort(Iterator begin, Iterator end, Comp comparator)
	{
		for (Iterator it = begin; it != end; ++it)
		{
			Iterator it2 = it;
			auto temp = Move(*it);
			for (; (it2 != begin) && (comparator(*(it2 - 1), temp) < 0); it2--)
			{
				*it2 = Move(*(it2 - 1));
			}
			*it2 = Move(temp);
		}
	}

	void ClearMem(void* mem, u64 size);

	b8 IsBitSet(u32 num, u8 bit);
	void SetBit(u32* num, u8 bit);
	void UnSetBit(u32* num, u8 bit);
	
	b8 IsBitSet(u64 num, u8 bit);
	void SetBit(u64* num, u8 bit);
	void UnSetBit(u64* num, u8 bit);

	u32 GetHighFrom64(u64 val);
	u32 GetLowFrom64(u64 val);

	
	b8 MemoryCompare(const c8* Left, const c8* Right, u32 Size);

	
	
#define MegaBytes(InBytes) (InBytes << 20)

	bool FlipFlop(b8& prev);
}

#endif