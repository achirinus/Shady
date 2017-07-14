#ifndef MATRIX_4_F_H
#define MATRIX_4_F_H

#include "Vec4.h"
#include "Vec3.h"
#include "ShString.h"
#include "Commons.h"
namespace Shady
{
	struct Matrix4f
	{
		union
		{
			float elem[4 * 4];
			Vec4f rows[4];
		};
		Matrix4f();
		Matrix4f(float diag);
		Matrix4f(const Matrix4f& other);
		Matrix4f(Vec4f firstRow, Vec4f secondRow, Vec4f thirdRow, Vec4f fourthRow);
		Matrix4f& operator=(const Matrix4f& other);
		Vec4f& operator[](int index);
		Matrix4f operator*(const Matrix4f& other) const;
		Matrix4f& operator*=(const Matrix4f& other);
		Vec4f operator*(Vec4f vec);
		static Matrix4f identity();
		static Matrix4f translation(float x, float y, float z);
		static Matrix4f translation(const Vec3f& vec);
		static Matrix4f scale(f32 scalar);
		static Matrix4f distort(const Vec3f&);
		static Matrix4f ortho(float left, float right, float bottom, float top, float near, float far);
		static Matrix4f lookAt(const Vec3f& eye, const Vec3f& center, const Vec3f& up);
		static Matrix4f perspectiveFov(float fov, float aspectRatio, float zNear, float zFar);
		Matrix4f& rotX(f32 rad);
		Matrix4f& rotY(f32 rad);
		Matrix4f& rotZ(f32 rad);

		String toString();
	};
}

#endif
