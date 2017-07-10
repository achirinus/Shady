#include "Matrix4f.h"
#include <math.h>
#define MAT4_DIM 4

namespace Shady
{

	Matrix4f::Matrix4f()
	{
		for (int i = 0; i < MAT4_DIM * MAT4_DIM; i++)
		{
			elem[i] = 0;
		}
	}
	Matrix4f::Matrix4f(Vec4f firstRow, Vec4f secondRow, Vec4f thirdRow, Vec4f fourthRow)
	{
		rows[0] = firstRow;
		rows[1] = secondRow;
		rows[2] = thirdRow;
		rows[3] = fourthRow;
	}

	Matrix4f::Matrix4f(float diag)
	{
		zeroMemory(elem, sizeof(f32) * 16);
		rows[0][0] = diag;
		rows[1][1] = diag;
		rows[2][2] = diag;
		rows[3][3] = diag;
	}

	Matrix4f::Matrix4f(const Matrix4f& other)
	{
		for (int i = 0; i < MAT4_DIM * MAT4_DIM; i++)
		{
			elem[i] = other.elem[i];
		}
	}

	Matrix4f& Matrix4f::operator=(const Matrix4f& other)
	{
		for (int i = 0; i < MAT4_DIM * MAT4_DIM; i++)
		{
			elem[i] = other.elem[i];
		}
		return *this;
	}
	Vec4f& Matrix4f::operator[](int index)
	{
		return rows[index];
	}
	Matrix4f Matrix4f::operator*(const Matrix4f& other) const
	{
		Matrix4f result;
		for (int i = 0; i < MAT4_DIM; i++)
		{
			for (int j = 0; j < MAT4_DIM; j++)
			{
				float sum = 0;
				for (int k = 0; k < MAT4_DIM; k++)
				{
					sum += elem[k + MAT4_DIM * i] * other.elem[j + MAT4_DIM * k];
				}
				result.elem[j + MAT4_DIM * i] = sum;
			}
		}
		return result;
	}

	Matrix4f& Matrix4f::operator*=(const Matrix4f& other)
	{
		*this = other * (*this);
		return *this;
	}

	Matrix4f Matrix4f::ortho(float left, float right, float bottom, float top, float nier, float phar) 
	{
		//Had to rename near and far due to some stupid keywords
		Matrix4f result(1);
		result[0][0] = 2 / (right - left);
		result[1][1] = 2 / (top - bottom);
		result[2][2] = - 2 / (phar - nier);
		result[3][0] = -(right + left) / (right - left);
		result[3][1] = -(top + bottom) / (top - bottom);
		result[3][2] = -(phar + nier) / (phar - nier);
		return result;
	}

	Matrix4f& Matrix4f::rotX(f32 rad)
	{
		f32 ca = (f32)cos(rad);
		f32 sa = (f32)sin(rad);
		(*this) = (*this) * Matrix4f{{1, 0, 0, 0},
							{0, ca, -sa, 0},
							{0, sa, ca, 0},
							{0, 0, 0, 1}};
		return *this;
	}

	Matrix4f& Matrix4f::rotY(f32 rad)
	{
		f32 ca = (f32)cos(rad);
		f32 sa = (f32)sin(rad);
		(*this) = (*this) * Matrix4f{{ca, 0, sa, 0},
							{0, 1, 0, 0},
							{-sa, 0, ca, 0},
							{0, 0, 0, 1}};
		return *this;
	}

	Matrix4f& Matrix4f::rotZ(f32 rad)
	{
		f32 ca = (f32)cos(rad);
		f32 sa = (f32)sin(rad);
		(*this) = (*this) * Matrix4f{{ca, -sa, 0, 0},
							{sa, ca, 0, 0},
							{0, 0, 1, 0},
							{0, 0, 0, 1}};
		return *this;
	}

	Matrix4f Matrix4f::translation(float x, float y, float z)
	{
		Matrix4f result = Matrix4f::identity();
		result[3][0] = x;
		result[3][1] = y;
		result[3][2] = z;
		return result;
	}

	Matrix4f Matrix4f::translation(const Vec3f& vec)
	{
		Matrix4f result = Matrix4f::identity();
		result[3][0] = vec.x;
		result[3][1] = vec.y;
		result[3][2] = vec.z;
		return result;
	}

	Matrix4f Matrix4f::scale(f32 scalar)
	{
		Matrix4f result{};
		result[0][0] = scalar;
		result[1][1] = scalar;
		result[2][2] = scalar;
		result[3][3] = 1.0f;
		return result;
	}

	Matrix4f Matrix4f::distort(const Vec3f& axis)
	{
		Matrix4f result{};

		result[0][0] = axis.x;
		result[1][1] = axis.y;
		result[2][2] = axis.z;
		result[3][3] = 1;

		return result;
	}

	Matrix4f Matrix4f::identity()
	{
		Matrix4f result{};
		for (int i = 0; i < MAT4_DIM; i++)
		{
			result.elem[i + MAT4_DIM * i] = 1.0f;
		}
		return result;
	}

	Matrix4f Matrix4f::perspectiveFov(float fov, float aspectRatio, float zNear, float zFar)
	{
		float q = 1.0 / tan(toRadians(0.5f * fov));
		float a = q / aspectRatio;
		float b = (zNear + zFar) / (zNear - zFar);
		float c = (2.0f * zNear * zFar) / (zNear - zFar);

		Matrix4f result{1};
		result.elem[0 + 0 * 4] = a;
		result.elem[1 + 1 * 4] = q;
		result.elem[2 + 2 * 4] = b;
		result.elem[3 + 2 * 4] = -1.0f;
		result.elem[2 + 3 * 4] = c;
		return result;
	}

	Vec4f Matrix4f::operator*(Vec4f vec)
	{
		Vec4f result;
		for (int i = 0; i < MAT4_DIM; i++)
		{
			float sum = 0;
			for (int j = 0; j < MAT4_DIM; j++)
			{
				sum += elem[j + MAT4_DIM * i] * vec[j];
			}
			result[i] = sum;
		}
		return result;
	}

	String Matrix4f::toString()
	{
		
		c8 all[256];
		sprintf_s(all, 256, "-----------\n%f  %f  %f  %f\n%f  %f  %f  %f\n%f  %f  %f  %f\n%f  %f  %f  %f\n-----------\n",
							elem[0], elem[1], elem[2], elem[3], elem[4], elem[5], elem[6], elem[7],
							elem[8], elem[9], elem[10], elem[11], elem[12], elem[13], elem[14], elem[15]);
		String result(all);
		return result;
	}
}