#ifndef SH_BITSET_H
#define SH_BITSET_H

#include "Commons.h"
#include "ShArray.h"
#include "StringUtils.h"
#include "ShString.h"

//Bits are 0 indexed!

namespace Shady
{
	template<u32 TSize = 32>
	class Bitset
	{
		u32 mElem[((TSize % 32)== 0) ? (TSize / 32) : (TSize / 32) + 1];
	public:

		Bitset() { ClearMem(mElem, sizeof(mElem));}
		Bitset(u32 bits) 
		{ 
			ClearMem(mElem, sizeof(mElem));
			mElem[0] = bits;
		}
		Bitset(const c8* str)
		{
			ClearMem(mElem, sizeof(mElem));
			u32 ind = StrLength(str);
			u32 bits = 0;
			if(ind)
			{
				do
				{
					ind--;
					c8 temp = str[ind];
					if(bits > TSize) break;
					if(temp == '1') Set(bits++, true);
					if(temp == '0') Set(bits++, false);		
				} while(ind);
			}
		}

		void Set(u32 bit, b8 val = true)
		{
			u32 elemIndex = bit / 32;
			u32 bitIndex = bit % 32;
			if(val)
			{
				mElem[elemIndex] = mElem[elemIndex] | (1 << bitIndex);
			}
			else
			{
				mElem[elemIndex] = mElem[elemIndex] & ~(1 << bitIndex);
			}
		}

		b8 Test(u32 bit) const 
		{
			u32 elemIndex = bit / 32;
			u32 bitIndex = bit % 32;
			return (mElem[elemIndex] & (1 << bitIndex));
		}

		String ToString() const
		{
			c8 ch[TSize + 1];
			u32 ind = TSize - 1;
			u32 chInd = 0;
			do
			{
				b8 bitVal = Test(ind);
				ch[chInd++] = bitVal? '1' : '0';
			}while(ind--);
			ch[TSize] = '\0';
			return String(ch);
		}

		b8 Any() const
		{
			b8 result = false;
			for(u32 ind = 0; i < TSize; ind++)
			{
				if(Test(ind))
				{
					result = true;
					break;
				}
			}
			return result;
		}

		b8 All() const
		{
			b8 result = true;
			for(u32 ind = 0; ind < TSize; ind++)
			{
				if(!Test(ind))
				{
					result = false;
					break;
				}
			}
			return result;
		}

		b8 None() const
		{
			b8 result = true;
			for(u32 ind = 0; ind < TSize; ind++)
			{
				if(Test(ind))
				{
					result = false;
					break;
				}
			}
			return result;
		}

		u32 Count() const
		{
			u32 result = 0;
			for(u32 ind = 0; ind < TSize; ind++)
			{
				if(Test(ind)) result++;
			}
			return result;
		}

		u32 Size() const
		{
			return TSize;
		}

		void Reset() 
		{
			ClearMem(mElem, sizeof(mElem));
		}

		void Flip()
		{
			for(u32 leftInd = 0; leftInd < TSize/2; leftInd++)
			{
				u32 rightInd = (TSize - 1) - leftInd;
				b8 valLeft = Test(leftInd);
				b8 valRight = Test(rightInd);
				Set(leftInd, valRight);
				Set(rightInd, valLeft);
			}
		}

		b8 operator[](u32 ind)
		{
			return Test(ind);
		}


	};
}

#endif