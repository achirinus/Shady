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

		MapPair() = default;
		MapPair(const K& k, const V& v)
		{
			key = k;
			value = v;
		}
		MapPair(const MapPair& other)
		{
			key = other.key;
			value = other.value;
		}
		MapPair(MapPair&& other)
		{
			key = other.key;
			value = other.value;	
		}
		MapPair& operator=(const MapPair& other)
		{
			key = other.key;
			value = other.value;	
		}
	};

	template<typename K, typename V>
	class MultiMap
	{
		typedef	MapPair<K, V> Pair; 
	
		Array<Pair> mPairs;
		
		template <typename T>
		struct MapIterator 
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
						currentIndex = map->mPairs.Size();
					} break;
				}
			}

			T& operator*()
			{
				SH_ASSERT(map->mPairs.size() > 0);
				return map->mPairs[currentIndex];
			}
			MapIterator& operator=(const MapIterator& other)
			{
				map = other.map;
				currentIndex = other.currentIndex;
				return *this;
			}
			MapIterator operator+(u32 offset)
			{
				MapIterator temp = *this;
				temp.currentIndex += offset;
				temp.currentIndex = Shady::clamp(temp.currentIndex, map->mPairs.Size());
				return temp;
			}
			MapIterator operator-(u32 offset)
			{
				MapIterator temp = *this;
				temp.currentIndex -= offset;
				if(temp.currentIndex < 0) temp.currentIndex = map->mPairs.Size();
				return temp;	
			}
			MapIterator& operator+=(u32 offset)
			{
				currentIndex += offset;
				currentIndex = Shady::clamp(currentIndex, map->mPairs.Size());
			}
			MapIterator& operator-=(u32 offset)
			{
				currentIndex -= offset;
				if(currentIndex < 0) currentIndex = map->mPairs.Size();
			}
			MapIterator operator++() 
			{
				MapIterator temp = *this;
				currentIndex++;
				return temp;
			}
			MapIterator operator++(int) 
			{
				currentIndex++;
			}
			MapIterator operator--()
			{
				MapIterator temp = *this;
				currentIndex--;
				return temp;
			}
			MapIterator operator--(int)
			{
				currentIndex--;
			}
			b8 operator==(const MapIterator& other)
			{
				return ((map == other.map) && (currentIndex == other.currentIndex));
			}
			b8 operator!=(const MapIterator& other) 
			{
				return ((map != other.map) || (currentIndex != other.currentIndex));	
			}
			b8 operator>(const MapIterator& other)
			{
				return currentIndex > other.currentIndex;
			}
			b8 operator>=(const MapIterator& other)
			{
				return currentIndex >= other.currentIndex;
			}
			b8 operator<(const MapIterator& other)
			{
				return currentIndex < other.currentIndex;
			}
			b8 operator<=(const MapIterator& other)
			{
				return currentIndex <= other.currentIndex;
			}

		};
	public:
		MultiMap(): mPairs{} {}
		
		s32 GetKeyIndex(K key)
		{
			for(u32 index = 0; index < mPairs.Size(); index++)
			{
				if(mPairs[index].key == key) return index;
			}
			return INVALID_MAP_KEY_INDEX;
		}

		s32 GetKeyByIndex(u32 index)
		{
			SH_ASSERT(index < mPairs.Size());
			return mPairs[index].key;
		}
		
		void Add(K key, V value)
		{
			mPairs.Put(key, value);
		}

		void Remove(K key)
		{
			s32 keyIndex = getKeyIndex(key);
			if(keyIndex != INVALID_MAP_KEY_INDEX)
			{
				mPairs.Remove(keyIndex);
			}
		}

		V* GetValue(K key)
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
			s32 keyIndex = GetKeyIndex(key);
			SH_ASSERT(keyIndex != INVALID_MAP_KEY_INDEX);
			return mPairs[keyIndex].value;
		}

		u32 Size()
		{
			return mPairs.Size();
		}

		b8 HasKey(const K& key)
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