#ifndef SHADY_MATH_H
#define SHADY_MATH_H

#include "Commons.h"
#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"
#include "Matrix3f.h"
#include "Matrix4f.h"
#include "math.h"

#define SH_PI 3.141592f
namespace Shady
{	
	s32 absolute(s32 a);
	f32 absolute(f32 a);	
	
	template<typename T>
	T safeRatio(T first, T second)
	{
		T result = static_cast<T>(0);
		if(second != 0) result = first / second;
		return result;
	}
	f32 pow(f32 base, u32 pow);
	s32 pow(s32 base, u32 pow);
	u32 pow(u32 base, u32 pow);
	f32 clamp(f32 value, f32 upperLimit);
	f64 clamp(f64 value, f64 upperLimit);
	s32 clamp(s32 value, s32 upperLimit);
	f32 clampToZero(f32 value);
	f32 ceil(f32 value);
	f64 ceil(f64 value);
	f32 floor(f32 value);
	f64 floor(f64 value);
	f32 round(f32 value);
	f64 round(f64 value);
	Vec3f normalize(const Vec3f& vec);
	f32 toRadians(f32 angle);
	void transpose(f32* elem, u32 dim);
}

#endif