#pragma once

#include "Vec3.h"

namespace Shady
{
	template <typename T>
	struct Vec4
	{
		union
		{
			T elem[4];
			struct
			{
				T x, y, z, w;
			};
		
			struct
			{
				T r, g, b, a;
			};
			Vec2<T> xy;
			Vec2<T> rg;
			Vec3<T> xyz;
			Vec3<T> rgb;
		};
		Vec4() = default;
		
		Vec4(T x_, T y_, T z_, T w_)
		{
			x = x_;
			y = y_;
			z = z_;
			w = w_;
		}

		
		Vec4(Vec3<T> xyz_, T w_)
		{
			x = xyz_.x;
			y = xyz_.y;
			z = xyz_.z;
			w = w_;
		}

		
		Vec4(Vec2<T> xy_, T z_, T w_)
		{
			x = xy_.x;
			y = xy_.y;
			z = z_;
			w = w_;
		}
		
		Vec4(Vec2<T> xy_, Vec2<T> zw_)
		{
			x = xy_.x;
			y = xy_.y;
			z = zw_.x;
			w = zw_.y;
		}
		Vec4(const Vec4<T>& other);
		T dot(Vec4<T> other);
		T dot(T x_, T y_, T z_, T w_);
		Vec4<T>& operator=(const Vec4<T>& other);
		Vec4<T>& operator+=(Vec4<T> other);
		Vec4<T>& operator-=(Vec4<T> other);
		Vec4<T>& operator*=(Vec4<T> other);
		Vec4<T>& operator/=(Vec4<T> other);
		Vec4<T> operator+(Vec4<T> other);
		Vec4<T> operator-(Vec4<T> other);
		Vec4<T> operator*(Vec4<T> other);
		Vec4<T> operator/(Vec4<T> other);
		Vec4<T> operator*(T scalar);
		Vec4<T> operator/(T scalar);
		Vec4<T>& operator*=(T scalar);
		Vec4<T>& operator/=(T scalar);
		T& operator[](int index);
	};
	template <typename T>
	Vec4<T> operator*(T scalar, Vec4<T> vec);

	typedef Vec4<float> Vec4f;
	typedef Vec4<int> Vec4i;
	
}