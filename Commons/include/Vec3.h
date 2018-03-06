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
		Vec3(T x_, T y_, T z_)
		{
			x = x_;
			y = y_;
			z = z_;
		}
		Vec3(Vec2<T> xy_, T z_)
		{
			x = xy_.x;
			y = xy_.y;
			z = z_;
		}
		Vec3(const Vec3<T>& other)
		{
			x = other.x;
			y = other.y;
			z = other.z;
		}
		T dot(const Vec3<T>& other)
		{
			return x * other.x + y * other.y + z * other.z;
		}
		T dot(T x_, T y_, T z_)
		{
			return x * x_ + y * y_ + z * z_;
		}
		Vec3<T> cross(const Vec3<T>& other)
		{
			return { (y * other.z - other.y* z) , 
				(z * other.x - x * other.z),
				(x * other.y - other.x * y) };
		}
		Vec3<T> cross(T x_, T y_, T z_)
		{
			return {(y * z_ - y_* z) , (z * x_ - x * z_), (x * y_ - x_ * y)};
		}
		Vec3<T>& operator=(const Vec3<T>& other)
		{
			x = other.x;
			y = other.y;
			z = other.z;
			return *this;
		}
		Vec3<T>& operator+=(const Vec3<T>& other)
		{
			x += other.x;
			y += other.y;
			z += other.z;
			return *this;
		}
		Vec3<T>& operator-=(const Vec3<T>& other)
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;
			return *this;
		}
		Vec3<T>& operator*=(const Vec3<T>& other)
		{
			x *= other.x;
			y *= other.y;
			z *= other.z;
			return *this;
		}
		Vec3<T>& operator/=(const Vec3<T>& other)
		{
			x /= other.x;
			y /= other.y;
			z /= other.z;
			return *this;
		}
		Vec3<T> operator+(const Vec3<T>& other) const
		{
			return{ x + other.x, y + other.y, z + other.z };
		}
		Vec3<T> operator-(const Vec3<T>& other) const 
		{
			return{ x - other.x, y - other.y, z - other.z };
		}
		Vec3<T> operator*(const Vec3<T>& other) const 
		{
			return{ x * other.x, y * other.y, z * other.z };
		}
		Vec3<T> operator/(const Vec3<T>& other) const 
		{
			return{ x / other.x, y / other.y, z / other.z };
		}
		Vec3<T> operator*(T scalar) const 
		{
			return{ x * scalar, y * scalar, z * scalar };
		}
		Vec3<T> operator/(T scalar) const 
		{
			return{ x / scalar, y / scalar, z / scalar };
		}

		Vec3<T> operator-()
		{
			return {-x, -y, -z};
		}
		Vec3<T>& operator*=(T scalar)
		{
			x *= scalar;
			y *= scalar;
			z *= scalar;
			return *this;
		}
		Vec3<T>& operator/=(T scalar)
		{
			x /= scalar;
			y /= scalar;
			z /= scalar;
			return *this;
		}
		
		T& operator[](int index)
		{
			return elem[index];
		}
	};
	template <typename T>
	Vec3<T> operator*(T scalar, Vec3<T> vec)
	{
		return{ vec.x * scalar, vec.y * scalar, vec.z * scalar };
	}

	
	typedef Vec3<float> Vec3f;
	typedef Vec3<int> Vec3i;
}
