#ifndef SHADY_MATH_H
#define SHADY_MATH_H

#include "Commons.h"
#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"
#include "Matrix3f.h"
#include "Matrix4f.h"
#include "math.h"
#include <cmath>

#define SH_PI 3.141592f
namespace Shady
{	
	#define cArrayCount(x) (sizeof(x) / sizeof(x[0]))

	template<typename T>
	T SafeRatio(T first, T second)
	{
		T result = static_cast<T>(0);
		if(second != 0) result = first / second;
		return result;
	}
	template<typename T>
	T Lerp(T first, T second, f32 alpha)
	{
		return (first + alpha * (second - first));
	}
	s32 Absolute(s32 a);
	f32 Absolute(f32 a);	
	f32 Pow(f32 base, u32 pow);
	s32 Pow(s32 base, u32 pow);
	u32 Pow(u32 base, u32 pow);
	u32 ClampHigh(u32 value, u32 upperLimit);
	f32 ClampHigh(f32 value, f32 upperLimit);
	f64 ClampHigh(f64 value, f64 upperLimit);
	s32 ClampHigh(s32 value, s32 upperLimit);
	s32 ClampLow(s32 value, s32 lowerLimit);
	f32 Clamp(f32 value, f32 lowerLimit, f32 upperLimit);
	
	s32 Clamp(s32 value, s32 lowerLimit, s32 upperLimit);
	f32 ClampToZero(f32 value);
	f32 Ceil(f32 value);
	f64 Ceil(f64 value);
	f32 Floor(f32 value);
	f64 Floor(f64 value);
	f32 Round(f32 value);
	f64 Round(f64 value);
	f32 Sin(f32 x);
	f32 Cos(f32 x);
	Vec3f Normalize(const Vec3f& vec);
	f32 ToRadians(f32 angle);
	void Transpose(f32* elem, u32 dim);
	f32 SquareRoot(f32 val);
	s32 Compare(f32 left, f32 right, f32 err);

	struct Rect
	{
		u32 Left;
		u32 Right;
		u32 Top;
		u32 Bottom;
	};

}

#endif