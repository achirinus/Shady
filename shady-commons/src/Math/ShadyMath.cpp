#include <ShadyMath.h>

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

	float ceil(float value)
	{
		value += 1.0f;
		int iValue = (int)value;
		return (float)iValue;
	}
	double ceil(double value)
	{
		value += 1.0;
		int iValue = (int)value;
		return (double)iValue;
	}
	float round(float value)
	{
		value += 0.50f;
		int iValue = (int)value;
		return (float)iValue;
	}
	double round(double value)
	{
		value += 0.50;
		int iValue = (int)value;
		return (double)iValue;
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

	float floor(float value)
	{
		int iValue = (int)value;
		return (float)iValue;
	}
	double floor(double value)
	{
		int iValue = (int)value;
		return (double)iValue;
	}
}