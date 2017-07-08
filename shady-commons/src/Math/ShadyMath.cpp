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

	float clamp(float value, float upperLimit)
	{
		return (value > upperLimit) ? upperLimit : value;
	}
	double clamp(double value, double upperLimit)
	{
		return (value > upperLimit) ? upperLimit : value;
	}
	s32 clamp(s32 value, s32 upperLimit)
	{
		return (value > upperLimit) ? upperLimit : value;
	}

	float clamp(float value, float lowerLimit, float upperLimit)
	{
		float result = value;
		if (result > upperLimit) result = upperLimit;
		if (result < lowerLimit) result = lowerLimit;
		return result;
	}
	double clamp(double value, double lowerLimit, double upperLimit)
	{
		double result = value;
		if (result > upperLimit) result = upperLimit;
		if (result < lowerLimit) result = lowerLimit;
		return result;
	}
	s32 clamp(s32 value, s32 lowerLimit, s32 upperLimit)
	{
		s32 result = value;
		if (result > upperLimit) result = upperLimit;
		if (result < lowerLimit) result = lowerLimit;
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