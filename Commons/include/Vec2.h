#pragma once

namespace Shady
{

	template <typename T>
	struct Vec2
	{
		union
		{
			T elem[2];
			struct
			{
				T x, y;
			};
			struct
			{
				T u, v;
			};

		};

		Vec2() = default;
		Vec2(T x_, T y_)
		{
			x = x_;
			y = y_;
		}
		Vec2(const Vec2<T>& other);
		T dot(Vec2<T> other);
		T dot(T x_, T y_);
		Vec2<T>& operator=(const Vec2<T>& other);
		Vec2<T>& operator+=(const Vec2<T>& other);
		Vec2<T>& operator-=(const Vec2<T>& other);
		Vec2<T>& operator*=(const Vec2<T>& other);
		Vec2<T>& operator/=(const Vec2<T>& other);
		Vec2<T> operator+(const Vec2<T>& other);
		Vec2<T> operator-(const Vec2<T>& other);
		Vec2<T> operator*(const Vec2<T>& other);
		Vec2<T> operator/(const Vec2<T>& other);
		Vec2<T> operator*(T scalar);
		Vec2<T> operator/(T scalar);
		Vec2<T>& operator*=(T scalar);
		Vec2<T>& operator/=(T scalar);
		T& operator[](int index);
	};
	template <typename T>
	Vec2<T> operator*(T scalar, const Vec2<T>& other);

	typedef Vec2<float> Vec2f;
	typedef Vec2<int> Vec2i;
}
