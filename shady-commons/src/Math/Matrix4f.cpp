#include "Matrix4f.h"

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
	Matrix4f Matrix4f::operator*(Matrix4f& other)
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

	Matrix4f Matrix4f::ortho(float left, float right, float bottom, float top, float near, float far)
	{
		Matrix4f result(1);
		result[0][0] = 2 / (right - left);
		result[1][1] = 2 / (top - bottom);
		result[2][2] = 2 / (far - near);
		result[3][0] = -(right + left) / (right - left);
		result[3][1] = -(top + bottom) / (top - bottom);
		result[3][2] = -(far + near) / (far - near);
		return result;
	}

	Matrix4f Matrix4f::translation(float x, float y, float z)
	{
		Matrix4f result = Matrix4f::identity();
		result.elem[3] = x;
		result.elem[7] = y;
		result.elem[11] = z;
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
}