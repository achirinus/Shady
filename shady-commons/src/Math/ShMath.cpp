#include <ShMath.h>
#include "ComFuncs.h"

namespace Shady
{

	s32 absolute(s32 a)
	{
		if (a < 0)
		{
			return a = -1 * a;
		}
		return a;	
	}

	f32 absolute(f32 a)
	{
		if (a < 0)
		{
			return a = -1 * a;
		}
		return a;	
	}

	f32 toRadians(f32 angle)
	{
		return (angle * SH_PI)/180;
	}

	f32 clamp(f32 value, f32 upperLimit)
	{
		return (value > upperLimit) ? upperLimit : value;
	}
	f64 clamp(f64 value, f64 upperLimit)
	{
		return (value > upperLimit) ? upperLimit : value;
	}
	s32 clamp(s32 value, s32 upperLimit)
	{
		return (value > upperLimit) ? upperLimit : value;
	}

	f32 clamp(f32 value, f32 lowerLimit, f32 upperLimit)
	{
		f32 result = value;
		if (result > upperLimit) result = upperLimit;
		if (result < lowerLimit) result = lowerLimit;
		return result;
	}
	f64 clamp(f64 value, f64 lowerLimit, f64 upperLimit)
	{
		f64 result = value;
		if (result > upperLimit) result = upperLimit;
		if (result < lowerLimit) result = lowerLimit;
		return result;
	}

	f32 clampToZero(f32 value)
	{	
		if(value < 0.0f) value = 0.0f;
		return value;
	}
	s32 clamp(s32 value, s32 lowerLimit, s32 upperLimit)
	{
		s32 result = value;
		if (result > upperLimit) result = upperLimit;
		if (result < lowerLimit) result = lowerLimit;
		return result;
	}

	f32 pow(f32 base, u32 pow)
	{
		if (pow == 0) return 1.0f;
		f32 result = base;
		for(u32 index = 0; index < pow; index++)
		{
			result *= base;
		}
		return result;
	}
	s32 pow(s32 base, u32 pow)
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
	u32 pow(u32 base, u32 pow)
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

	f32 ceil(f32 value)
	{
		value += 1.0f;
		s32 iValue = (s32)value;
		return (f32)iValue;
	}
	f64 ceil(f64 value)
	{
		value += 1.0;
		s32 iValue = (s32)value;
		return (f64)iValue;
	}
	f32 round(f32 value)
	{
		value += 0.50f;
		s32 iValue = (s32)value;
		return (f32)iValue;
	}
	f64 round(f64 value)
	{
		value += 0.50;
		s32 iValue = (s32)value;
		return (f64)iValue;
	}

	Vec3f normalize(const Vec3f& vec)
	{
		Vec3f result;
		f32 len = (f32)sqrt(absolute(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2)));
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

	f32 floor(f32 value)
	{
		s32 iValue = (s32)value;
		return (f32)iValue;
	}
	
	f64 floor(f64 value)
	{
		s32 iValue = (s32)value;
		return (f64)iValue;
	}

	void transpose(f32* elem, u32 dim)
	{
		for(u32 i = 0; i < dim; i++)
		{
			for(u32 j = i + 1; j < dim; j++)
			{
				swap(elem[i + j * dim], elem[j + i * dim]);
			}			
		}
	}
}