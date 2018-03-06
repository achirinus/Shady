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
			return *this;
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
					case IteratorPosition::RBEGIN
					{
						currentIndex = map->mPairs.Size() - 1;
					} break;
					case IteratorPosition::REND
					{
						currentIndex = -1;
					} break;
				}
			}

			b8 IsReverse() {return (position == IteratorPosition::RBEGIN) || (position == IteratorPosition::REND);}

			T& operator*()
			{
				SH_ASSERT(map->mPairs.size() > 0);
				return map->mPairs[currentIndex];
			}
			const T& operator*() const
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
				if(IsReverse())
				{
					temp.currentIndex -= offset;
				}
				else
				{
					temp.currentIndex += offset;
				}
				return temp;
			}
			MapIterator operator-(u32 offset)
			{
				MapIterator temp = *this;
				if(IsReverse())
				{
					temp.currentIndex += offset;
				}
				else
				{
					temp.currentIndex -= offset;
				}
				return temp;	
			}
			MapIterator& operator+=(u32 offset)
			{
				if(IsReverse())
				{
					currentIndex -= offset;
				}
				else
				{
					currentIndex += offset;
				}
				return *this;
			}
			MapIterator& operator-=(u32 offset)
			{
				if(IsReverse())
				{
					currentIndex -= offset;
				}
				else
				{
					currentIndex += offset;
				}
				return *this;
			}
			MapIterator operator++() 
			{
				MapIterator temp = *this;
				if(IsReverse())
				{
					temp.currentIndex--;
				}
				else
				{
					temp.currentIndex++;
				}
				return temp;
			}
			MapIterator operator++(int) 
			{
				if(IsReverse())
				{
					currentIndex--;
				}
				else
				{
					currentIndex++;
				}
				return *this;
			}
			MapIterator operator--()
			{
				MapIterator temp = *this;
				if(IsReverse())
				{
					temp.currentIndex++;
				}
				else
				{
					temp.currentIndex--;
				}
				return temp;
			}
			MapIterator operator--(int)
			{
				if(IsReverse())
				{
					currentIndex++;
				}
				else
				{
					currentIndex--;
				}
				return *this;
			}
			b8 operator==(const MapIterator& other) const
			{
				return ((map == other.map) && (currentIndex == other.currentIndex));
			}
			b8 operator!=(const MapIterator& other) const
			{
				return ((map != other.map) || (currentIndex != other.currentIndex));	
			}
			b8 operator>(const MapIterator& other) const
			{
				return currentIndex > other.currentIndex;
			}
			b8 operator>=(const MapIterator& other) const
			{
				return currentIndex >= other.currentIndex;
			}
			b8 operator<(const MapIterator& other) const
			{
				return currentIndex < other.currentIndex;
			}
			b8 operator<=(const MapIterator& other) const
			{
				return currentIndex <= other.currentIndex;
			}
		};
	public:
		MultiMap(): mPairs{} {}
		
		s32 GetKeyIndex(K key) const
		{
			for(u32 index = 0; index < mPairs.Size(); index++)
			{
				if(mPairs[index].key == key) return index;
			}
			return INVALID_MAP_KEY_INDEX;
		}

		s32 GetKeyByIndex(u32 index) const
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

		const V& operator[](K key) const
		{
			s32 keyIndex = GetKeyIndex(key);
			SH_ASSERT(keyIndex != INVALID_MAP_KEY_INDEX);
			return mPairs[keyIndex].value;
		}

		u32 Size() const
		{
			return mPairs.Size();
		}

		b8 HasKey(const K& key) const
		{
			b8 result = false;
			for(auto& pair : mPairs)
			{
				if(pair.key == key) result = true;
			}
			return result;
		}

		void Swap(MultiMap<K, V>& other)
		{
			mPairs.Swap(other.mPairs);
		}

		void Clear()
		{
			mPairs.Clear();
		}

		MapIterator<Pair> begin()
		{
			return MapIterator(this, IteratorPosition::BEGIN);
		}

		MapIterator<Pair> end()
		{
			return MapIterator(this, IteratorPosition::END);
		}

		const MapIterator<Pair> begin() const
		{
			return MapIterator(this, IteratorPosition::BEGIN);
		}

		const MapIterator<Pair> end() const
		{
			return MapIterator(this, IteratorPosition::END);
		}


		MapIterator<Pair> rbegin()
		{
			return MapIterator(this, IteratorPosition::RBEGIN);
		}

		MapIterator<Pair> rend()
		{
			return MapIterator(this, IteratorPosition::REND);
		}

		const MapIterator<Pair> rbegin() const
		{
			return MapIterator(this, IteratorPosition::RBEGIN);
		}

		const MapIterator<Pair> rend() const
		{
			return MapIterator(this, IteratorPosition::REND);
		}
	};
}

#endif