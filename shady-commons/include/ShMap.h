#ifndef SH_MAP_H
#define SH_MAP_H

#include "ShArray.h"
#include "ShadyAssert.h"


#define INVALID_MAP_KEY_INDEX -1

namespace Shady
{
	template<typename K, typename E>
	class Map
	{
	private:
		Array<K> mKeys;
		Array<E> mElem;

	public:
		Map(): mKeys(), mElem() {}
		
		s32 getKeyIndex(K key)
		{
			for(u32 index = 0; index < mKeys.size(); index++)
			{
				if(mKeys[index] == key) return index;
			}
			return INVALID_MAP_KEY_INDEX;
		}

		s32 getKeyByIndex(u32 index)
		{
			SH_ASSERT(index < mKeys.size());
			return mKeys[index];
		}
		
		void add(K key, E elem)
		{
			mKeys.add(key);
			mElem.add(elem);
		}

		void remove(K key)
		{
			s32 keyIndex = getKeyIndex(key);
			if(keyIndex != INVALID_MAP_KEY_INDEX)
			{
				mKeys.remove(keyIndex);
				mElem.remove(keyIndex);
			}
		}

		E& operator[](K key)
		{
			s32 keyIndex = getKeyIndex(key);
			SH_ASSERT(keyIndex != INVALID_MAP_KEY_INDEX);
			return mElem[keyIndex];
		}

		u32 size()
		{
			return mKeys.size();
		}
	};
}

#endif