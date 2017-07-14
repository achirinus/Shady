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
	f32 pow(f32 base, u32 pow);
	s32 pow(s32 base, u32 pow);
	u32 pow(u32 base, u32 pow);
	f32 clamp(f32 value, f32 upperLimit);
	f64 clamp(f64 value, f64 upperLimit);
	f32 ceil(f32 value);
	f64 ceil(f64 value);
	f32 floor(f32 value);
	f64 floor(f64 value);
	f32 round(f32 value);
	f64 round(f64 value);
	Vec3f normalize(const Vec3f& vec);
	f32 toRadians(f32 angle);
	s32 clamp(s32 value, s32 upperLimit);
}

#endif