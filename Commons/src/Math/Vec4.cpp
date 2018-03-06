#include "../include/Vec4.h"

namespace Shady
{
	template<typename T>
	Vec4<T>::Vec4(const Vec4<T>& other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
		w = other.w;
	}

	template<typename T>
	Vec4<T>& Vec4<T>::operator=(const Vec4<T>& other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
		w = other.w;
		return *this;
	}

	template <typename T>
	T Vec4<T>::dot(Vec4<T> other)
	{
		return x * other.x + y * other.y + z * other.z + w * other.w;
	}
	template <typename T>
	T Vec4<T>::dot(T x_, T y_, T z_, T w_)
	{
		return x * x_ + y * y_ + z * z_ + w * w_;
	}
	template <typename T>
	Vec4<T>& Vec4<T>::operator+=(Vec4<T> other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		w += other.w;
		return *this;
	}
	template <typename T>
	Vec4<T>& Vec4<T>::operator-=(Vec4<T> other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		w -= other.w;
		return *this;
	}
	template <typename T>
	Vec4<T>& Vec4<T>::operator*=(Vec4<T> other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;
		w *= other.w;
		return *this;
	}
	template <typename T>
	Vec4<T>& Vec4<T>::operator/=(Vec4<T> other)
	{
		x /= other.x;
		y /= other.y;
		z /= other.z;
		w /= other.w;
		return *this;
	}
	template <typename T>
	Vec4<T>& Vec4<T>::operator*=(T scalar)
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;
		w *= scalar;
		return *this;
	}
	template <typename T>
	Vec4<T>& Vec4<T>::operator/=(T scalar)
	{
		x /= scalar;
		y /= scalar;
		z /= scalar;
		w /= scalar;
		return *this;
	}
	template <typename T>
	Vec4<T> Vec4<T>::operator+(Vec4<T> other)
	{
		return { x + other.x, y + other.y, z + other.z, w + other.w };
	}
	template <typename T>
	Vec4<T> Vec4<T>::operator-(Vec4<T> other)
	{
		return{ x - other.x, y - other.y, z - other.z, w - other.w };
	}
	template <typename T>
	Vec4<T> Vec4<T>::operator*(Vec4<T> other)
	{
		return{ x * other.x, y * other.y, z * other.z, w * other.w };
	}
	template <typename T>
	Vec4<T> Vec4<T>::operator/(Vec4<T> other)
	{
		return{ x / other.x, y / other.y, z / other.z, w / other.w };
	}
	template <typename T>
	Vec4<T> Vec4<T>::operator*(T scalar)
	{
		return{ x * scalar, y * scalar, z * scalar, w * scalar };
	}
	template <typename T>
	Vec4<T> Vec4<T>::operator/(T scalar)
	{
		return{ x / scalar, y / scalar, z / scalar, w / scalar };
	}

	template <typename T>
	Vec4<T> operator*(T scalar, Vec4<T> vec)
	{
		return{ x * scalar, y * scalar, z * scalar, w * scalar };
	}

	template <typename T>
	T& Vec4<T>::operator[](int index)
	{
		return elem[index];
	}


	template struct Vec4<float>;
	template struct Vec4<int>;
}