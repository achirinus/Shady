#ifndef SHADY_ARRAY_H
#define SHADY_ARRAY_H

#include <Commons.h>

namespace Shady
{
	template<typename T>
	class Array
	{
		T* mBuffer;
		u32 mBufferSize;
		u32 mNumOfElem;
	public:
		Array(): mNumOfElem(0), mBuffer(0), mBufferSize(0)
		{

		}
		Array(u32 size): mBufferSize(size), mNumOfElem(0)
		{
			mBuffer = new T[mBufferSize];
		}
		Array(Array<T>&& other)
		{
			mBufferSize = other.mBufferSize;
			mNumOfElem = other.mNumOfElem;
			mBuffer = other.mBuffer;
			other.mBuffer = 0;
		}
		Array(const Array<T>& other)
		{
			mBuffer = new T[other.mBufferSize];
			mBufferSize = other.mBufferSize;
			mNumOfElem = other.mNumOfElem;
			for(u32 i = 0; i < mBufferSize; i++)
			{
				mBuffer[i] = other.mBuffer[i];
			}
		}
		~Array()
		{
			if(mBuffer)
			{
				delete[] mBuffer;
			}
		}
		void resize(u32 size)
		{
			if(!mBufferSize)
			{
				T* tempBuffer = mBuffer;
				u32 tempSize = mBufferSize
				mBufferSize = size;
				mBuffer = new T[mBufferSize];
				u32 copyLimit = 0;
				if(mNumOfElem <= size) copyLimit = mNumOfElem;
				if(mNumOfElem > size) copyLimit = size;
				for(u32 i; i < copyLimit; i++)
				{
					mBuffer[i] = tempBuffer[i];
				}
				mNumOfElem = copyLimit;
				delete[] tempBuffer;
			}
			else
			{
				mBuffer = new T[size];
			}
		}
		u32 size() const
		{
			return mNumOfElem;
		}
		void add(T elem)
		{
			mNumOfElem++;
			if(mBuffer)
			{

				if(mNumOfElem >= mBufferSize)
				{
					T* tempBuffer = mBuffer;
					mBufferSize = mNumOfElem * 2;
					mBuffer =  new T[mBufferSize];
					for(u32 index = 0; index < mNumOfElem - 1; index++)
					{
						mBuffer[index] = tempBuffer[index];
					}
					mBuffer[mNumOfElem - 1] = elem;
					delete[] tempBuffer;
				}
				else
				{
					mBuffer[mNumOfElem -1] = elem;
				}
			}
			else
			{
				mBufferSize = mNumOfElem * 2;
				mBuffer =  new T[mBufferSize];
				mBuffer[mNumOfElem-1] = elem;
			}
		}
		void insert(T elem, u32 index)
		{
			SH_ASSERT(index > 0);
			mNumOfElem++;
			if(mNumOfElem >= mBufferSize)
			{
				T* tempBuffer = mBuffer;
				mBufferSize = mBufferSize * 2;
				mBuffer =  new T[mBufferSize];
				if(index < mNumOfElem)
				{
					for(u32 firstIndex = 0; firstIndex < index; firstIndex++)
					{
						mBuffer[firstIndex] = tempBuffer[firstIndex];
					}
					mBuffer[index] = elem;
					for(u32 secondIndex = index+1; secondIndex < mNumOfElem; secondIndex++)
					{
						mBuffer[secondIndex] = tempBuffer[secondIndex - 1];
					}
				}
				else
				{
					for(u32 firstIndex = 0; firstIndex < mNumOfElem - 1; firstIndex++)
					{
						mBuffer[firstIndex] = tempBuffer[firstIndex];
					}
					mBuffer[mNumOfElem - 1] = elem;

				}
				delete[] tempBuffer;
			}
			else
			{
				if(index < mNumOfElem)
				{
					for(u32 firstIndex = mNumOfElem-1; firstIndex > index; firstIndex--)
					{
						mBuffer[firstIndex + 1] = mBuffer[firstIndex];
					}
					mBuffer[index] = elem;
				}
				else
				{
					mBuffer[index];
				}

			}
		}
		void remove()
		{
			mNumOfElem--;
		}
		void remove(u32 index)
		{
			SH_ASSERT((index >= 0) && (index  < mNumOfElem));
			for(u32 firstIndex = index; firstIndex < mNumOfElem-1; firstIndex++)
			{
				mBuffer[firstIndex] = mBuffer[firstIndex + 1];
			}
			mNumOfElem--;
		}

		T& operator[](s32 index)
		{
			SH_ASSERT((index >= 0) && (index < mNumOfElem));
			return mBuffer[index];
		}
		Array<T>& operator=(const Array<T>& other)
		{
			Array<T> result{other};
			return result;
		}
	};
}

#endif