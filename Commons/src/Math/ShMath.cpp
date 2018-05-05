#include <ShMath.h>
#include "ComFuncs.h"
//#include "CPUInstructionSet.h"

namespace Shady
{

	f32 Get01FromRange(s32 pos, s32 min, s32 max)
	{
		f32 Sum = (f32)(min + max);
		f32 Result = SafeRatio((f32)pos, Sum);
		return Result;
	}

	s32 Absolute(s32 a)
	{
		if (a < 0)
		{
			return a = -1 * a;
		}
		return a;	
	}

	f32 Absolute(f32 a)
	{
		if (a < 0)
		{
			return a = -1 * a;
		}
		return a;	
	}

	f32 ToRadians(f32 angle)
	{
		return (angle * SH_PI)/180;
	}

	f32 ClampHigh(f32 value, f32 upperLimit)
	{
		return (value > upperLimit) ? upperLimit : value;
	}
	f64 ClampHigh(f64 value, f64 upperLimit)
	{
		return (value > upperLimit) ? upperLimit : value;
	}
	s32 ClampHigh(s32 value, s32 upperLimit)
	{
		return (value > upperLimit) ? upperLimit : value;
	}

	u32 ClampHigh(u32 value, u32 upperLimit)
	{
		return (value > upperLimit) ? upperLimit : value;
	}

	s32 ClampLow(s32 value, s32 lowerLimit)
	{
		s32 result = value;
		if (result < lowerLimit) result = lowerLimit;
		return result;
	}

	f32 ClampToZero(f32 value)
	{	
		if(value < 0.0f) value = 0.0f;
		return value;
	}

	f32 Pow(f32 base, u32 pow)
	{
		if (pow == 0) return 1.0f;
		f32 result = base;
		for(u32 index = 0; index < pow; index++)
		{
			result *= base;
		}
		return result;
	}
	s32 Pow(s32 base, u32 pow)
	{
		if(base == 0) return 0;
		if (pow == 0) return 1;
		f32 result = base;
		for(u32 index = 0; index < pow; index++)
		{
			result *= base;
		}
		return result;
	}
	u32 Pow(u32 base, u32 pow)
	{
		if(base == 0) return 0;
		if (pow == 0) return 1;
		f32 result = base;
		for(u32 index = 0; index < pow; index++)
		{
			result *= base;
		}
		return result;	
	}

	f32 Ceil(f32 value)
	{
		value += 1.0f;
		s32 iValue = (s32)value;
		return (f32)iValue;
	}
	f64 Ceil(f64 value)
	{
		value += 1.0;
		s32 iValue = (s32)value;
		return (f64)iValue;
	}
	f32 Round(f32 value)
	{
		value += 0.50f;
		s32 iValue = (s32)value;
		return (f32)iValue;
	}
	f64 Round(f64 value)
	{
		value += 0.50;
		s32 iValue = (s32)value;
		return (f64)iValue;
	}

	Vec3f Normalize(const Vec3f& vec)
	{
		Vec3f result;
		f32 len = (f32)sqrt(Absolute(Pow(vec.x, 2) + Pow(vec.y, 2) + Pow(vec.z, 2)));
		if(len != 0)
		{
			result = Vec3f(vec.x/len, vec.y/len, vec.z/len);	
		} 
		else
		{
			result = Vec3f();
		}
		
		return result;
	}

	f32 Floor(f32 value)
	{
		s32 iValue = (s32)value;
		return (f32)iValue;
	}
	
	f64 Floor(f64 value)
	{
		s32 iValue = (s32)value;
		return (f64)iValue;
	}

	void Transpose(f32* elem, u32 dim)
	{
		for(u32 i = 0; i < dim; i++)
		{
			for(u32 j = i + 1; j < dim; j++)
			{
				Swap(elem[i + j * dim], elem[j + i * dim]);
			}			
		}
	}

	f32 SquareRoot(f32 val)
	{
		f32 result = _mm_cvtss_f32(_mm_sqrt_ss(_mm_set_ss(val)));
		return result;
	}

	s32 Compare(f32 left, f32 right, f32 err)
	{
		s32 result = 0;
		f32 dif =left-right;
		f32 abs = Absolute(dif);
		if(abs > err)
		{
			result = ((s32)dif & (1 << 31)) ? 1 : -1;
		}
		return result;
	}

	f32 Sin(f32 x)
	{
		return sin(x);
	}
	f32 Cos(f32 x)
	{
		return cos(x);
	}
}