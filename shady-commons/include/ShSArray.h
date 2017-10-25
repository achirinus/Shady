#ifndef SH_S_ARRAY_H
#define SH_S_ARRAY_H

namespace Shady
{

	template<typename T, u32 size>
	class SArray
	{
		T elem[size];

	public:
		T& operator[](u32 index)
		{
			return elem[index];
		}

		T* Data()
		{
			return &elem[0];
		}

		const T* Data() const 
		{
			return &elem[0];
		}
	};

}

#endif