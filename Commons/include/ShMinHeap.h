#ifndef SH_MIN_HEAP_H
#define SH_MIN_HEAP_H

#include <ShArray.h>
#include <ShAssert.h>
#include <Commons.h>

namespace Shady
{
	template<typename T>
	struct MinHeap
	{
		Array<T> mElem;
		u32 mSize;

		MinHeap():mSize{0}, mElem{} {}
		MinHeap(const MinHeap<T>& other): mSize{other.mSize}, mElem{other.mElem} {}
		MinHeap(MinHeap<T>&& other)
		{
			mSize = other.mSize;
			mElem = Move(other.mElem);
		}
		MinHeap<T>& operator=(const MinHeap<T>& other)
		{
			mSize = other.mSize;
			mElem = other.mElem;
			return *this;
		}
		MinHeap<T>& operator=(MinHeap<T>&& other)
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

		T GetMin()
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
						if (mElem[LeftChildIndex] < mElem[RightChildIndex])
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
						if (mElem[LeftChildIndex] < mElem[index])
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
				if (mElem[Parent] > mElem[index])
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
}
#endif