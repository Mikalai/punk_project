/**********************************************************
*	File: mat3.h
*	Author: Mikalai Abramau
*	Desc: Implements a 3x3 matrix entity
***********************************************************/

#ifndef _H_MAT3X3_MATH
#define _H_MAT3X3_MATH

//#include <algorithm>
#include "../system/errors/exceptions.h"
#include "math_error.h"
#include "mat2.h"
#include "vec3.h"
#include "../string/string.h"

namespace System { class Buffer; }
namespace Math
{
	template<class T>
	class  Matrix3x3
	{
    protected:
		T m[9];

	public:

		Matrix3x3<T>(T m0, T m1, T m2, T m3, T m4, T m5, T m6, T m7, T m8)
		{
			m[0] = m0;
			m[1] = m1;
			m[2] = m2;
			m[3] = m3;
			m[4] = m4;
			m[5] = m5;
			m[6] = m6;
			m[7] = m7;
			m[8] = m8;
		}

		Matrix3x3<T>(const Vector3<T>& column0, const Vector3<T>& column1, const Vector3<T>& column2)
		{
			m[0] = column0[0];
			m[1] = column0[1];
			m[2] = column0[2];
			m[3] = column1[0];
			m[4] = column1[1];
			m[5] = column1[2];
			m[6] = column2[0];
			m[7] = column2[1];
			m[8] = column2[2];
		}

		Matrix3x3<T>()
		{
			memset(m, 0, sizeof(m));
			m[0] = m[4] = m[8] = T(1);
		}

		Matrix3x3<T>(const Matrix3x3<T>& mat)
		{
			if (this != &mat)
			{
				memcpy(m, mat.m, sizeof(m));
			}
		}

		template<class U>
		Matrix3x3<T>(const Matrix3x3<U>& mat)
		{
			for (int i = 0; i < 9; ++i)
				m[i] = (T)mat[i];
		}

		Matrix3x3<T>& operator = (const Matrix3x3<T>& mat)
		{
			if (this != &mat)
			{
				memcpy(m, mat.m, sizeof(m));
			}
			return *this;
		}

		T& operator [] (int i)
		{
			if (i < 0 || i > 8)
                throw System::PunkException("Index out of range");

			return m[i];
		}

		const T& operator [] (int i) const
		{
			if (i < 0 || i > 8)
                throw System::PunkException("Index out of range");
			return m[i];
		}


		operator T*()
		{
			return m;
		}

		operator const T*() const
		{
			return m;
		}

		Matrix3x3<T>& operator += (const Matrix3x3<T>& v)
		{
			for (int i = 0; i < 9; ++i)
				m[i] += v[i];
			return *this;
		}

		Matrix3x3<T>& operator -= (const Matrix3x3<T>& v)
		{
			for (int i = 0; i < 9; ++i)
				m[i] -= v[i];
			return *this;
		}

		Matrix3x3<T>& operator *= (T s)
		{
			for (int i = 0; i < 9; i++)
				m[i] *= s;

			return *this;
		}

		Matrix3x3<T>& operator /= (T s)
		{
			s = T(1) / s;
			for (int i = 0; i < 9; i++)
				m[i] *= s;

			return *this;
		}

		//
		//  find determinant
		//
		T Determinant() const
		{
			return m[0] * (m[4] * m[8] - m[5] * m[7])
				- m[1] * (m[3] * m[8] - m[5] * m[6])
				+ m[2] * (m[3] * m[7] - m[4] * m[6]);
		}

		const T At(int row, int col) const
		{
			return m[col*3 + row];
		}

		T& At(int row, int col) 
		{
			return m[col*3 + row];
		}
		
		Matrix3x3<T>& SwapRows(int row1, int row2)
		{
			int size = 3;
            for (int col = 0; col < size; ++col)
				std::swap(At(row1, col), At(row2, col));
			return *this;
		}

		Matrix3x3<T>& Chop(T eps = T(0.00001))
		{
			for (int i = 0; i != 9; ++i)
				if (fabs(m[i]) < eps)
					m[i] = T(0);
			return *this;				
		}

		//
		//	returned inversed copy
		//
		const Matrix3x3<T> Inversed() const
		{
			Matrix3x3<T> inversedMatrix;
			inversedMatrix[0] = m[4] * m[8] - m[5] * m[7];
			inversedMatrix[1] = -(m[1] * m[8] - m[2] * m[7]);
			inversedMatrix[2] = m[1] * m[5] - m[2] * m[4];
			inversedMatrix[3] = -(m[3] * m[8] - m[5] * m[6]);
			inversedMatrix[4] = m[0] * m[8] - m[2] * m[6];
			inversedMatrix[5] = -(m[0] * m[5] - m[2] * m[3]);
			inversedMatrix[6] = m[3] * m[7] - m[4] * m[6];
			inversedMatrix[7] = -(m[0] * m[7] - m[1] * m[6]);
			inversedMatrix[8] = m[0] * m[4] - m[1] * m[3];

			T d = Determinant();

			if (d == T(0))
                throw System::PunkException("Can't inverse matrix. Determinant is 0");

			return inversedMatrix / d;
		}

		Matrix3x3<T>& Inverse()
		{
			T d = Determinant();
			T tm[9];

			tm[0] = m[4] * m[8] - m[5] * m[7];
			tm[1] = -(m[1] * m[8] - m[2] * m[7]);
			tm[2] = m[1] * m[5] - m[2] * m[4];
			tm[3] = -(m[3] * m[8] - m[5] * m[6]);
			tm[4] = m[0] * m[8] - m[2] * m[6];
			tm[5] = -(m[0] * m[5] - m[2] * m[3]);
			tm[6] = m[3] * m[7] - m[4] * m[6];
			tm[7] = -(m[0] * m[7] - m[1] * m[6]);
			tm[8] = m[0] * m[4] - m[1] * m[3];

			memcpy(m, tm, sizeof(m));

			if (d == T(0))
                throw System::PunkException("Can't inverse matrix. Determinant is 0");
			
			return *this /= d;
		}

		/******************************************************
		* Set row in matrix
		* */
		Matrix3x3<T>& SetColumn(int column, const Vector3<T>& v)
		{
			for (int i = 0; i < 3; i++)
			{
				m[column * 3 + i] = v[i];
			}
			return *this;
		}

		Matrix3x3<T>& SetRow(int row, const Vector3<T>& v)
		{
			for (int i = 0; i < 3; ++i)
				m[3*i + row] = v[i];
			return *this;
		}

		/*********************************************************
		* makes current matrix identity
		* **********************************************************/
		Matrix3x3<T>& Identity()
		{
			T tm[9] = {1, 0, 0, 
					  0, 1, 0, 
					  0, 0, 1};

			memcpy(m, tm, sizeof(m));

			return *this;
		}

		Matrix3x3<T>& Zerofy()
		{
			memset(m, 0, sizeof(m));
			return *this;
		}

		//
		//	Translation part
		//
		const Vector2<T> TranslationPart() const
		{
			return Vector2<T>(m[6], m[7]);
		}

		//
		//	Rotation part
		//
		const Matrix2x2<T> RotationPart() const
		{
			Matrix2x2<T> tm;
			tm[0] = m[0];
			tm[1] = m[1];
			tm[2] = m[3];
			tm[3] = m[4];
			return tm;
		}

		const System::string ToString() const
		{
            return System::string(L"\n {0:7.3} {1:7.3} %{2:7.3}\n {3:7.3} {4:7.3} {5:7.3}\n{6:7.3} %{7:7.3} {8:7.3}\n").arg(m[0])
                    .arg(m[3]).arg(m[6]).arg(m[1]).arg(m[4]).arg(m[7]).arg(m[2]).arg(m[5]).arg(m[8]);
		}


/*		bool Save(System::Buffer& buffer) const
		{
			buffer.WriteBuffer(m, sizeof(m));
		}

		bool Load(System::Buffer& buffer)
		{
			buffer.ReadBuffer(m, sizeof(m));
		}
*/
		//	0 3 6
		//	1 4 7
		//	2 5 8
		Matrix3x3<T> Transposed() const
		{
			Matrix3x3<T> res;
			res.m[1] = m[3];
			res.m[3] = m[1];
			res.m[6] = m[2];
			res.m[2] = m[6];
			res.m[5] = m[7];
			res.m[7] = m[5];
			res.m[0] = m[0];
			res.m[4] = m[4];
			res.m[8] = m[8];
			return res;
		}

		Matrix3x3<T>& Transpose()
		{
			T tm[9];
			tm[1] = m[3];
			tm[3] = m[1];
			tm[6] = m[2];
			tm[2] = m[6];
			tm[5] = m[7];
			tm[7] = m[5];
			tm[0] = m[0];
			tm[4] = m[4];
			tm[8] = m[8];

			return *this;
		}

		static const Matrix3x3<T> Null()
		{
			Matrix3x3<T> res;
			memset(&res, 0, sizeof(res));
			return res;
		}

		static const Matrix3x3<T> Create2DTranslate(T dx, T dy)
		{
			Matrix3x3<T> res;
			res[0] = res[4] = res[8] = T(1);
			res[6] = dx;
			res[7] = dy;
			return res;
		}

		
		static const Matrix3x3<T> Create2DTranslate(const Vector2<T>& v)
		{
			return Create2DTranslate(v.X(), v.Y());
		}

		static const Matrix3x3<T> Create2DRotate(T angle)
		{
			Matrix3x3<T> res;
			res[0] = cos(angle);
			res[1] = sin(angle);
			res[2] = 0;
			res[3] = -sin(angle);
			res[4] = cos(angle);
			res[5] = 0;
			res[6] = 0;
			res[7] = 0;
			res[8] = 1;
			return res;
		}

		static const Matrix3x3<T> CreateFreeForm2DRotate(T angle, T x, T y)
		{
			return Create2DTranslate(x, y) * Create2DRotate(angle) * Create2DTranslate(x, y).Inversed();
		}

		static const Matrix3x3<T> CreateFreeForm2DRotate(T angle, const Vector2<T>& v)
		{
			return CreateFreeForm2DRotate(angle, v.X(), v.Y());
		}

		static const Matrix3x3<T> Create2DScale(T sx, T sy)
		{
			Matrix3x3<T> m;
			m[0] = sx;
			m[4] = sy;
			m[8] = 1;
			return m;
		}

		static const Matrix3x3<T> Create2DScale(const Vector2<T>& v)
		{
			return Create2DScale(v[0], v[1]);
		}

		static const Matrix3x3<T> CreateIdentity() 
		{
			return Matrix3x3<T>();
		}

		static const Matrix3x3<T> Create2DFreeFormScale(T sx, T sy, const Vector2<T>& v)
		{
			return Create2DTranslate(v) * Create2DScale(sx, sy) * Create2DTranslate(v).Inversed();
		}

		static const Matrix3x3<T> Create2DFreeFormScale(T sx, T sy, T x, T y)
		{
			return Create2DTranslate(x, y) * Create2DScale(sx, sy) * Create2DTranslate(x, y).Inversed();
		}		

		static const Matrix3x3<T> Create2DReflectionX()
		{
			Matrix3x3<T> m;
			m[0] = 1;
			m[4] = -1;
			m[8] = 1;
			return m;
		}

		static const Matrix3x3<T> Create2DReflectionY()
		{
			Matrix3x3<T> m;
			m[0] = -1;
			m[4] = 1;
			m[8] = 1;
			return m;
		}

		static const Matrix3x3<T> Create2DOriginReflection()
		{
			Matrix3x3<T> m;
			m[0] = -1;
			m[4] = -1;
			m[8] = 1;
			return m;
		}
	};

	//  mult matrix
	template<class T>
	static const Matrix3x3<T> operator *(const Matrix3x3<T>& a, const Matrix3x3<T>& b)
	{
		Matrix3x3<T> c;
		c.SetColumn(0, Vector3<T>(
			b[0] * a[0] + b[1] * a[3] + b[2] * a[6],
			b[0] * a[1] + b[1] * a[4] + b[2] * a[7],
			b[0] * a[2] + b[1] * a[5] + b[2] * a[8]));
		c.SetColumn(1, Vector3<T>(
			b[3] * a[0] + b[4] * a[3] + b[5] * a[6],
			b[3] * a[1] + b[4] * a[4] + b[5] * a[7],
			b[3] * a[2] + b[4] * a[5] + b[5] * a[8]));
		c.SetColumn(2, Vector3<T>(
			b[6] * a[0] + b[7] * a[3] + b[8] * a[6],
			b[6] * a[1] + b[7] * a[4] + b[8] * a[7],
			b[6] * a[2] + b[7] * a[5] + b[8] * a[8]));
		return c;
	}

	//
	//	mult on scalar
	//
	template<class T> 
	static const Matrix3x3<T> operator * (const T& s, const Matrix3x3<T>& a)
	{
		Matrix3x3<T> m;
		m[0] = a[0] * s;
		m[1] = a[1] * s;
		m[2] = a[2] * s;
		m[3] = a[3] * s;
		m[4] = a[4] * s;
		m[5] = a[5] * s;
		m[6] = a[6] * s;
		m[7] = a[7] * s;
		m[8] = a[8] * s;
		return m;
	}

	//
	//	mult on scalar
	//
	template<class T> 
	static const Matrix3x3<T> operator * (const Matrix3x3<T>& a, const T& s)
	{
		Matrix3x3<T> m;
		m[0] = a[0] * s;
		m[1] = a[1] * s;
		m[2] = a[2] * s;
		m[3] = a[3] * s;
		m[4] = a[4] * s;
		m[5] = a[5] * s;
		m[6] = a[6] * s;
		m[7] = a[7] * s;
		m[8] = a[8] * s;
		return m;
	}

	//
	//	divide on scalar
	//
	template<class T>
	static const Matrix3x3<T> operator / (const Matrix3x3<T>& a, const T& s)
	{
		Matrix3x3<T> m;
		m[0] = a[0] / s;
		m[1] = a[1] / s;
		m[2] = a[2] / s;
		m[3] = a[3] / s;
		m[4] = a[4] / s;
		m[5] = a[5] / s;
		m[6] = a[6] / s;
		m[7] = a[7] / s;
		m[8] = a[8] / s;
		return m;
	}

	//
	//	add 2 matrix
	//
	template<class T>
	static const Matrix3x3<T> operator + (const Matrix3x3<T>& a, const Matrix3x3<T>& b)
	{
		Matrix3x3<T> m;
		m[0] = a[0] + b[0];
		m[1] = a[1] + b[1];
		m[2] = a[2] + b[2];
		m[3] = a[3] + b[3];
		m[4] = a[4] + b[4];
		m[5] = a[5] + b[5];
		m[6] = a[6] + b[6];
		m[7] = a[7] + b[7];
		m[8] = a[8] + b[8];
		return m;
	}

	//
	//	add 2 matrix
	//
	template<class T>
	static const Matrix3x3<T> operator - (const Matrix3x3<T>& a, const Matrix3x3<T>& b)
	{
		Matrix3x3<T> m;
		m[0] = a[0] - b[0];
		m[1] = a[1] - b[1];
		m[2] = a[2] - b[2];
		m[3] = a[3] - b[3];
		m[4] = a[4] - b[4];
		m[5] = a[5] - b[5];
		m[6] = a[6] - b[6];
		m[7] = a[7] - b[7];
		m[8] = a[8] - b[8];
		return m;
	}

	template<class T>
	static const Matrix3x3<T> MultTransposed(const Vector3<T>& a, const Vector3<T>& b)
	{
		Matrix3x3<T> m;
		m[0] = a[0]*b[0];
		m[3] = a[0]*b[1];
		m[6] = a[0]*b[2];

		m[1] = a[1]*b[0];
		m[4] = a[1]*b[1];
		m[7] = a[1]*b[2];

		m[2] = a[2]*b[0];
		m[5] = a[2]*b[1];
		m[8] = a[2]*b[2];

		return m;
	}

	//
	//	mult vector on matrix
	//
	template<class T>
	static Vector3<T> operator * (const Matrix3x3<T>& m, const Vector3<T>& v)
	{
		Vector3<T> res;
		res[0] = m[0] * v[0] + m[3] * v[1] + m[6] * v[2];
		res[1] = m[1] * v[0] + m[4] * v[1] + m[7] * v[2];
		res[2] = m[2] * v[0] + m[5] * v[1] + m[8] * v[2];

		return res;
	}

	//
	//	mult vector on matrix
	//
	template<class T>
	static bool operator == (const Matrix3x3<T>& l, const Matrix3x3<T>& r)
	{
		for (int i = 0; i < 9; ++i)
			if (l[i] != r[i])
				return false;
		return true;;
	}

	class PUNK_ENGINE_API mat3 : public Matrix3x3<float>
	{		
	public:
		typedef float T;

		mat3() : Matrix3x3<float> () {}
		mat3(const mat3& m) : Matrix3x3<float>(m) {}
		mat3(const Matrix3x3<float>& m) : Matrix3x3<float>(m) {}
		mat3(T m0, T m1, T m2, T m3, T m4, T m5, T m6, T m7, T m8) : Matrix3x3<float>(m0, m1, m2, m3, m4, m5, m6, m7, m8) {}
        void Save(System::Buffer* buffer) const;
        void Load(System::Buffer* buffer);
	};

}

#endif
