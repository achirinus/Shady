#ifndef SH_SHHASHTABLE_H 
#define SH_SHHASHTABLE_H

#include "ShArray.h"

namespace Shady
{
	template<typename T>
	using HashTableFuncType = u32(*)(const T&);

#define DEFAULT_HASH_TABLE_SIZE 256

	template<typename T>
	struct HashTable
	{
		HashTableFuncType<T> HashFunction;
		Array<List<T>> Elements;

		HashTable(): Elements { DEFAULT_HASH_TABLE_SIZE }, HashFunction{ 0 } {}
		explicit HashTable(u32 size,  HashTableFuncType<T> func = 0): Elements { size }, HashFunction{ func } {}

		b8 Add(T elem)
		{
			if (!HashFunction) return false;

			u32 RawHash = HashFunction(elem);
			Elements[RawHash % Elements.Capacity()].AddFront(elem);
			return true;
		}

		void SetHashFunc(HashTableFuncType<T> newFunc)
		{
			HashFunction = newFunc;
		}
		
	};
}


#undef DEFAULT_HASH_TABLE_SIZE
#endif
