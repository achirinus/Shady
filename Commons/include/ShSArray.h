#ifndef SH_S_ARRAY_H
#define SH_S_ARRAY_H

#include <initializer_list>

namespace Shady
{

	template<typename T, u32 size>
	class SArray
	{
		T mElem[size];
	public:
		SArray() = default;

		SArray(std::initializer_list<T> list)
		{
			auto it = list.begin();
			for(u32 sz = 0; sz < size; sz++, it++)
			{
				if(sz >= list.size()) break;
				
				mElem[sz] = *it;
			}
		}

		T& operator[](u32 index)
		{
			SH_ASSERT((index >= 0) && (index < size));
			return mElem[index];
		}

		T* Data()
		{
			return &mElem[0];
		}

		const T* Data() const 
		{
			return &mElem[0];
		}

		u32 Size() const
		{
			return size;
		}
	};

}

#endif