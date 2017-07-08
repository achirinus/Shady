#ifndef MATRIX_4_F_H
#define MATRIX_4_F_H

#include "Vec4.h"
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
		Matrix4f operator*(Matrix4f& other);
		Vec4f operator*(Vec4f vec);
		static Matrix4f identity();
		static Matrix4f translation(float x, float y, float z);
	};
}

#endif
