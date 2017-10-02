#ifndef MATRIX_3_F_H
#define MATRIX_3_F_H

#include <Vec3.h>

namespace Shady
{

	struct Matrix3f
	{

		union
		{
			float elem[3 * 3];
			Vec3f rows[3];
		};
		Matrix3f();
		Matrix3f(const Matrix3f& other);
		Matrix3f(Vec3f firstRow, Vec3f secondRow, Vec3f thirdRow);
		Matrix3f& operator=(const Matrix3f& other);
		Vec3f& operator[](int index);
		Matrix3f operator*(Matrix3f& other);
		Vec3f operator*(Vec3f vec);
		
		static Matrix3f identity();

		void transpose();
	};
	
}

#endif
