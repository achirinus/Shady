#ifndef SH_MAP_H
#define SH_MAP_H

#include "ShArray.h"
#include "ShAssert.h"
#include "ShIterator.h"
#include "ShMath.h"

#define INVALID_MAP_KEY_INDEX -1

namespace Shady
{
	template <typename K, typename V>
	struct MapPair
	{
		K key;
		V value;
	};

	template<typename K, typename V>
	class MultiMap
	{
		typedef	MapPair<K, V> Pair; 
	
		Array<Pair> mPairs;
		
		template <typename T>
		struct MapIterator : public Shady::Iterator<MapIterator<T>, T>
		{
			friend MultiMap;

			MultiMap* map;
			u32 currentIndex;

			MapIterator(MultiMap* m, IteratorPosition pos): map{m}
			{
				switch(pos)
				{
					case IteratorPosition::BEGIN
					{
						currentIndex = 0;
					} break;
					case IteratorPosition::END
					{
						currentIndex = map->mPairs.size();
					} break;
				}
			}

			virtual T& operator*()
			{
				SH_ASSERT(map->mPairs.size() > 0);
				return map->mPairs[currentIndex];
			}
			virtual MapIterator& operator=(const MapIterator& other)
			{
				map = other.map;
				currentIndex = other.currentIndex;
				return *this;
			}
			virtual MapIterator operator+(u32 offset)
			{
				MapIterator temp = *this;
				temp.currentIndex += offset;
				temp.currentIndex = Shady::clamp(temp.currentIndex, map->mPairs.size());
				return temp;
			}
			virtual MapIterator operator-(u32 offset)
			{
				MapIterator temp = *this;
				temp.currentIndex -= offset;
				if(temp.currentIndex < 0) temp.currentIndex = map->mPairs.size();
				return temp;	
			}
			virtual MapIterator& operator+=(u32 offset)
			{
				currentIndex += offset;
				currentIndex = Shady::clamp(currentIndex, map->mPairs.size());
			}
			virtual MapIterator& operator-=(u32 offset)
			{
				currentIndex -= offset;
				if(currentIndex < 0) currentIndex = map->mPairs.size();
			}
			virtual MapIterator operator++() 
			{
				MapIterator temp = *this;
				currentIndex++;
				return temp;
			}
			virtual MapIterator operator++(int) 
			{
				currentIndex++;
			}
			virtual MapIterator operator--()
			{
				MapIterator temp = *this;
				currentIndex--;
				return temp;
			}
			virtual MapIterator operator--(int)
			{
				currentIndex--;
			}
			virtual b8 operator==(const MapIterator& other)
			{
				return ((map == other.map) && (currentIndex == other.currentIndex));
			}
			virtual b8 operator!=(const MapIterator& other) 
			{
				return ((map != other.map) || (currentIndex != other.currentIndex));	
			}
		};
	public:
		MultiMap(): mPairs{} {}
		
		s32 getKeyIndex(K key)
		{
			for(u32 index = 0; index < mPairs.size(); index++)
			{
				if(mPairs[index].key == key) return index;
			}
			return INVALID_MAP_KEY_INDEX;
		}

		s32 getKeyByIndex(u32 index)
		{
			SH_ASSERT(index < mPairs.size());
			return mPairs[index].key;
		}
		
		void add(K key, V value)
		{
			mPairs.add({key, value});
		}

		void remove(K key)
		{
			s32 keyIndex = getKeyIndex(key);
			if(keyIndex != INVALID_MAP_KEY_INDEX)
			{
				mPairs.remove(keyIndex);
			}
		}

		V* getValue(K key)
		{
			V* result = nullptr;
			s32 keyIndex = getKeyIndex(key);
			if(keyIndex != INVALID_MAP_KEY_INDEX)
			{
				result = &mPairs[keyIndex].value;
			}
			return result;	
		}

		V& operator[](K key)
		{
			s32 keyIndex = getKeyIndex(key);
			SH_ASSERT(keyIndex != INVALID_MAP_KEY_INDEX);
			return mPairs[keyIndex].value;
		}

		u32 size()
		{
			return mPairs.size();
		}

		b8 hasKey(const K& key)
		{
			b8 result = false;
			for(auto& pair : mPairs)
			{
				if(pair.key == key) result = true;
			}
			return result;
		}

		MapIterator<Pair> begin()
		{
			return MapIterator(this, IteratorPosition::BEGIN);
		}

		MapIterator<Pair> end()
		{
			return MapIterator(this, IteratorPosition::END);
		}
	};
}

#endif