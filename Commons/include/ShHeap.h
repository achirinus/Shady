#ifndef SH_HEAP_H
#define SH_HEAP_H

#include "ShArray.h"
#include <ShAssert.h>
#include <Commons.h>

namespace Shady
{
	template<typename T>
	bool HeapMinProc(const T& left, const T& right)
	{
		return left < right;
	}

	template<typename T>
	bool HeapMaxProc(const T& left, const T& right)
	{
		return left > right;
	}

	template<typename T>
	using HeapCompProc = bool (const T&, const T&);

	template<typename T, HeapCompProc<T>* HeapProc = HeapMinProc<T>>
	struct Heap
	{
		Array<T> mElem;
		u32 mSize;

		Heap():mSize{0}, mElem{} {}
		Heap(const Heap<T>& other): mSize{other.mSize}, mElem{other.mElem} {}

		Heap(T* buffer, u32 num): mSize{ 0 }, mElem{}
		{
			for (u32 i = 0; i < num; i++)
			{
				Insert(buffer[i]);
			}
		}

		Heap(Array<T> arr) : mSize{ 0 }, mElem{}
		{
			for (T& elem : arr)
			{
				Insert(elem);
			}
		}

		Heap(Heap<T>&& other)
		{
			mSize = other.mSize;
			mElem = Move(other.mElem);
		}
		Heap<T>& operator=(const Heap<T>& other)
		{
			mSize = other.mSize;
			mElem = other.mElem;
			return *this;
		}
		Heap<T>& operator=(Heap<T>&& other)
		{
			mSize = other.mSize;
			mElem = Move(other.mElem);
			return *this;
		}

		void Insert(const T& elem)
		{
			if (mSize == 0) mElem.Add(T{});
			mElem.Add(elem);
			mSize++;
			if (mSize > 1)
			{
				BubbleUp(mSize);
			}
		}

		T Get()
		{
			SH_ASSERT(mSize > 0);

			T Result = mElem[1];
			if (mSize > 1)
			{
				mElem.Swap(1, mSize);
				mElem.Remove(mSize--);
				BubbleDown(1);
			}
			
			return Move(Result);
		}

		void BubbleDown(u32 index)
		{
			while (true)
			{
				b8 Swapped = false;
				u32 LeftChildIndex = LeftIndex(index);
				u32 RightChildIndex = RightIndex(index);
				
				if (HasLeftChild(index))
				{
					if (HasRightChild(index))
					{
						if (HeapProc(mElem[LeftChildIndex], mElem[RightChildIndex]))
						{
							mElem.Swap(index, LeftChildIndex);
							index = LeftChildIndex;
							Swapped = true;
						}
						else
						{
							mElem.Swap(index, RightChildIndex);
							index = RightChildIndex;
							Swapped = true;
						}
					}
					else
					{
						if (HeapProc(mElem[LeftChildIndex], mElem[index]))
						{
							mElem.Swap(index, LeftChildIndex);
							index = LeftChildIndex;
							Swapped = true;
						}
					}
				}
				if(!Swapped) break;
			}
		}

		void BubbleUp(u32 index)
		{
			u32 Parent = ParentIndex(index);
			while (Parent)
			{
				if (HeapProc(mElem[index], mElem[Parent]))
				{
					mElem.Swap(Parent, index);
					index = Parent;
					Parent = ParentIndex(index);
				}
				else
				{
					break;
				}
			}
		}

		u32 Size()
		{
			return mSize;
		}

		b8 HasLeftChild(u32 index)
		{
			return mSize >= (2 * index);
		}
		b8 HasRightChild(u32 index)
		{
			return mSize >= ((2 * index) + 1);
		}

		b8 HasParent(u32 index)
		{
			return index / 2;
		}

		u32 LeftIndex(u32 index)
		{
			return 2 * index;
		}
		u32 RightIndex(u32 index)
		{
			return (2 * index) + 1;
		}
		u32 ParentIndex(u32 index)
		{
			return index / 2;
		}
	};

	template<typename T> using MaxHeap = Heap<T, HeapMaxProc<T>>;
	
	template<typename T> using MinHeap = Heap<T, HeapMinProc<T>>;
	
}
#endif