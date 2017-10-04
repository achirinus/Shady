#include "Matrix4f.h"
#include <math.h>
#include "ShMath.h"
#include "MemUtils.h"
#define MAT4_DIM 4

#define MAT4_ROW_MAJOR
//#define MAT4_COL_MAJOR

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

	Matrix4f Matrix4f::ortho(float left, float right, float top, float bottom, float nier, float phar) 
	{
		//Had to rename near and far due to some stupid keywords
		Matrix4f result(1);
		result[0][0] = 2 / (right - left);
		result[1][1] = 2 / (top - bottom);
		result[2][2] = - 2 / (phar - nier);

#ifdef MAT4_COL_MAJOR 
		result[3][0] = -(right + left) / (right - left);
		result[3][1] = -(top + bottom) / (top - bottom);
		result[3][2] = -(phar + nier) / (phar - nier);
#else
		result[0][3] = -(right + left) / (right - left);
		result[1][3] = -(top + bottom) / (top - bottom);
		result[2][3] = -(phar + nier) / (phar - nier);
#endif

		return result;
	}

	Matrix4f Matrix4f::lookAt(const Vec3f& eye, const Vec3f& center, const Vec3f& up)
	{
		Matrix4f result(1);
		Vec3f first(normalize(center - eye));
		Vec3f second(normalize(first.cross(up)));
		Vec3f third = second.cross(first);
		result[0][0] = second.x;
		result[1][0] = second.y;
		result[2][0] = second.z;
		result[0][1] = third.x;
		result[1][1] = third.y;
		result[2][1] = third.z;
		result[0][2] = -first.x;
		result[1][2] = -first.y;
		result[2][2] = -first.z;
		result[3][0] = -second.dot(eye);
		result[3][1] = -third.dot(eye);
		result[3][2] = -first.dot(eye);
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
#ifdef MAT4_COL_MAJOR
		result[3][0] = x;
		result[3][1] = y;
		result[3][2] = z;
#else
		result[0][3] = x;
		result[1][3] = y;
		result[2][3] = z;
#endif
		return result;
	}

	Matrix4f Matrix4f::translation(const Vec3f& vec)
	{
		Matrix4f result = Matrix4f::identity();
#ifdef MAT4_COL_MAJOR
		result[3][0] = vec.x;
		result[3][1] = vec.y;
		result[3][2] = vec.z;
#else
		result[0][3] = vec.x;
		result[1][3] = vec.y;
		result[2][3] = vec.z;
#endif
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
		f32 tanHalfFov = tan(fov/2);
		Matrix4f result{};

		
		result[0][0] = 1 / aspectRatio * tanHalfFov;
		result[1][1] = 1/ tanHalfFov;
		result[2][2] = -(zFar + zNear) / (zFar - zNear);
		result[3][2] = -(2 * zFar * zNear) / (zFar - zNear);
		result[2][3] = -1.0f;
		return result;
	}

	Matrix4f Matrix4f::perspective(f32 left, f32 right, f32 top, f32 bot, f32 nier, f32 phar)
	{
		Matrix4f result{};

		result[0][0] = (2.0f * nier) /(right - left);
		result[1][1] = (2.0f * nier) /(top - bot);
		result[2][2] = -(phar + nier) / (phar - nier);

#ifdef MAT4_COL_MAJOR
		result[2][0] = (right + left) / (right - left);
		result[2][1] = (top + bot) / (top - bot);
		result[3][2] = -(2.0f * phar * nier) / (phar - nier);
		result[2][3] = -1.0f;
#else
		result[0][2] = (right + left) / (right - left);
		result[1][2] = (top + bot) / (top - bot);
		result[2][3] = -(2.0f * phar * nier) / (phar - nier);
		result[3][2] = -1.0f;
#endif
		return result;
	}

	Vec4f Matrix4f::operator*(Vec4f vec)
	{
		Vec4f result;
#ifdef MAT4_ROW_MAJOR
		result.x = (vec.x * rows[0][0]) + (vec.y * rows[0][1]) + (vec.z * rows[0][2]) + (vec.w * rows[0][3]);
		result.y = (vec.x * rows[1][0]) + (vec.y * rows[1][1]) + (vec.z * rows[1][2]) + (vec.w * rows[1][3]);
		result.z = (vec.x * rows[2][0]) + (vec.y * rows[2][1]) + (vec.z * rows[2][2]) + (vec.w * rows[2][3]); 
		result.w = (vec.x * rows[3][0]) + (vec.y * rows[3][1]) + (vec.z * rows[3][2]) + (vec.w * rows[3][3]);
#else
		result.x = (vec.x * rows[0][0]) + (vec.y * rows[1][0]) + (vec.z * rows[2][0]) + (vec.w * rows[3][0]);
		result.y = (vec.x * rows[0][1]) + (vec.y * rows[1][1]) + (vec.z * rows[2][1]) + (vec.w * rows[3][1]);
		result.z = (vec.x * rows[0][2]) + (vec.y * rows[1][2]) + (vec.z * rows[2][2]) + (vec.w * rows[3][2]); 
		result.w = (vec.x * rows[0][3]) + (vec.y * rows[1][3]) + (vec.z * rows[2][3]) + (vec.w * rows[3][3]);
#endif
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

	void Matrix4f::transpose()
	{
		Shady::transpose(elem, 4);
	}

	b8 Matrix4f::isColumnMajor()
	{
#ifdef MAT4_COL_MAJOR
		return true;
#else
		return false;
#endif
	}

} // namespace Shady

#ifdef MAT4_COL_MAJOR
	#undef MAT4_COL_MAJOR
#endif

#ifdef MAT4_ROW_MAJOR
	#undef MAT4_ROW_MAJOR
#endif