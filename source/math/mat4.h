#ifndef _H_MAT4X4_MATH
#define _H_MAT4X4_MATH

#include <stdio.h>
#include <ostream>
#include <istream>
#include <cmath>

#include "../config.h"
#include "../system/logger.h"

#include "mat3.h"
#include "vec4.h"
#include "vec3.h"

namespace Math
{
	template<class T>
	class Matrix4x4
	{
		T m[16];
	public:

		static const Matrix4x4<T> CreateFromPoistionAndDirection(const Math::Vector3<T>& position, const Math::Vector3<T>& direction)
		{
			Matrix4x4<T> result = CreateTargetCameraMatrix(position, position + direction, Math::Vector3<T>(0, 1, 0)).Inversed();
			return result;
		}

		static Matrix4x4<T> CreatePerspectiveProjection(T fovx, T aspect, T znear, T zfar)
		{
			Matrix4x4<T> res;

			float e = 1.0f / tanf(fovx / 2.0f);
			float fovy = 2.0f * atanf(aspect / e);
			float xScale = 1.0f / tanf(0.5f * fovy);
			float yScale = xScale * aspect;
			float* m = &res[0];

			m[0*4 + 0] = xScale;
			m[0*4 + 1] = 0.0f;
			m[0*4 + 2] = 0.0f;
			m[0*4 + 3] = 0.0f;

			m[1*4 + 0] = 0.0f;
			m[1*4 + 1] = yScale;
			m[1*4 + 2] = 0.0f;
			m[1*4 + 3] = 0.0f;

			m[2*4 + 0] = 0.0f;
			m[2*4 + 1] = 0.0f;
			m[2*4 + 2] = (zfar + znear) / (znear - zfar);
			m[2*4 + 3] = -1.0f;

			m[3*4 + 0] = 0.0f;
			m[3*4 + 1] = 0.0f;
			m[3*4 + 2] = (2.0f * zfar * znear) / (znear - zfar);
			m[3*4 + 3] = 0.0f;

			return res;
		}

		static Matrix4x4<T> CreatePerspectiveProjectionInfinity(T left, T right, T top, T bottom, T znear)
		{
			Matrix4x4<T> res;

			float* m = &res[0];

			m[0*4 + 0] = T(2)*znear / (right - left);
			m[0*4 + 1] = 0.0f;
			m[0*4 + 2] = 0.0f;
			m[0*4 + 3] = 0.0f;

			m[1*4 + 0] = 0.0f;
			m[1*4 + 1] = T(2)*znear / (top - bottom);
			m[1*4 + 2] = 0.0f;
			m[1*4 + 3] = 0.0f;

			m[2*4 + 0] = (right + left) / (right - left);
			m[2*4 + 1] = (top + bottom) / (top - bottom);
			m[2*4 + 2] = -1;
			m[2*4 + 3] = -1.0f;

			m[3*4 + 0] = 0.0f;
			m[3*4 + 1] = 0.0f;
			m[3*4 + 2] = -(2.0f * znear);
			m[3*4 + 3] = 0.0f;

			return res;
		}

		static Matrix4x4<T> CreatePerspectiveProjection(T left, T right, T top, T bottom, T znear, T zfar)
		{
			Matrix4x4<T> res;

			float* m = &res[0];

			m[0*4 + 0] = T(2)*znear / (right - left);
			m[0*4 + 1] = 0.0f;
			m[0*4 + 2] = 0.0f;
			m[0*4 + 3] = 0.0f;

			m[1*4 + 0] = 0.0f;
			m[1*4 + 1] = T(2)*znear / (top - bottom);
			m[1*4 + 2] = 0.0f;
			m[1*4 + 3] = 0.0f;

			m[2*4 + 0] = (right + left) / (right - left);
			m[2*4 + 1] = (top + bottom) / (top - bottom);
			m[2*4 + 2] = -(zfar+znear) / (zfar - znear);
			m[2*4 + 3] = -1.0f;

			m[3*4 + 0] = 0.0f;
			m[3*4 + 1] = 0.0f;
			m[3*4 + 2] = -(2.0f * znear * zfar) / (zfar - znear);
			m[3*4 + 3] = 0.0f;

			return res;
		}

		static Matrix4x4<T> CreateTargetCameraMatrix(const Vector3<T>& eye, const Vector3<T>& target, const Vector3<T>& up)
		{
			Vector3<T> zAxis = (eye - target);
			zAxis.Normalize();

			vec3 xAxis = up.Cross(zAxis);
			xAxis.Normalize();

			vec3 yAxis = zAxis.Cross(xAxis);
			yAxis.Normalize();

			Matrix4x4<T> res;
			float* m = res.m;

			/*m[0*4 + 0] = xAxis[0];
			m[0*4 + 1] = xAxis[1];
			m[0*4 + 2] = xAxis[2];
			m[0*4 + 3] = -eye.Dot(xAxis);

			m[1*4 + 0] = yAxis[0];
			m[1*4 + 1] = yAxis[1];
			m[1*4 + 2] = yAxis[2];
			m[1*4 + 3] = -eye.Dot(yAxis);

			m[2*4 + 0] = -zAxis[0];
			m[2*4 + 1] = -zAxis[1];
			m[2*4 + 2] = -zAxis[2];
			m[2*4 + 3] = -eye.Dot(zAxis);

			m[3*4 + 0] = 0.0f;
			m[3*4 + 1] = 0.0f;
			m[3*4 + 2] = 0.0f;
			m[3*4 + 3] = 1.0f;*/

			m[0*4 + 0] = xAxis[0];
			m[1*4 + 0] = xAxis[1];
			m[2*4 + 0] = xAxis[2];
			m[3*4 + 0] = -eye.Dot(xAxis);

			m[0*4 + 1] = yAxis[0];
			m[1*4 + 1] = yAxis[1];
			m[2*4 + 1] = yAxis[2];
			m[3*4 + 1] = -eye.Dot(yAxis);

			m[0*4 + 2] = zAxis[0];
			m[1*4 + 2] = zAxis[1];
			m[2*4 + 2] = zAxis[2];
			m[3*4 + 2] = -eye.Dot(zAxis);

			m[0*4 + 3] = 0.0f;
			m[1*4 + 3] = 0.0f;
			m[2*4 + 3] = 0.0f;
			m[3*4 + 3] = 1.0f;/**/
			return res;
		}

		static Matrix4x4<T> CreateFreeCameraMatrix(const Vector3<T>& eye, const Vector3<T>& dir, const Vector3<T>& up)
		{
			Vector3<T> target = eye + dir;
			return CreateTargetCameraMatrix(eye, target, up);
		}

		static Matrix4x4<T> CreateIdentity()
		{
			return Matrix4x4<T>();
		}

		static Matrix4x4<T> CreateOrthographicProjection(float left, float right, float top, float bottom, float _near, float _far)
		{
			Matrix4x4<T> result;
			result.SetColumn(0, Vector4<T>(T(2)/(right - left), 0, 0, 0));
			result.SetColumn(1, Vector4<T>(0, T(2)/(top - bottom), 0, 0));
			result.SetColumn(2, Vector4<T>(0, 0, T(-2)/(_far - _near), 0));
			result.SetColumn(3, Vector4<T>(-(right+left)/(right - left), -(top + bottom)/(top-bottom), - (_far+_near)/(_far-_near), 1));
			return result;
		}

		static Matrix4x4<T> CreateTranslate(float x, float y, float z)
		{
			Matrix4x4<T> result;
			result.SetColumn(0, Vector4<T>(1, 0, 0, 0));
			result.SetColumn(1, Vector4<T>(0, 1, 0, 0));
			result.SetColumn(2, Vector4<T>(0, 0, 1, 0));
			result.SetColumn(3, Vector4<T>(x, y, z, 1));
			return result;
		}

		static Matrix4x4<T> CreateTranslate(const Vector3<T>& v)
		{
			Matrix4x4<T> result;
			result.SetColumn(0, Vector4<T>(1, 0, 0, 0));
			result.SetColumn(1, Vector4<T>(0, 1, 0, 0));
			result.SetColumn(2, Vector4<T>(0, 0, 1, 0));
			result.SetColumn(3, Vector4<T>(v[0], v[1], v[2], 1));
			return result;
		}

		static Matrix4x4<T> CreateScaling(float sx, float sy, float sz)
		{
			Matrix4x4<T> result;
			result.SetColumn(0, Vector4<T>(sx, 0, 0, 0));
			result.SetColumn(1, Vector4<T>(0, sy, 0, 0));
			result.SetColumn(2, Vector4<T>(0, 0, sz, 0));
			result.SetColumn(3, Vector4<T>(0, 0, 0, 1));
			return result;
		}

		static Matrix4x4<T> CreateZRotation(T angle)
		{
			T s = std::sin(angle);
			T c = std::cos(angle);
			Matrix4x4<T> result;
			result.SetColumn(0, Vector4<T>(c, s, 0, 0));
			result.SetColumn(1, Vector4<T>(-s, c, 0, 0));
			result.SetColumn(2, Vector4<T>(0, 0, 1, 0));
			result.SetColumn(3, Vector4<T>(0, 0, 0, 1));
			return result;
		}
		static Matrix4x4 CreateXRotation(T angle)
		{
			T s = std::sin(angle);
			T c = std::cos(angle);
			Matrix4x4<T> result;
			result.SetColumn(0, Vector4<T>(1, 0, 0, 0));
			result.SetColumn(1, Vector4<T>(0, c, s, 0));
			result.SetColumn(2, Vector4<T>(0, -s, c, 0));
			result.SetColumn(3, Vector4<T>(0, 0, 0, 1));
			return result;
		}

		static Matrix4x4 CreateYRotation(T angle)
		{
			T s = std::sin(angle);
			T c = std::cos(angle);
			Matrix4x4<T> result;
			result.SetColumn(0, Vector4<T>(c, 0, -s, 0));
			result.SetColumn(1, Vector4<T>(0, 1, 0, 0));
			result.SetColumn(2, Vector4<T>(s, 0, c, 0));
			result.SetColumn(3, Vector4<T>(0, 0, 0, 1));
			return result;
		}

		static Matrix4x4<T> CreateRotation(T x, T y, T z, T angle)
		{
			T inversed_length = T(1)/sqrt(x*x+y*y+z*z);

			x *= inversed_length;
			y *= inversed_length;
			z *= inversed_length;

			Matrix4x4<T> result;
			T c = std::cos(angle);
			T s = std::sin(angle);
			result.SetColumn(0, Vector4<T>(c+(1-c)*x*x, (1-c)*x*y+s*z, (1-c)*x*z-s*y, 0));
			result.SetColumn(1, Vector4<T>((1-c)*x*y-s*z, c+(1-c)*y*y, (1-c)*y*z+s*x, 0));
			result.SetColumn(2, Vector4<T>((1-c)*x*z+s*y, (1-c)*y*z-s*x, c+(1-c)*z*z, 0));
			result.SetColumn(3, Vector4<T>(0,0,0,1));
			return result;
		}

		static Matrix4x4<T> CreateReflectZ()
		{
			Matrix4x4<T> m;
			m[0] = 1;
			m[5] = 1;
			m[10] = -1;
			m[15] = 1;
			return m;
		}

		static Matrix4x4<T> CreateReflectX()
		{
			Matrix4x4<T> m;
			m[0] = -1;
			m[5] = 1;
			m[10] = 1;
			m[15] = 1;
			return m;
		}

		static Matrix4x4<T> CreateReflectY()
		{
			Matrix4x4<T> m;
			m[0] = 1;
			m[5] = -1;
			m[10] = 1;
			m[15] = 1;
			return m;
		}

		static Matrix4x4<T> CreateFromYawPitchRoll(const Vector3<T>& eye, T yaw, T pitch, T roll)
		{
			T cos_yaw = cos(yaw);
			T cos_pitch = cos(pitch);
			T cos_roll = cos(roll);
			T sin_yaw = sin(yaw);
			T sin_pitch = sin(pitch);
			T sin_roll = sin(roll);

			Math::Vector3<T> dir(sin_yaw * cos_pitch, sin_pitch, cos_pitch * -cos_yaw);
			Math::Vector3<T> up(-cos_yaw * sin_roll - sin_yaw * sin_pitch * cos_roll, cos_pitch * cos_roll, -sin_yaw * sin_roll - sin_pitch * cos_roll * -cos_yaw);

			return CreateTargetCameraMatrix(eye, eye + dir, up);
		}

		/*
		0 4 8
		1 5 9
		2 6 10
		3 7 11
		*/
		Matrix3x3<T> RotationPart() const
		{
			Matrix3x3<T> res;
			res.SetColumn(0, Vector3<T>(m[0], m[1], m[2]));
			res.SetColumn(1, Vector3<T>(m[4], m[5], m[6]));
			res.SetColumn(2, Vector3<T>(m[8], m[9], m[10]));
			return res;
		}

		Matrix4x4<T> RotationPart4x4() const
		{
			Matrix4x4<T> res;
			res.SetColumn(0, Vector4<T>(m[0], m[1], m[2], 0));
			res.SetColumn(1, Vector4<T>(m[4], m[5], m[6], 0));
			res.SetColumn(2, Vector4<T>(m[8], m[9], m[10], 0));
			res.SetColumn(3, Vector4<T>(0, 0, 0, 1));
			return res;
		}

		Vector3<T> TranslationPart() const
		{
			return Vector3<T>(m[12], m[13], m[14]);
		}

		Matrix4x4<T>()
		{
			m[0] = m[1] = m[2] = m[3] = m[4] = m[5] =
				m[6] = m[7] = m[8] = m[9] = m[10] = m[11] =
				m[12] = m[13] = m[14] = m[15] = T(0);
			m[0] = m[5] = m[10] = m[15] = T(1);
		}

		Matrix4x4<T>(const Matrix4x4<T>& v)
		{
			for (int i = 0; i < 16; ++i)
				m[i] = v[i];
		}

		T& operator [] (int i)
		{
			return m[i];
		}

		const T& operator [] (int i) const
		{
			return m[i];
		}

		/*operator T*()
		{
		return m;
		}

		operator const T* ()
		{
		return m;
		}*/

		//  inverse
		Matrix4x4<T> Inversed() const
		{
#define SWAP_ROWS(a, b) {  float * _tmp = a; (a)=(b); (b)=_tmp; }
#define MAT(m,r,c)     m [r*4+c]

			float	wtmp [4][8];
			float	m0, m1, m2, m3, s;
			float	* r0, * r1, * r2, * r3;

			r0 = wtmp [0];
			r1 = wtmp [1];
			r2 = wtmp [2];
			r3 = wtmp [3];

			r0 [0] = MAT(m,0,0);
			r0 [1] = MAT(m,0,1);
			r0 [2] = MAT(m,0,2);
			r0 [3] = MAT(m,0,3);
			r0 [4] = 1;
			r0 [5] =
				r0 [6] =
				r0 [7] = 0;

			r1 [0] = MAT(m,1,0);
			r1 [1] = MAT(m,1,1);
			r1 [2] = MAT(m,1,2);
			r1 [3] = MAT(m,1,3);
			r1 [5] = 1;
			r1 [4] =
				r1 [6] =
				r1 [7] = 0,

				r2 [0] = MAT(m,2,0);
			r2 [1] = MAT(m,2,1);
			r2 [2] = MAT(m,2,2);
			r2 [3] = MAT(m,2,3);
			r2 [6] = 1;
			r2 [4] =
				r2 [5] =
				r2 [7] = 0;

			r3 [0] = MAT(m,3,0);
			r3 [1] = MAT(m,3,1);
			r3 [2] = MAT(m,3,2);
			r3 [3] = MAT(m,3,3);
			r3 [7] = 1;
			r3 [4] =
				r3 [5] =
				r3 [6] = 0;

			// choose pivot - or die
			if ( fabs (r3 [0] )> fabs ( r2 [0] ) )
				SWAP_ROWS ( r3, r2 );

			if ( fabs ( r2 [0] ) > fabs ( r1 [0] ) )
				SWAP_ROWS ( r2, r1 );

			if ( fabs ( r1 [0] ) > fabs ( r0 [0 ] ) )
				SWAP_ROWS ( r1, r0 );

			if ( r0 [0] == 0 )
				return Matrix4x4<T>();

			// eliminate first variable
			m1 = r1[0]/r0[0];
			m2 = r2[0]/r0[0];
			m3 = r3[0]/r0[0];

			s = r0[1];
			r1[1] -= m1 * s;
			r2[1] -= m2 * s;
			r3[1] -= m3 * s;

			s = r0[2];
			r1[2] -= m1 * s;
			r2[2] -= m2 * s;
			r3[2] -= m3 * s;

			s = r0[3];
			r1[3] -= m1 * s;
			r2[3] -= m2 * s;
			r3[3] -= m3 * s;

			s = r0[4];

			if ( s != 0 )
			{
				r1[4] -= m1 * s; r2[4] -= m2 * s; r3[4] -= m3 * s;
			}

			s = r0[5];

			if ( s != 0.0 )
			{
				r1[5] -= m1 * s; r2[5] -= m2 * s; r3[5] -= m3 * s;
			}

			s = r0[6];

			if ( s != 0 )
			{
				r1[6] -= m1 * s; r2[6] -= m2 * s; r3[6] -= m3 * s;
			}

			s = r0[7];

			if ( s != 0 )
			{
				r1[7] -= m1 * s; r2[7] -= m2 * s; r3[7] -= m3 * s;
			}

			// choose pivot - or die
			if ( fabs (r3 [1] ) > fabs ( r2 [1] ) )
				SWAP_ROWS ( r3, r2 );

			if ( fabs ( r2 [1] ) > fabs ( r1 [1] ) )
				SWAP_ROWS ( r2, r1 );

			if ( r1 [1] == 0 )
				return Matrix4x4<T>();


			// eliminate second variable
			m2     = r2[1]/r1[1]; m3     = r3[1]/r1[1];
			r2[2] -= m2 * r1[2];  r3[2] -= m3 * r1[2];
			r2[3] -= m2 * r1[3];  r3[3] -= m3 * r1[3];

			s = r1[4];

			if ( 0 != s )
			{
				r2[4] -= m2 * s; r3[4] -= m3 * s;
			}

			s = r1[5];

			if ( 0 != s )
			{
				r2[5] -= m2 * s; r3[5] -= m3 * s;
			}

			s = r1[6];

			if ( 0 != s )
			{
				r2[6] -= m2 * s; r3[6] -= m3 * s;
			}

			s = r1[7];

			if ( 0 != s )
			{
				r2[7] -= m2 * s; r3[7] -= m3 * s;
			}

			// choose pivot - or die
			if ( fabs ( r3 [2] ) > fabs ( r2 [2] ) )
				SWAP_ROWS ( r3, r2 );

			if ( r2 [2] == 0)
				return Matrix4x4<T>();

			// eliminate third variable
			m3     = r3[2]/r2[2];
			r3[3] -= m3 * r2[3], r3[4] -= m3 * r2[4],
				r3[5] -= m3 * r2[5], r3[6] -= m3 * r2[6],
				r3[7] -= m3 * r2[7];

			// last check
			if ( r3 [3] == 0 )
				return Matrix4x4<T>();


			// now back substitute row 3
			s      = 1.0f/r3[3];
			r3[4] *= s; r3[5] *= s; r3[6] *= s; r3[7] *= s;

			// now back substitute row 2
			m2    = r2[3];
			s     = 1.0f/r2[2];
			r2[4] = s * (r2[4] - r3[4] * m2), r2[5] = s * (r2[5] - r3[5] * m2),
				r2[6] = s * (r2[6] - r3[6] * m2), r2[7] = s * (r2[7] - r3[7] * m2);
			m1     = r1[3];
			r1[4] -= r3[4] * m1, r1[5] -= r3[5] * m1,
				r1[6] -= r3[6] * m1, r1[7] -= r3[7] * m1;

			m0     = r0[3];
			r0[4] -= r3[4] * m0, r0[5] -= r3[5] * m0,
				r0[6] -= r3[6] * m0, r0[7] -= r3[7] * m0;

			// now back substitute row 1
			m1    = r1[2];
			s     = 1.0f/r1[1];
			r1[4] = s * (r1[4] - r2[4] * m1), r1[5] = s * (r1[5] - r2[5] * m1),
				r1[6] = s * (r1[6] - r2[6] * m1), r1[7] = s * (r1[7] - r2[7] * m1);

			m0     = r0[2];
			r0[4] -= r2[4] * m0, r0[5] -= r2[5] * m0,
				r0[6] -= r2[6] * m0, r0[7] -= r2[7] * m0;

			// now back substitute row 0
			m0    = r0[1];
			s     = 1.0f/r0[0];
			r0[4] = s * (r0[4] - r1[4] * m0), r0[5] = s * (r0[5] - r1[5] * m0),
				r0[6] = s * (r0[6] - r1[6] * m0), r0[7] = s * (r0[7] - r1[7] * m0);

			Matrix4x4 res;
			float* out = res.m;
			MAT(out,0,0) = r0[4]; MAT(out,0,1) = r0[5];
			MAT(out,0,2) = r0[6]; MAT(out,0,3) = r0[7];
			MAT(out,1,0) = r1[4]; MAT(out,1,1) = r1[5];
			MAT(out,1,2) = r1[6]; MAT(out,1,3) = r1[7];
			MAT(out,2,0) = r2[4]; MAT(out,2,1) = r2[5];
			MAT(out,2,2) = r2[6]; MAT(out,2,3) = r2[7];
			MAT(out,3,0) = r3[4]; MAT(out,3,1) = r3[5];
			MAT(out,3,2) = r3[6]; MAT(out,3,3) = r3[7];

#undef MAT
#undef SWAP_ROWS

			return res;
		}

		//  mults matrix on scalar
		Matrix4x4<T>& MultScalar(T d)
		{
			for (int i = 0; i < 4; i++)
			{
				m[i] *= d;
			}
			return *this;
		}

		/******************************************************
		* Set row in matrix
		* */
		void SetColumn(int column, const Vector4<T>& v)
		{
			for (int i = 0; i < 4; i++)
			{
				m[column * 4 + i] = v[i];
			}
		}

		void SetRow(int row, const Vector4<T>& v)
		{
			for (int i = 0; i < 4; i++)
			{
				m[i * 4 + row] = v[i];
			}
		}

		Vector4<T> GetRow(int row) const
		{
			return Vector4<T>(m[0 * 4 + row],
				m[1 * 4 + row],
				m[2 * 4 + row],
				m[3 * 4 + row]);
		}

		Vector4<T> GetColumn(int column) const
		{
			return Vector4<T>(m[column*4 + 0],
				m[column * 4 + 1],
				m[column * 4 + 2],
				m[column * 4 + 3]);
		}

		/*********************************************************
		* makes current matrix identity
		* **********************************************************/
		Matrix4x4<T> Identity()
		{
			int RowLength = 4;
			for (int i = 0; i < RowLength; i++)
			{
				for (int j = 0; j < RowLength; j++)
				{
					if (i == j)
						m[i * RowLength + j] = 1;
					else
						m[i * RowLength + j] = 0;
				}
			}
			return *this;
		}

		/*********************************************************
		* Transpose matrix
		*********************************************************/
		Matrix4x4<T> Transposed() const
		{
			Matrix4x4<T> res;
			res.SetColumn(0, Vector4<T>(m[0], m[4], m[8], m[12]));
			res.SetColumn(1, Vector4<T>(m[1], m[5], m[9], m[13]));
			res.SetColumn(2, Vector4<T>(m[2], m[6], m[10], m[14]));
			res.SetColumn(3, Vector4<T>(m[3], m[7], m[11], m[15]));

			return res;
		}

		System::string ToString() const
		{
			return System::string::Format(L"\n(%7.3f %7.3f %7.3f %7.3f)\n(%7.3f %7.3f %7.3f %7.3f)\n(%7.3f %7.3f %7.3f %7.3f)\n(%7.3f %7.3f %7.3f %7.3f)\n",
				m[0], m[4], m[8], m[12], m[1], m[5], m[9], m[13], m[2], m[6], m[10], m[14], m[3], m[7], m[11], m[15]);
		}

		bool Save(std::ostream& stream) const
		{
			stream.write(reinterpret_cast<const char*>(m), sizeof(m));
			return true;
		}

		bool Load(std::istream& stream)
		{
			stream.read(reinterpret_cast<char*>(m), sizeof(m));
			return true;
		}

		/*
		bool Save(System::Buffer& buffer) const
		{
		buffer.WriteBuffer(m, sizeof(m));
		}

		bool Load(System::Buffer& buffer)
		{
		buffer.ReadBuffer(m, sizeof(m));
		}
		*/

		Matrix4x4<T> operator *= (const Matrix4x4<T>& b)
		{
			Matrix4x4<T> a = *this;
			SetColumn(0, Vector4<T>(
			b[0] * a[0] + b[1] * a[4] + b[2] * a[8] + b[3] * a[12],
			b[0] * a[1] + b[1] * a[5] + b[2] * a[9] + b[3] * a[13],
			b[0] * a[2] + b[1] * a[6] + b[2] * a[10] + b[3] * a[14],
			b[0] * a[3] + b[1] * a[7] + b[2] * a[11] + b[3] * a[15]));
			SetColumn(1, Vector4<T>(
			b[4] * a[0] + b[5] * a[4] + b[6] * a[8] + b[7] * a[12],
			b[4] * a[1] + b[5] * a[5] + b[6] * a[9] + b[7] * a[13],
			b[4] * a[2] + b[5] * a[6] + b[6] * a[10] + b[7] * a[14],
			b[4] * a[3] + b[5] * a[7] + b[6] * a[11] + b[7] * a[15]));
			SetColumn(2, Vector4<T>(
			b[8] * a[0] + b[9] * a[4] + b[10] * a[8] + b[11] * a[12],
			b[8] * a[1] + b[9] * a[5] + b[10] * a[9] + b[11] * a[13],
			b[8] * a[2] + b[9] * a[6] + b[10] * a[10] + b[11] * a[14],
			b[8] * a[3] + b[9] * a[7] + b[10] * a[11] + b[11] * a[15]));
			SetColumn(3, Vector4<T>(
			b[12] * a[0] + b[13] * a[4] + b[14] * a[8] + b[15] * a[12],
			b[12] * a[1] + b[13] * a[5] + b[14] * a[9] + b[15] * a[13],
			b[12] * a[2] + b[13] * a[6] + b[14] * a[10] + b[15] * a[14],
			b[12] * a[3] + b[13] * a[7] + b[14] * a[11] + b[15] * a[15]));

			return *this;
		}
	};

	//  mult matrix
	template<class T>
	static Matrix4x4<T> operator + (const Matrix4x4<T>& a, const Matrix4x4<T>& b)
	{
		Matrix4x4<T> c;
		for (int i = 0; i < 16; i++)
		{
			c[i] = a[i] + b[i];
		}
		return c;
	}

	//  mult matrix
	template<class T>
	static Matrix4x4<T> operator * (const Matrix4x4<T>& a, const Matrix4x4<T>& b)
	{
		Matrix4x4<T> c;
		c.SetColumn(0, Vector4<T>(
			b[0] * a[0] + b[1] * a[4] + b[2] * a[8] + b[3] * a[12],
			b[0] * a[1] + b[1] * a[5] + b[2] * a[9] + b[3] * a[13],
			b[0] * a[2] + b[1] * a[6] + b[2] * a[10] + b[3] * a[14],
			b[0] * a[3] + b[1] * a[7] + b[2] * a[11] + b[3] * a[15]));
		c.SetColumn(1, Vector4<T>(
			b[4] * a[0] + b[5] * a[4] + b[6] * a[8] + b[7] * a[12],
			b[4] * a[1] + b[5] * a[5] + b[6] * a[9] + b[7] * a[13],
			b[4] * a[2] + b[5] * a[6] + b[6] * a[10] + b[7] * a[14],
			b[4] * a[3] + b[5] * a[7] + b[6] * a[11] + b[7] * a[15]));
		c.SetColumn(2, Vector4<T>(
			b[8] * a[0] + b[9] * a[4] + b[10] * a[8] + b[11] * a[12],
			b[8] * a[1] + b[9] * a[5] + b[10] * a[9] + b[11] * a[13],
			b[8] * a[2] + b[9] * a[6] + b[10] * a[10] + b[11] * a[14],
			b[8] * a[3] + b[9] * a[7] + b[10] * a[11] + b[11] * a[15]));
		c.SetColumn(3, Vector4<T>(
			b[12] * a[0] + b[13] * a[4] + b[14] * a[8] + b[15] * a[12],
			b[12] * a[1] + b[13] * a[5] + b[14] * a[9] + b[15] * a[13],
			b[12] * a[2] + b[13] * a[6] + b[14] * a[10] + b[15] * a[14],
			b[12] * a[3] + b[13] * a[7] + b[14] * a[11] + b[15] * a[15]));
		return c;
	}

	template<class T>
	static Vector4<T> operator * (const Matrix4x4<T>& m, const Vector4<T>& v)
	{
		return Vector4<T>(
			m[0]*v[0] + m[4]*v[1] + m[8]*v[2] + m[12]*v[3],
			m[1]*v[0] + m[5]*v[1] + m[9]*v[2] + m[13]*v[3],
			m[2]*v[0] + m[6]*v[1] + m[10]*v[2] + m[14]*v[3],
			m[3]*v[0] + m[7]*v[1] + m[11]*v[2] + m[15]*v[3]);
	}

	template<class T>
	static Vector3<T> operator * (const Matrix4x4<T>& m, const Vector3<T>& v)
	{
		return (m * Vector4<T>(v[0], v[1], v[2], T(1))).XYZ();
	}

	template<class T>
	const Matrix4x4<T> operator * (const Matrix4x4<T>& m, const T& v)
	{
		Math::Matrix4x4<T> res;
		for (int i = 0; i < 16; i++)
			res[i] = m[i]*v;
		return res;
	}

	template<class T>
	const Matrix4x4<T> operator * (const T& v, const Matrix4x4<T>& m)
	{
		Math::Matrix4x4<T> res;
		for (int i = 0; i < 16; i++)
			res[i] = m[i]*v;
		return res;
	}

	template<class T>
	std::wostream& operator << (std::wostream& stream, const Matrix4x4<T>& m)
	{
		std::streamsize old = stream.width(8);
		std::streamsize old_prec = stream.precision(5);
		for (int row = 0; row < 4; ++row)
		{
			stream << Tab();
			for (int col = 0; col < 4; ++col)
			{
				stream << std::fixed << m[col*4 + row] << '\t';
			}
			stream << std::endl;
		}
		stream.width(old);
		stream.precision(old_prec);
		return stream;
	}


	class PUNK_ENGINE_PUBLIC mat4 : public Matrix4x4<float>
	{
	public:
		mat4() : Matrix4x4<float> () {}
		mat4(const mat4& m) : Matrix4x4<float>(m) {}
		mat4(const Matrix4x4<float>& m) : Matrix4x4<float>(m) {}
	};

}

#endif
