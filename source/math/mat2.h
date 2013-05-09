/****************************************************
*	File: mat2.h
*    Author: Mikalai Abramau
*	Desc: Class implemeting 2x2 matrix
****************************************************/

#ifndef _H_MAT2X2_MATH
#define _H_MAT2X2_MATH

#include "math_error.h"
#include "vec2.h"

namespace Math
{
	template<class T>
	class  Matrix2x2
	{
		T m[4];
	public:

		static Matrix2x2<T> CreateIdentity()
		{
			return Matrix2x2<T>();
		}

		static Matrix2x2<T> CreateMirrorX()
		{
			Matrix2x2<T> m;
			m[0] = 1;
			m[1] = 0;
			m[2] = 0;
			m[3] = -1;
			return m;

		}

		static Matrix2x2<T> CreateMirrorY()
		{
			Matrix2x2<T> m;
			m[0] = -1;
			m[1] = 0;
			m[2] = 0;
			m[3] = 1;
			return m;
		}

		static Matrix2x2<T> CreateMirrorXY()
		{
			Matrix2x2<T> m;
			m[0] = -1;
			m[1] = 0;
			m[2] = 0;
			m[3] = -1;
			return m;
		}

		Matrix2x2<T>()
		{
			memset(m, 0, sizeof(m));
			m[0] = m[3] = T(1);
		}

		const T& operator [] (int i) const
		{
			if (i < 0 || i > 3)
				throw MathIndexOutOfRange();
			return m[i];
		}

		T& operator [] (int i)
		{
			if (i < 0 || i > 3)
				throw MathIndexOutOfRange();
			return m[i];
		}

		Vector2<T> Row(int i)
		{
			return Vector2<T>(m[i*2 + 0], m[i*2 + 1]);
		}

		Vector2<T> Column(int i)
		{
			return Vector2<T>(m[i], m[2 + i]);
		}

		//
		//  find determinant
		//
		T Determinant() const
		{
			return m[0] * m[3] - m[1] * m[2];
		}

		operator T* ()
		{
			return m;
		}
			
		operator const T* () const
		{
			return m;
		}

		//
		//	inverse matrix
		//
		Matrix2x2<T>& Inverse()
		{
			T d = Determinant();
			if (d == T(0))
				throw MathDevisionByZero();

			d = T(1) / d;

			T tm[4];
			tm[0] =	 m[3] * d;
			tm[1] = -m[1] * d;
			tm[2] = -m[2] * d;
			tm[3] =  m[0] * d;
			
			memcpy(m, tm, sizeof(m));
			return *this;
		}

		Matrix2x2<T> Inversed() const
		{
			T d = Determinant();
			if (d == T(0))
				throw MathDevisionByZero();

			d = T(1) / d;

			Matrix2x2<T> tm;
			tm[0] =	 m[3] * d;
			tm[1] = -m[1] * d;
			tm[2] = -m[2] * d;
			tm[3] =  m[0] * d;
			
			return tm;
		}

		//
		// Set column in matrix
		//
		Matrix2x2<T>& SetColumn(int column, const Vector2<T>& v)
		{
			for (int i = 0; i < 2; i++)
			{
				m[column * 2 + i] = v[i];
			}

			return *this;
		}

		Matrix2x2<T>& SetRow(int row, const Vector2<T>& v)
		{
			for (int i = 0; i < 2; i++)
			{
				m[i * 2 + row] = v[i];
			}

			return *this;
		}

		//
		//	Identify matrix
		//
		Matrix2x2<T>& Identity()
		{
			T tm[4] = {T(1),T(0),T(0),T(1)};
			memcpy(m, tm, sizeof(m));
			return *this;
		}
	};

	//  mult two matrix
	template<class T>
	static Matrix2x2<T> operator *(const Matrix2x2<T>& a, const Matrix2x2<T>& b)
	{
		Matrix2x2<T> c;
		c.SetRow(0, Vector2<T>(a[0]*b[0] + a[2]*b[1], a[0]*b[2] + a[2]*b[3]));
		c.SetRow(1, Vector2<T>(a[1]*b[0] + a[3]*b[1], a[1]*b[2] + a[3]*b[3]));
		return c;
	}

	//
	//	mult vector on matrix
	//
	template<class T>
	static Vector2<T> operator * (const Matrix2x2<T>& a, const Vector2<T>& v)
	{
		Vector2<T> r;
		r[0] = a[0]*v[0] + a[2]*v[1];
		r[1] = a[1]*v[0] + a[3]*v[2];
		return r;
	}
	//
	//	mult matrix on scalar
	//
	template<class T>
	static Matrix2x2<T> operator * (const Matrix2x2<T>& a, T b)
	{
		Matrix2x2<T> c;
		c[0] *= b;
		c[1] *= b;
		c[2] *= b;
		c[3] *= b;
	}

	//
	//	divide matrix on scalar
	//
	template<class T>
	static Matrix2x2<T> operator / (const Matrix2x2<T>& a, T b)
	{
		if (b == T(0))
			throw MathDevisionByZero();

		b = T(1) / b;
		return a * b;
	}
		
	//
	//	adds two matrix
	//
	template<class T>
	static Matrix2x2<T> operator + (const Matrix2x2<T>& a, const Matrix2x2<T>& b)
	{
		Matrix2x2<T> m;
		for (int i = 0; i < 4; i++)
			m[i] = a[i] + b[i];
		return m;
	}

	class PUNK_ENGINE mat2 : public Matrix2x2<float>
	{
	public:
		mat2() : Matrix2x2<float> () {}
		mat2(const mat2& m) : Matrix2x2<float>(m) {}
		mat2(const Matrix2x2<float>& m) : Matrix2x2<float>(m) {}
	};

}

#endif
