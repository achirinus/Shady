#include <Matrix3f.h>

#include "ShMath.h" 
#define MAT3_DIM 3

namespace Shady
{
	Matrix3f::Matrix3f()
	{
		for (int i = 0; i < MAT3_DIM * MAT3_DIM; i++)
		{
			elem[i] = 0;
		}
	}
	Matrix3f::Matrix3f(Vec3f firstRow, Vec3f secondRow, Vec3f thirdRow)
	{
		rows[0] = firstRow;
		rows[1] = secondRow;
		rows[2] = thirdRow;
	}
	Matrix3f::Matrix3f(const Matrix3f& other)
	{
		for (int i = 0; i < MAT3_DIM * MAT3_DIM; i++)
		{
			elem[i] = other.elem[i];
		}
	}

	Matrix3f& Matrix3f::operator=(const Matrix3f& other)
	{
		for (int i = 0; i < MAT3_DIM * MAT3_DIM; i++)
		{
			elem[i] = other.elem[i];
		}
		return *this;
	}
	Vec3f& Matrix3f::operator[](int index)
	{
		return rows[index];
	}
	Matrix3f Matrix3f::identity()
	{
		Matrix3f result{};
		for (int i = 0; i < MAT3_DIM; i++)
		{
			result.elem[i + MAT3_DIM * i] = 1.0f;
		}
		return result;
	}

	Matrix3f Matrix3f::operator*(Matrix3f& other)
	{
		Matrix3f result;
		for (int i = 0; i < MAT3_DIM; i++)
		{
			for (int j = 0; j < MAT3_DIM; j++)
			{
				float sum = 0;
				for (int k = 0; k < MAT3_DIM; k++)
				{
					sum += elem[k + MAT3_DIM * i] * elem[j + MAT3_DIM * k];
				}
				result.elem[j + MAT3_DIM * i] = sum;
			}
		}
		return result;
	}
	
	Vec3f Matrix3f::operator*(Vec3f vec)
	{
		Vec3f result;
		for (int i = 0; i < MAT3_DIM; i++)
		{
			float sum = 0;
			for (int j = 0; j < MAT3_DIM; j++)
			{
				sum += elem[j + MAT3_DIM * i] * vec[j];
			}
			result[i] = sum;
		}
		return result;
	}

	void Matrix3f::transpose()
	{
		Shady::transpose(elem, 3);
	}

}