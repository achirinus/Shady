#ifndef SHADY_ARRAY_H
#define SHADY_ARRAY_H

#include <Commons.h>
#include <ShIterator.h>
#include <initializer_list>

namespace Shady
{
	template<typename T>
	class Array
	{
		T* mBuffer;
		u32 mBufferSize;
		u32 mNumOfElem;

		template <typename T>
		class ArrayIterator : public Shady::Iterator<ArrayIterator<T>, T>
		{
			friend Array;
			Array<T>* array;
			u32 currentIndex;
			ArrayIterator(Array* arr, IteratorPosition pos = IteratorPosition::BEGIN):
			 array(arr)
			{
				switch(pos)
				{
					case IteratorPosition::BEGIN:
					{
						currentIndex = 0;
					}break;
					case IteratorPosition::END:
					{
						currentIndex = arr->mNumOfElem;
					}break;
				}
			}
		public:
			T& operator*()
			{
				SH_ASSERT(array);
				SH_ASSERT((currentIndex >=0) && (currentIndex < array->mNumOfElem));
				return array->mBuffer[currentIndex];
			}

			ArrayIterator& operator=(const ArrayIterator& other)
			{
				array = other.array;
				currentIndex = other.currentIndex;
				return *this;
			}
			
			ArrayIterator operator+(u32 offset)
			{
				ArrayIterator temp = *this;
				temp.currentIndex = currentIndex + offset;
				return temp; 
			} 

			ArrayIterator operator-(u32 offset)
			{
				ArrayIterator temp = *this;
				temp.currentIndex = currentIndex - offset;
				return temp; 
			}

			ArrayIterator& operator+=(u32 offset)
			{
				SH_ASSERT(array);
				SH_ASSERT((currentIndex + offset) < array->mNumOfElem);
				currentIndex += offset;
				return *this;
			} 

			ArrayIterator& operator-=(u32 offset)
			{
				SH_ASSERT(array);
				SH_ASSERT((currentIndex - offset) >= 0);
				currentIndex -= offset;
				return *this;
			} 

			ArrayIterator operator++()
			{
				SH_ASSERT(currentIndex < array->mNumOfElem);
				ArrayIterator temp = *this;
				currentIndex++;
				return temp;
			}
			ArrayIterator operator++(int)
			{
				SH_ASSERT(array);
				SH_ASSERT(currentIndex < array->mNumOfElem);
				++currentIndex;
				return *this;
			}

			ArrayIterator operator--()
			{
				SH_ASSERT(array);
				SH_ASSERT(currentIndex > 0);
				ArrayIterator temp = *this;
				currentIndex++;
				return temp;
			}

			ArrayIterator operator--(int)
			{
				SH_ASSERT(array);
				SH_ASSERT(currentIndex > 0);
				++currentIndex;
				return *this;
			}

			b8 operator==(const ArrayIterator& other)
			{
				return (array == other.array) && (currentIndex == other.currentIndex);
			}
			b8 operator!=(const ArrayIterator& other)
			{
				return (array != other.array) || (currentIndex != other.currentIndex);
			}
			
		};
					
	public:
		Array(): mNumOfElem(0), mBuffer(0), mBufferSize(0)
		{

		}
		Array(u32 size): mBufferSize(size), mNumOfElem(0)
		{
			mBuffer = new T[mBufferSize];
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
		void add(const Array<T>& other)
		{
			for(u32 i = 0; i < other.size(); i++)
			{
				add(other[i]);
			}
		}
		void add(T* first, u32 num)
		{
			Array<T> temp{first, num};
			add(temp);
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

		ArrayIterator<T> begin()
		{
			return ArrayIterator<T>(this, IteratorPosition::BEGIN);
		}

		ArrayIterator<T> end()
		{
			return ArrayIterator<T>(this, IteratorPosition::END);
		}

		T& operator[](s32 index)
		{
			SH_ASSERT((index >= 0) && (index < mNumOfElem));
			return mBuffer[index];
		}

		const T& operator[](s32 index) const
		{
			SH_ASSERT((index >= 0) && (index < mNumOfElem));
			return mBuffer[index];
		}

		T* getPointer()
		{
			T* result = nullptr;
			if(mBufferSize > 0) result = &mBuffer[0];
			return result;
		}

		const T* getPointer() const 
		{
			T* result = nullptr;
			if(mBufferSize > 0) result = &mBuffer[0];
			return restult;
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

	};
}

#endif