#pragma once

#include "Vec2.h"
namespace Shady
{

	template <typename T>
	struct Vec3
	{
		union
		{
			T elem[3];
			struct
			{
				T x, y, z;
			};
			struct
			{
				T u, v, w;
			};

			struct
			{
				T r, g, b;
			};

			Vec2<T> xy;
			Vec2<T> uv;
			Vec2<T> rg;
		};

		Vec3() = default;
		Vec3(T x_, T y_, T z_);
		Vec3(Vec2<T> xy_, T z_)
		{
			x = xy_.x;
			y = xy_.y;
			z = z_;
		}
		Vec3(const Vec3<T>& other);
		T dot(Vec3<T> other);
		T dot(T x_, T y_, T z_);
		Vec3<T> cross(Vec3<T> other);
		Vec3<T> cross(T x_, T y_, T z_);
		Vec3<T>& operator=(const Vec3<T>& other);
		Vec3<T>& operator+=(Vec3<T> other);
		Vec3<T>& operator-=(Vec3<T> other);
		Vec3<T>& operator*=(Vec3<T> other);
		Vec3<T>& operator/=(Vec3<T> other);
		Vec3<T> operator+(Vec3<T> other);
		Vec3<T> operator-(Vec3<T> other);
		Vec3<T> operator*(Vec3<T> other);
		Vec3<T> operator/(Vec3<T> other);
		Vec3<T> operator*(T scalar);
		Vec3<T> operator/(T scalar);
		Vec3<T>& operator*=(T scalar);
		Vec3<T>& operator/=(T scalar);
		T& operator[](int index);
	};
	template <typename T>
	Vec3<T> operator*(T scalar, Vec3<T> vec);

	
	typedef Vec3<float> Vec3f;
	typedef Vec3<int> Vec3i;
}
