#ifndef SHADY_ARRAY_H
#define SHADY_ARRAY_H

#include "ShTypes.h"
#include "ShAssert.h"
#include <ShIterator.h>
#include <initializer_list>
#include <new>

namespace Shady
{
	#define SH_ARRAY_DEFAULT_SIZE 4

	template<typename T, u32 size = SH_ARRAY_DEFAULT_SIZE>
	class Array
	{
		T* mBuffer;
		u32 mBufferSize;
		u32 mNumOfElem;

		typedef Array<T> SType;
		typedef T EType;

	template<typename AType> class ArrayIterator;	
	public:
		Array(): mNumOfElem(0), mBuffer(0), mBufferSize(0)
		{
			mBufferSize = size;
			mBuffer = new T[mBufferSize];
		}
		explicit Array(u32 size): mBufferSize(size), mNumOfElem(0), mBuffer(nullptr)
		{
			if(mBufferSize) mBuffer = new T[mBufferSize];
		}
		Array(T* first, u32 num): mBufferSize{0}, mNumOfElem{0}, mBuffer{nullptr}
		{
			if(num && first)
			{
				mBufferSize = num;
				mNumOfElem = num;
				mBuffer = new T[mBufferSize];
				for(u32 i = 0; i < num; i++)
				{
					mBuffer[i] = first[i];
				}	
			}
		}
		Array(std::initializer_list<T> list)
		{
			mBufferSize = list.size();
			mNumOfElem = mBufferSize;
			mBuffer = new T[mBufferSize];
			auto it = list.begin();
			for(u32 i = 0; i < mNumOfElem; i++, it++)
			{
				mBuffer[i] = *it;
			}
		}

		Array(Array<T>&& other)
		{
			mBufferSize = other.mBufferSize;
			mNumOfElem = other.mNumOfElem;
			mBuffer = other.mBuffer;
			other.mBuffer = nullptr;
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

		Array<T>& operator=(Array<T>&& other)
		{
			if(mBuffer) delete[] mBuffer;

			mBufferSize = other.mBufferSize;
			mNumOfElem = other.mNumOfElem;
			mBuffer = other.mBuffer;
			other.mBuffer = nullptr;
			return *this;
		}

		Array<T>& operator=(const Array<T>& other)
		{
			if(&other == this) return *this;
			if(mBuffer) delete[] mBuffer;

			mBufferSize = other.mBufferSize;
			mNumOfElem = other.mNumOfElem;
			mBuffer = new T[mBufferSize];
			for(u32 i = 0; i < mBufferSize; i++)
			{
				mBuffer[i] = other.mBuffer[i];
			}
			return *this;
		}

		Array<T>& operator=(std::initializer_list<T> list)
		{
			if(mBuffer) delete[] mBuffer;
			mBufferSize = list.size();
			mNumOfElem = list.size();
			mBuffer = new T[mBufferSize];
			auto it = list.begin();
			for(u32 i = 0; i < mNumOfElem; i++, it++)
			{
				mBuffer[i] = *it;
			}

			return *this;
		}
		~Array()
		{
			if(mBuffer)
			{
				delete[] mBuffer;
			}
		}
		void Resize(u32 size)
		{
			if(mBufferSize)
			{
				T* tempBuffer = mBuffer;
				u32 tempSize = mBufferSize
				mBufferSize = size;
				mBuffer = new T[mBufferSize];
				u32 copyLimit = (mNumOfElem <= size) ? mNumOfElem : size;
				
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
		u32 Size() const
		{
			return mNumOfElem;
		}

		u32 Capacity() const
		{
			return mBufferSize;
		}

		void Add(const T& elem)
		{
			if(mBufferSize)
			{
				if(mNumOfElem >= mBufferSize)
				{
					T* tempBuffer = mBuffer;
					mBufferSize = mBufferSize * 2;
					mBuffer =  new T[mBufferSize];
					for(u32 index = 0; index < mNumOfElem; index++)
					{
						mBuffer[index] = tempBuffer[index];
					}
					mBuffer[mNumOfElem] = elem;
					delete[] tempBuffer;
				}
				else
				{
					mBuffer[mNumOfElem] = elem;
				}
			}
			else
			{
				mBufferSize = SH_ARRAY_DEFAULT_SIZE;
				mBuffer = new T[mBufferSize];
				mBuffer[mNumOfElem] = elem;
			}
			mNumOfElem++;
		}
		void Add(const Array<T>& other)
		{
			for(u32 i = 0; i < other.Size(); i++)
			{
				Add(other[i]);
			}
		}

		void Add(T* first, u32 num)
		{
			Array<T> temp{first, num};
			add(temp);
		}

		template<typename It>
		void Add(It begin, It end)
		{
			while(begin != end)
			{
				Add(*begin);
				begin++;
			}
		}

		template<typename ...Args>
		void Put(Args... vArgs)
		{
			if (mBufferSize)
			{
				if (mNumOfElem >= mBufferSize)
				{
					mBufferSize *= 2;
					T* temp = mBuffer;
					mBuffer = new T[mBufferSize];
					for (u32 i = 0; i < mNumOfElem; i++)
					{
						mBuffer[i] = temp[i];
					}
					new(&mBuffer[mNumOfElem]) T(vArgs...);

					delete[] temp;
				}
				else
				{
					new(&mBuffer[mNumOfElem]) T(vArgs...);
				}
			}
			else
			{
				mBufferSize = SH_ARRAY_DEFAULT_SIZE;
				mBuffer = new T[mBufferSize];
				new(&mBuffer[mNumOfElem]) T(vArgs...);
			}
			mNumOfElem++;
		}

		void Insert(T& elem, u32 index)
		{
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

		void Swap(Array<T>& other)
		{
			T* buff = mBuffer;
			u32 tSize = mBufferSize;
			u32 tNum = mNumOfElem;

			mBuffer = other.mBuffer;
			mBufferSize = other.mBufferSize;
			mNumOfElem = other.mNumOfElem;

			other.mBuffer = buff;
			other.mBufferSize = tSize;
			other.mNumOfElem = tNum;
		}

		b8 Swap(u32 firstIndex, u32 secondIndex)
		{
			b8 Result = false;
			u32 maxAvailableIndex = mBufferSize - 1;
			if (maxAvailableIndex < firstIndex) return Result;
			if (maxAvailableIndex < secondIndex) return Result;
			T Temp = Move(mBuffer[firstIndex]);
			mBuffer[firstIndex] = Move(mBuffer[secondIndex]);
			mBuffer[secondIndex] = Move(Temp);
			return Result;
		}

		Array<T>& RemoveFirst()
		{
			if(mNumOfElem)
			{
				mNumOfElem--;
				for(u32 i = 0; i < mNumOfElem; i++)
				{
					mBuffer[i] = mBuffer[i + 1];
				}
			}
			return *this;
		}

		Array<T>& RemoveLast()
		{
			mNumOfElem--;
			return *this;
		}

		T Remove(u32 index)
		{
			SH_ASSERT((index >= 0) && (index  < mNumOfElem));
			T Result = Move(mBuffer[index]);
			for(u32 firstIndex = index; firstIndex < mNumOfElem-1; firstIndex++)
			{
				mBuffer[firstIndex] = mBuffer[firstIndex + 1];
			}
			mNumOfElem--;
			return Result;
		}

		b8 Has(T& elem)
		{
			b8 result = false;
			for (T& itElem : *this)
			{
				if (elem == itElem)
				{
					result = true;
				}
			}
			return result;
		}

		s32 FindFirstIndex(T& elem)
		{
			s32 result = -1;
			for (u32 i = 0; i < mNumOfElem; i++)
			{
				if (elem == mBuffer[mNumOfElem])
				{
					result = i;
					break;
				}
			}
			return result;
		}

		s32 FindLastIndex(T& elem)
		{
			s32 result = -1;
			for (u32 i = mNumOfElem - 1; i <= 0; i--)
			{
				if (elem == mBuffer[mNumOfElem])
				{
					result = i;
					break;
				}
			}
			return result;
		}

		Array<T>& Fit()
		{
			if(mBufferSize > mNumOfElem)
			{
				T* temp = mBuffer;
				mBufferSize = mNumOfElem;
				mBuffer = new T[mBufferSize];
				for(u32 i = 0; i < mNumOfElem; i++)
				{
					mBuffer[i] = temp[i];
				}
				delete[] temp;
			}
			return *this;
		}

		Array<T>& Clear()
		{
			mNumOfElem = 0;
			return *this;
		}

		T& First()
		{
			return mBuffer[0];
		}

		T& Last()
		{
			return mBuffer[mNumOfElem-1];
		}

		T* begin()
		{
			return mBuffer;
		}

		T* end()
		{
			return mBuffer + mNumOfElem;
		}

		const T* begin() const
		{
			return mBuffer;
		}

		const T* end() const 
		{
			
			return mBuffer + mNumOfElem;
		}

		
		T& operator[](u32 index)
		{
			SH_ASSERT(index < mBufferSize);
			return mBuffer[index];
		}

		const T& operator[](u32 index) const
		{
			SH_ASSERT(index < mBufferSize);
			return mBuffer[index];
		}

		b8 operator>(const Array<T>& other)
		{
			return (mNumOfElem > other.mNumOfElem);
		}

		b8 operator<(const Array<T>& other)
		{
			return (mNumOfElem < other.mNumOfElem);
		}

		b8 operator>=(const Array<T>& other)
		{
			return (mNumOfElem >= other.mNumOfElem);
		}

		b8 operator<=(const Array<T>& other)
		{
			return (mNumOfElem <= other.mNumOfElem);
		}

		b8 operator==(const Array<T>& other)
		{
			b8 result = true;
			if(mNumOfElem != other.mNumOfElem) return false;

			for(u32 i = 0; i < mNumOfElem; i++)
			{
				if(mBuffer[i] != other.mBuffer[i])
				{
					result = false;
					break;
				}
			}
			return result;
		}

		b8 operator!=(const Array<T>& other)
		{
			b8 result = false;
			for(u32 i = 0; i < mNumOfElem; i++)
			{
				if(mBuffer[i] != other.mBuffer[i])
				{
					result = true;
					break;
				}
			}
			return result;
		}

		operator b8() const
		{
			b8 result = false;
			if(mBuffer)
			{
				if(mNumOfElem > 0) result = true;
			}
			
			return result;
		}

		T* GetPointer()
		{
			T* result = nullptr;
			if(mBufferSize > 0) result = &mBuffer[0];
			return result;
		}

		const T* GetPointer() const 
		{
			T* result = nullptr;
			if(mBufferSize > 0) result = &mBuffer[0];
			return result;
		}

	}; 
	
#undef SH_ARRAY_DEFAULT_SIZE	
}

#endif