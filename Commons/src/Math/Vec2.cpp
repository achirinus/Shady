#include <Vec2.h>

namespace Shady
{
	
	template<typename T>
	Vec2<T>::Vec2(const Vec2<T>& other)
	{
		x = other.x;
		y = other.y;
	}

	template<typename T>
	Vec2<T>& Vec2<T>::operator=(const Vec2<T>& other)
	{
		x = other.x;
		y = other.y;
		return *this;
	}
	template <typename T>
	T Vec2<T>::dot(Vec2<T> other)
	{
		return x * other.x + y * other.y;
	}
	template <typename T>
	T Vec2<T>::dot(T x_, T y_)
	{
		return x * x_ + y * y_;
	}
	template <typename T>
	Vec2<T>& Vec2<T>::operator+=(const Vec2<T>& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}
	template <typename T>
	Vec2<T>& Vec2<T>::operator-=(const Vec2<T>& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}
	template <typename T>
	Vec2<T>& Vec2<T>::operator*=(const Vec2<T>& other)
	{
		x *= other.x;
		y *= other.y;
		return *this;
	}
	template <typename T>
	Vec2<T>& Vec2<T>::operator/=(const Vec2<T>& other)
	{
		x /= other.x;
		y /= other.y;
		return *this;
	}
	template <typename T>
	Vec2<T>& Vec2<T>::operator*=(T scalar)
	{
		x *= scalar;
		y *= scalar;
		return *this;
	}
	template <typename T>
	Vec2<T>& Vec2<T>::operator/=(T scalar)
	{
		x /= scalar;
		y /= scalar;
		return *this;
	}
	template <typename T>
	Vec2<T> Vec2<T>::operator+(const Vec2<T>& other)
	{
		return{ x + other.x, y + other.y };
	}
	template <typename T>
	Vec2<T> Vec2<T>::operator-(const Vec2<T>& other)
	{
		return{ x - other.x, y - other.y };
	}
	template <typename T>
	Vec2<T> Vec2<T>::operator*(const Vec2<T>& other)
	{
		return{ x * other.x, y * other.y };
	}
	template <typename T>
	Vec2<T> Vec2<T>::operator/(const Vec2<T>& other)
	{
		return{ x / other.x, y / other.y };
	}
	template <typename T>
	Vec2<T> Vec2<T>::operator*(T scalar)
	{
		return{ x * scalar, y * scalar };
	}
	template <typename T>
	Vec2<T> Vec2<T>::operator/(T scalar)
	{
		return{ x / scalar, y / scalar };
	}

	template <typename T>
	Vec2<T> operator*(T scalar, const Vec2<T>& vec)
	{
		return{ x * scalar, y * scalar };
	}

	template <typename T>
	T& Vec2<T>::operator[](int index)
	{
		return elem[index];
	}

	template struct Vec2<float>;
	template struct Vec2<int>;
}
