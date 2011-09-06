#ifndef _H_QUAT_MATH
#define _H_QUAT_MATH

#include <cmath>
#include <stdio.h>
#include "../system/string.h"
#include "vec3.h"

namespace Math
{
	template<class T> class Matrix4x4;

	template<class T>
	class Quaternion
	{
		T m_scalar;
		Vector3<T> m_vec;
	public:

		Quaternion() : m_scalar(0), m_vec(0,0,0) {}
		Quaternion(T w, T x, T y, T z) : m_scalar(w), m_vec(x, y, z) {}

		Quaternion(T angle, const Vector3<T>& axis)
		{
			m_scalar = std::cos(angle / 2.0);
			m_vec[0] = axis[0] * std::sin(angle / 2.0);
			m_vec[1] = axis[1] * std::sin(angle / 2.0);
			m_vec[2] = axis[2] * std::sin(angle / 2.0);

			Normalize();
		}

		T& Scalar()
		{
			return m_scalar;
		}

		Vector3<T>& Vector()
		{
			return m_vec;
		}


		const T& Scalar() const
		{
			return m_scalar;
		}

		const Vector3<T>& Vector() const
		{
			return m_vec;
		}

		T& operator [] (int i)
		{
			if (i == 0)
				return m_scalar;
			if (i < 4)
				return m_vec[i-1];
		}

		const T& operator[] (int i) const
		{
			if (i == 0)
				return m_scalar;

			if (i < 4)
				return m_vec[i-1];

			throw MathIndexOutOfRange();
		}

		T& W() 
		{
			return m_scalar;
		}

		const T& W() const
		{
			return m_scalar;
		}

		T& X() 
		{
			return m_vec[0];
		}

		const T& X() const
		{
			return m_vec[0];
		}

		T& Y() 
		{
			return m_vec[1];
		}

		const T& Y() const
		{
			return m_vec[1];
		}

		T& Z() 
		{
			return m_vec[2];
		}

		const T& Z() const
		{
			return m_vec[2];
		}

		Quaternion<T> Conjugated() const
		{
			return Quaternion(m_scalar, m_vec.Negated()).Normalized();
		}

		Quaternion<T>& Conjugate()
		{
			m_vec.Negate();
			Normalize();
			return *this;
		}

		Quaternion<T>& Normalize() 
		{
			T l = Length();
			m_scalar /= l;
			m_vec[0] /= l;
			m_vec[1] /= l;
			m_vec[2] /= l;

			return *this;
		}

		Quaternion<T> Normalized() const
		{
			T l = Length();
			return Quaternion(m_scalar / l, m_vec[0] / l, m_vec[1] / l, m_vec[2] / l);
		}

		T Length() const
		{
			return std::sqrt(m_scalar*m_scalar + m_vec.SquareLength());
		}

		T SquareLength() const
		{
			return m_scalar*m_scalar + m_vec.SquareLength();
		}

		const wchar_t* ToString() const
		{
			System::string::Format(L"[%f, (%f; %f, %f)]", m_scalar, m_vec[0], m_vec[1], m_vec[2]);
		}

		Matrix4x4<T> ToMatrix4x4() const
		{
			Matrix4x4<T> m;
			T xx = m_vec.X()*m_vec.X();
			T xy = m_vec.X()*m_vec.Y();
			T xz = m_vec.X()*m_vec.Z();
			T xw = m_vec.X()*m_scalar;

			T yy = m_vec.Y()*m_vec.Y();
			T yz = m_vec.Y()*m_vec.Z();
			T yw = m_vec.Y()*m_scalar;

			T zz = m_vec.Z()*m_vec.Z();
			T zw = m_vec.Z()*m_scalar;

			m[0] = 1.0 - 2.0 * (yy + zz);
			m[1] = 2.0 * (xy - zw);
			m[2] = 2.0 * (xz + yw);

			m[4] = 2.0 * (xy + zw);
			m[5] = 1.0 - 2.0 * (xx + zz);
			m[6] = 2.0 * (yz - xw);

			m[8] = 2.0 * (xz - yw);
			m[9] = 2.0 * (yz + xw);
			m[10] = 1.0 - 2.0 * (xx + yy);
			m[3] = m[7] = m[11] = m[12] = m[13] = m[14] = 0.0;
			m[15] = 1.0;

			return m.Transposed();
		}
	};

	template<class T>
	Quaternion<T> operator * (const Quaternion<T>& q1, const Quaternion<T>& q2)
	{
		T scalar = q1.Scalar() * q2.Scalar() - q1.Vector().Dot(q2.Vector());
		Vector3<T> vector = q1.Scalar() * q2.Vector() + q2.Scalar()*q1.Vector() + q1.Vector().Cross(q2.Vector());
		return Quaternion<T>(scalar, vector[0], vector[1], vector[2]);
	}

	typedef Quaternion<float> quat;
}

/*

T Sign() const
{
return *this
}

T Dot(const Quaternion<T>& q) const
{
return m_v[1]*q[1] + m_v[2]*q[2] + m_v[3]*q[3] + m_v[0]*q[0];
}

const wchar_t* ToString() const
{
swprintf(m_buffer, L"(%.3f; %.3f, %.3f; %.3f)", m_v[0], m_v[1], m_v[2], m_v[3]);
return m_buffer;
}

T& operator [] (int i)
{
return m_v[i];
}

const T& operator[] (int i) const
{
return m_v[i];
}

T& W() 
{
return m_v[0];
}

const T& W() const
{
return m_v[0];
}

T& X() 
{
return m_v[1];
}

const T& X() const
{
return m_v[1];
}

T& Y() 
{
return m_v[2];
}

const T& Y() const
{
return m_v[2];
}

T& Z() 
{
return m_v[3];
}

const T& Z() const
{
return m_v[3];
}

void Save(System::Buffer& buffer) const
{
buffer.WriteBuffer(m_v, sizeof(m_v));
}

void Load(System::Buffer& buffer)
{
buffer.ReadBuffer(m_v, sizeof(m_v));
}
};

template<class T>
wchar_t Quaternion<T>::m_buffer[128];

template<class T>
Quaternion<T> operator + (const Quaternion<T>& q1, const Quaternion<T>& q2)
{
return Quaternion<T> (q1[0]+q2[0] ,q1[1]+q2[1], q1[2]+q2[2], q1[3]+q2[3]);
}

template<class T>
Quaternion<T> operator * (const Quaternion<T>& q1, const Quaternion<T>& q2)
{
Vector3<T> u(q1[1], q1[2], q1[3]);
Vector3<T> v(q2[1], q2[2], q2[3]);
T a = q1[0];
T b = q2[0];

Vector3<T> r = a*v + b*u + u.Cross(v);

Quaternion<T> q;
q[0] = a*b - u.Dot(v);
q[1] = r[0];
q[2] = r[1];
q[3] = r[2];

return q;//.Normalized();

/*
T v[4];
T A, B, C, D, E, F, G, H;

A = (q1[0] + q1[1]) * (q2[0] + q2[1]);
B = (q1[3] - q1[2]) * (q2[2] - q2[3]);
C = (q1[1] - q1[0]) * (q2[2] + q2[3]);
D = (q1[2] + q1[3]) * (q2[1] - q2[0]);
E = (q1[1] + q1[3]) * (q2[1] + q2[2]);
F = (q1[1] - q1[3]) * (q2[1] - q2[2]);
G = (q1[0] + q1[2]) * (q2[0] - q2[3]);
H = (q1[0] - q1[2]) * (q2[0] + q2[3]);

v[0] = B + (-E - F + G + H) * 0.5;
v[1] = A - ( E + F + G + H) * 0.5; 
v[2] =-C + ( E - F + G - H) * 0.5;
v[3] =-D + ( E - F - G + H) * 0.5;

return Quaternion<T>(v[0], v[1], v[2], v[3]);
}	
/*
template<class T>
Quaternion<T> operator * (const Quaternion<T>& q, T s)
{
return Quaternion<T>(q[0]*s, q[1]*s, q[2]*s, q[3]*s);
}

template<class T>
Quaternion<T> operator * (T s, const Quaternion<T>& q)
{
return Quaternion<T>(q[0]*s, q[1]*s, q[2]*s, q[3]*s);
}

template<class T>
Quaternion<T> operator / (const Quaternion<T>& q, T s)
{
return Quaternion<T>(q[0]/s, q[1]/s, q[2]/s, q[3]/s);
}

template<class T>
Vector3<T> operator * (const Quaternion<T>& q, const Vector3<T>& v)
{
Quaternion<T> q2(0, v[0], v[1], v[2]);
q2 = q * q2;
return Vector3<T>(q2[1], q2[2], q2[3]);
}

template<class T>
Vector3<T> operator * (const Vector3<T>& v, const Quaternion<T>& q)
{
Quaternion<T> q2(0, v[0], v[1], v[2]);
q2 = q2 * q;
return Vector3<T>(q2[1], q2[2], q2[3]);
}

template<class T>
Quaternion<T> operator / (T s, const Quaternion<T>& q)
{
return Quaternion<T>(q[0]/s, q[1]/s, q[2]/s, q[3]/s);
}

template<class T>
Quaternion<T> LinearInterpolation(const Quaternion<T>& q1, const Quaternion<T>& q2, const T& t)
{
Quaternion<T> res = (1-t)*q1 + t*q2;
return res.Normalized();
}

template<class T>
Quaternion<T> SphericalLinearInterpolation(const Quaternion<T>& q1, const Quaternion<T>& q2, const T& t)
{
T theta = std::acos(q1.Dot(q2));
return std::sin(theta*(1-t))/std::sin(theta)*q1 + std::sin(theta*t)/std::sin(theta)*q2;
}

}


*/
#endif
