#ifndef _H_HELPER_MATH
#define _H_HELPER_MATH

#include "../config.h"
#include "vec3.h"
#include "vec4.h"
#include "mat4.h"
#include "mat3.h"
#include "smart_matrix.h"
#include "quat.h"

namespace Math
{
	PUNK_ENGINE const mat4 ProjectionMatrix(float fov, float aspect, float zNear, float zFar);
	PUNK_ENGINE const mat4 OrthoMatrix(float width, float height, float bottom, float top);
	PUNK_ENGINE const mat4 Rotate(vec4 v);
	PUNK_ENGINE const mat4 Translate(vec3 pos);
	PUNK_ENGINE const mat4 Scale(vec3 scale);
	PUNK_ENGINE const mat4 TargetCamera(vec3 eye, vec3 pos, vec3 up);
	PUNK_ENGINE const mat4 FreeCamera(vec3 pos, vec3 dir, vec3 up);
	PUNK_ENGINE const mat4 RotationMatrixFromQuaternion(const quat& q);
	PUNK_ENGINE const mat3 NormalMatrixFromWorldView(const mat4& worldView);

	//	used to find ceter of the mass of the object
	PUNK_ENGINE const vec3 CalculateAverage(const float* points, int count, unsigned offset);
	PUNK_ENGINE const mat3 CreateCovarianceMatrix(const float* points, int count, unsigned offset);
	PUNK_ENGINE bool DiagonalizeMatrix(const mat3& m, mat3& res);
	PUNK_ENGINE bool EigenValues(const mat3& m, vec3& res);
	PUNK_ENGINE bool EigenVectors(const mat3& m, const vec3& value, vec3 res[3]);

	PUNK_ENGINE bool SymmetricEigenSystem(const mat3& m, vec3& value, mat3& r);

	//	used to find native axis of the point set
	PUNK_ENGINE bool CalculateNativeAxis(const float* points, int count, unsigned offset, vec3& r, vec3& s, vec3& t);
	PUNK_ENGINE bool YawPitchRollToUpDirection(float yaw, float pitch, float roll, vec3& up, vec3& dir);

	template<class T>
	const Quaternion<T> Matrix4x4ToQuaternion(const Matrix4x4<T>& m)
	{
		T t = m[0] + m[5] + m[10] + T(1);
		if (t > 0)
		{
			T s = T(0.5) / (T)sqrtf((float)t);
			T w = T(0.25) / s;
			T x = (m[6] - m[9]) * s;
			T y = (m[8] - m[2]) * s;
			T z = (m[1] - m[4]) * s;
			return Quaternion<T>(w, x, y, z);
		}
		int Max = 0;
		for (int i = 0; i < 3; i++)
		{
			if (m[Max*4 + Max] < m[i*4 + i])
				Max = i;
		}

		switch(Max)
		{
		case 0:
			{
				T s = sqrt(T(1.0) + m[0] - m[5] - m[10]) * T(2.0);
				T x = T(0.5) / s;
				T y = (m[1] + m[4]) / s;
				T z = (m[2] + m[8]) / s;
				T w = (m[6] + m[9]) / s;
				return Quaternion<T>(w, x, y, z);
			}
		case 1:
			{
				T s = sqrt(T(1.0) + m[5] - m[0] - m[10]) * T(2.0);
				T x = (m[1] + m[4]) / s;
				T y = T(0.5) / s;
				T z = (m[6] + m[9]) / s;
				T w = (m[2] + m[8]) / s;
				return Quaternion<T>(w, x, y, z);
			}
		case 2:
			{
				T s = sqrt(T(1.0) + m[10] - m[0] - m[5]) * T(2.0);
				T x = (m[2] + m[8]) / s;
				T y = (m[6] + m[9]) / s;
				T z = T(0.5) / s;
				T w = (m[1] + m[4]) / s;
				return Quaternion<T>(w, x, y, z);
			}
		default:
			out_message() << m.ToString() << std::endl;
			out_message() << "Max is " << Max << std::endl;
			out_error() << L"Can't convert matrix to quaternion" << std::endl;
		}
	}

	template<class T>
	const Matrix4x4<T> QuaternionToMatrix4x4(const Quaternion<T>& q)
	{
		Matrix4x4<T> m;
		T xx = q.X()*q.X();
		T xy = q.X()*q.Y();
		T xz = q.X()*q.Z();
		T xw = q.X()*q.W();

		T yy = q.Y()*q.Y();
		T yz = q.Y()*q.Z();
		T yw = q.Y()*q.W();

		T zz = q.Z()*q.Z();
		T zw = q.Z()*q.W();

		m[0] = T(1.0) - T(2.0) * (yy + zz);
		m[1] = T(2.0) * (xy - zw);
		m[2] = T(2.0) * (xz + yw);

		m[4] = T(2.0) * (xy + zw);
		m[5] = T(1.0) - T(2.0) * (xx + zz);
		m[6] = T(2.0) * (yz - xw);

		m[8] = T(2.0) * (xz - yw);
		m[9] = T(2.0) * (yz + xw);
		m[10] = T(1.0) - T(2.0) * (xx + yy);
		m[3] = m[7] = m[11] = m[12] = m[13] = m[14] = T(0.0);
		m[15] = T(1.0);

		return m.Transposed();
	}

	template<class T>
	inline int Sign(T x)
	{
		return (x == T(0) ? 0 : ((x < 0) ? -1 : 1));
	}

	template<class T>
	inline T Abs(T x)
	{
		return abs(x);
	}

	template<class T>
	inline T Floor(T x)
	{
		return floor(x);
	}

	template<class T>
	inline T Fract(T x)
	{
		return x - Floor(x);
	}

	template<class T>
	inline T Mod(T x, T y)
	{
		return x - y*Floor(x/y);
	}

	template<class T>
	inline T Step(T edge, T x)
	{
		if (x < edge)
			return T(0);
		return T(1);
	}

	template<class T>
	T SmoothStep(T edge0, T edge1, T x)
	{
		T t = Clamp((x-edge0)/(edge1-edge0), T(0), T(1));
		return t*t*(T(3)-T(2)*t);
	}

	template<class T>
	T RoundUp(T value, T ratio)
	{
		T rest = value % ratio;
		if (rest == 0)
			return value;
		else
			return value + ratio - rest;
	}

	template<class T>
	inline T Min(T x, T y)
	{
		return x < y ? x : y;
	}

	template<class T>
	inline T Max(T x, T y)
	{
		return x > y ? x : y;
	}

	template<class T>
	inline T Min(T a, T b, T c)
	{
		return Min(a, Min(b, c));
	}

	template<class T>
	inline T Max(T a, T b, T c)
	{
		return Max(a, Max(b, c));
	}

	template<class T>
	T Clamp(T min_val, T max_val, T x)
	{
		return Min(Max(x, min_val), max_val);
	}

	template<class T>
	inline T Refract(T I, T N, float eta)
	{
		float k = 1.0f - eta*eta*(1.0f - N.Dot(I) * N.Dot(I));
		if (k < 0.0f)
			return T(0.0f);
		else
			return eta*I-(eta*N.Dot(I)+sqrt(k))*N;
	}

	template<class T>
	inline T Reflect(T I, T N)
	{
		return I - N.Dot(N, I) * N;
	}

	template<class T>
	inline T FaceForward(T N, T I, T Nref)
	{
		if (Nref.Dot(I) < 0)
			return N;
		return -N;
	}
	template<class T>
	inline T Mix(T x, T y, float a)
	{
		return x*(1-a)+y*a;
	}
	template<class T>
	Vector3<T> CalculateNormal(const Vector3<T>& p1, const Vector3<T>& p2, const Vector3<T>& p3)
	{
		return ((p2-p1).Cross(p3-p1)).Normalize();
	}

	template<class T>
	static void CalculateTBN(const Vector3<T>& p1, const Vector3<T>& p2, const Vector3<T>& p3,
		const Vector2<T>& tex1, const Vector2<T>& tex2, const Vector2<T>& tex3,
		Vector3<T>& tng, Vector3<T>& btn, Vector3<T>& nrm, T& mm)
	{
		nrm = CalculateNormal(p1, p2, p3);
		Matrix<T> s(2,2);
		s.At(0,0) = (tex2 - tex1)[0];
		s.At(0,1) = (tex2 - tex1)[1];
		s.At(1,0) = (tex3 - tex1)[0];
		s.At(1,1) = (tex3 - tex1)[1];

		Matrix<T> q(2, 3);
		q.At(0,0) = (p2 - p1)[0];
		q.At(0,1) = (p2 - p1)[1];
		q.At(0,2) = (p2 - p1)[2];
		q.At(1,0) = (p3 - p1)[0];
		q.At(1,1) = (p3 - p1)[1];
		q.At(1,2) = (p3 - p1)[2];

		Matrix<T> tb = s.Inversed()*q;

		tng[0] = tb.At(0,0);
		tng[1] = tb.At(0,1);
		tng[2] = tb.At(0,2);

		btn[0] = tb.At(1,0);
		btn[1] = tb.At(1,1);
		btn[2] = tb.At(1,2);

		if (btn.Length()==0 || tng.Length() == 0)
		{
			nrm.Normalize();
			mm = 1;
		}
		else
		{
			//
			//	gram-shmidt normalization
			//
			nrm.Normalize();
			tng = (tng - tng.Dot(nrm)*nrm).Normalize();
			btn = (btn - btn.Dot(nrm)*nrm - btn.Dot(tng)*tng).Normalize();

			Matrix<T> m(3,3);
			m.At(0,0) = tng[0]; m.At(0,1) = tng[1]; m.At(0,2) = tng[2];
			m.At(1,0) = btn[0]; m.At(1,1) = btn[1]; m.At(1,2) = btn[2];
			m.At(2,0) = nrm[0]; m.At(2,1) = nrm[1]; m.At(2,2) = nrm[2];

			mm = m.Determinant();/**/
		}
	}

}

#endif
