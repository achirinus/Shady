#ifndef SHSTACK_H 
#define SHSTACK_H

#include <Commons.h>
#include <cstring>

namespace Shady
{
#define SH_DEFAULT_STACK_SIZE 32
#define SH_INVALID_STACK_INDEX -1

	template<typename T>
	class  Stack
	{
		T* mBuffer;
		u32 mBufferSize;
		s32 mIndex;

		void GrowBuffer(u32 size)
		{
			mBufferSize = size;
			T* newBuffer = new T[mBufferSize];
			memcpy(newBuffer, mBuffer, (mIndex + 1) * sizeof(T));
			delete[] mBuffer;
			mBuffer = newBuffer;
		}
		
	public:
		Stack() 
		{
			mBufferSize = SH_DEFAULT_STACK_SIZE;
			mBuffer = new T[mBufferSize];
			mIndex = SH_INVALID_STACK_INDEX;
		}

		Stack(const Stack<T>& other)
		{
			mBufferSize = other.mBufferSize;
			mBuffer = new T[mBufferSize];
			mIndex = other.mIndex;
			for (int i = 0; i <= mIndex; i++)
			{
				mBuffer[i] = other.mBuffer[i];
			}
		}

		Stack<T>& operator=(const Stack<T>& other)
		{
			Clear();
			mBufferSize = other.mBufferSize;
			mBuffer = new T[mBufferSize];
			mIndex = other.mIndex;
			for (int i = 0; i <= mIndex; i++)
			{
				mBuffer[i] = other.mBuffer[i];
			}
			return *this;
		}

		Stack(Stack<T>&& other)
		{
			mBuffer = other.mBuffer;
			mBufferSize = other.mBufferSize;
			mIndex = other.mIndex;

			other.mBuffer = 0;
		}

		Stack<T>& operator=(Stack<T>&& other)
		{
			mBuffer = other.mBuffer;
			mBufferSize = other.mBufferSize;
			mIndex = other.mIndex;

			other.mBuffer = 0;
			return *this;
		}

		~Stack()
		{
			Clear();
		}

		explicit Stack(u32 size)
		{
			mBufferSize = size;
			mBuffer = new T[mBufferSize];
			mIndex = SH_INVALID_STACK_INDEX;
		}

		void Push(const T& elem)
		{
			mIndex++;
			if (mBufferSize <= mIndex)
			{
				GrowBuffer(mBufferSize * 2);
			}
			mBuffer[mIndex] = elem;
		}

		T Pop()
		{
			SH_ASSERT(mIndex > SH_INVALID_STACK_INDEX);
			return mBuffer[mIndex--];
		}

		b8 Pop(T* OutElem)
		{
			if (!OutElem) return false;
			if (!mIndex) return false;

			*OutElem = mBuffer[mIndex--];

			return true;
		}

		T& Peek()
		{
			SH_ASSERT(mIndex > SH_INVALID_STACK_INDEX);
			return mBuffer[mIndex];
		}

		u32 Size() const
		{
			return mIndex + 1;
		}

		void Clear()
		{
			if (mBuffer) delete[] mBuffer;
		}

		T* begin()
		{
			return mBuffer;
		}

		T* end()
		{
			return mBuffer + Size();
		}
	};


#undef SH_INVALID_STACK_INDEX
#undef SH_DEFAULT_STACK_SIZE
}

#endif