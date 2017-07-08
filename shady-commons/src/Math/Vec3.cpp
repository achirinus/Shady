#include <Vec3.h>

namespace Shady
{
	template<typename T>
	Vec3<T>::Vec3(T x_, T y_, T z_)
	{
		x = x_;
		y = y_;
		z = z_;
	}
	template<typename T>
	Vec3<T>::Vec3(const Vec3<T>& other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
	}

	template<typename T>
	Vec3<T>& Vec3<T>::operator=(const Vec3<T>& other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
		return *this;
	}
	template <typename T>
	T Vec3<T>::dot(Vec3<T> other)
	{
		return x * other.x + y * other.y + z * other.z;
	}
	template <typename T>
	T Vec3<T>::dot(T x_, T y_, T z_)
	{
		return x * x_ + y * y_ + z * z_;
	}

	template <typename T>
	Vec3<T> Vec3<T>::cross(T x_, T y_, T z_)
	{
		return {(y * z_ - y_* z) , (z * x_ - x * z_), (x * y_ - x_ * y)};
	}

	template <typename T>
	Vec3<T> Vec3<T>::cross(Vec3<T> other)
	{
		return { (y * other.z - other.y* z) , 
				(z * other.x - x * other.z),
				(x * other.y - other.x * y) };
	}

	template <typename T>
	Vec3<T>& Vec3<T>::operator+=(Vec3<T> other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}
	template <typename T>
	Vec3<T>& Vec3<T>::operator-=(Vec3<T> other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}
	template <typename T>
	Vec3<T>& Vec3<T>::operator*=(Vec3<T> other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;
		return *this;
	}
	template <typename T>
	Vec3<T>& Vec3<T>::operator/=(Vec3<T> other)
	{
		x /= other.x;
		y /= other.y;
		z /= other.z;
		return *this;
	}
	template <typename T>
	Vec3<T>& Vec3<T>::operator*=(T scalar)
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;
		return *this;
	}
	template <typename T>
	Vec3<T>& Vec3<T>::operator/=(T scalar)
	{
		x /= scalar;
		y /= scalar;
		z /= scalar;
		return *this;
	}
	template <typename T>
	Vec3<T> Vec3<T>::operator+(Vec3<T> other)
	{
		return{ x + other.x, y + other.y, z + other.z };
	}
	template <typename T>
	Vec3<T> Vec3<T>::operator-(Vec3<T> other)
	{
		return{ x - other.x, y - other.y, z - other.z };
	}
	template <typename T>
	Vec3<T> Vec3<T>::operator*(Vec3<T> other)
	{
		return{ x * other.x, y * other.y, z * other.z };
	}
	template <typename T>
	Vec3<T> Vec3<T>::operator/(Vec3<T> other)
	{
		return{ x / other.x, y / other.y, z / other.z };
	}
	template <typename T>
	Vec3<T> Vec3<T>::operator*(T scalar)
	{
		return{ x * scalar, y * scalar, z * scalar };
	}
	template <typename T>
	Vec3<T> Vec3<T>::operator/(T scalar)
	{
		return{ x / scalar, y / scalar, z / scalar };
	}

	template <typename T>
	Vec3<T> operator*(T scalar, Vec3<T> vec)
	{
		return{ x * scalar, y * scalar, z * scalar };
	}
	
	template <typename T>
	T& Vec3<T>::operator[](int index)
	{
		return elem[index];
	}

	template struct Vec3<float>;
	template struct Vec3<int>;
}