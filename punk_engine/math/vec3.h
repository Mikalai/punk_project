#ifndef _H_VEC3_MATH
#define _H_VEC3_MATH

#include <istream>
#include <ostream>
#include <vector>

#include <memory.h>
#include <math.h>

#include "config.h"
#include "vec2.h"
#include "vec4.h"

namespace Math
{

	template<class T>
	class Vector3
	{
		static const int Size_c = 3;
		T m_v[Size_c];
	public:

		Vector3<T>(const Vector3<T>& vec)
		{
			m_v[0] = vec.m_v[0];
			m_v[1] = vec.m_v[1];
			m_v[2] = vec.m_v[2];
		}

		Vector3<T>()
		{
			memset(m_v, 0, sizeof(m_v));
		}

		Vector3<T>(T x, T y, T z)
		{
			m_v[0] = x;
			m_v[1] = y;
			m_v[2] = z;
		}

		Vector3<T>(const Vector3<T>& origin, const Vector3<T>& destination)
		{
			for (int i = 0; i < Size_c; i++)
			{
				m_v[i] = destination[i] - origin[i];
			}
		}

		const T& X() const
		{
			return m_v[0];
		}

		T& X() 
		{
			return m_v[0];
		}

		const T& Y() const
		{
			return m_v[1];
		}

		T& Y() 
		{
			return m_v[1];
		}

		const T& Z() const
		{
			return m_v[2];
		}

		T& Z() 
		{
			return m_v[2];
		}

		Vector3<T> Negated() const
		{
			return Vector3<T>(-m_v[0], -m_v[1], -m_v[2]);
		}

		Vector3<T>& Negate() 
		{
			m_v[0] = -m_v[0];
			m_v[1] = -m_v[1];
			m_v[2] = -m_v[2];

			return *this;
		}

		Vector3<T> ComponentMult(const Vector3<T>& v)
		{
			return Vector3<T>(m_v[0]*v[0], m_v[1]*v[1], m_v[2]*v[2]);
		}

		Vector4<T> ToHomogeneous() const
		{
			return Vector4<T>(m_v[0], m_v[1], m_v[2], T(1));
		}

		Vector2<T> XY() const
		{
			return Vector2<T>(m_v[0], m_v[1]);
		}
		
		Vector2<T> YX() const 
		{
			return Vector2<T>(m_v[1], m_v[0]);
		}
		
		Vector2<T> XZ() const
		{
			return Vector2<T>(m_v[0], m_v[2]);
		}

		Vector2<T> ZX() const
		{
			return Vector2<T>(m_v[2], m_v[0]);
		}

		Vector2<T> YZ() const
		{
			return Vector2<T>(m_v[1], m_v[2]);
		}

		Vector2<T> ZY() const
		{
			return Vector2<T>(m_v[2], m_v[1]);
		}

				Vector3<T> XYZ() const
		{
			return Vector3<T>(m_v[0], m_v[1], m_v[2]);
		}

		Vector3<T> XZY() const
		{
			return Vector3<T>(m_v[0], m_v[2], m_v[1]);
		}

		Vector3<T> YXZ() const
		{
			return Vector3<T>(m_v[1], m_v[0], m_v[2]);
		}

		Vector3<T> YZX() const 
		{
			return Vector3<T>(m_v[1], m_v[2], m_v[0]);
		}

		Vector3<T> ZXY() const
		{
			return Vector3<T>(m_v[2], m_v[0], m_v[1]);
		}

		Vector3<T> ZYX() const
		{
			return Vector3<T>(m_v[2], m_v[1], m_v[0]);
		}

		Vector3<T>& Nullify()
		{
			memset(m_v, 0, sizeof(m_v));
			return *this;
		}

		Vector3<T>& operator += (const Vector3<T>& vec)
		{
			m_v[0] += vec.m_v[0];
			m_v[1] += vec.m_v[1];
			m_v[2] += vec.m_v[2];
			return *this;
		}

		Vector3<T>& operator -= (const Vector3<T>& vec)
		{
			m_v[0] -= vec.m_v[0];
			m_v[1] -= vec.m_v[1];
			m_v[2] -= vec.m_v[2];
			return *this;
		}

		T& operator [] (int i)
		{
			return m_v[i];
		}

		operator T* ()
		{
			return m_v;
		}

		
		operator const T* () const
		{
			return m_v;
		}

		const T& operator [] (int i) const
		{
			return m_v[i];
		}

		T SquareLength() const
		{
			return m_v[0]*m_v[0]+m_v[1]*m_v[1]+m_v[2]*m_v[2];
		}

		T Length() const
		{
			return static_cast<T>(sqrtf((float)(m_v[0]*m_v[0]+m_v[1]*m_v[1]+m_v[2]*m_v[2])));
		}

		Vector3<T> Normalized() const
		{
			T length = Length();
			return *this / length;
		}

		Vector3<T>& Normalize()
		{
			T length = Length();
			m_v[0] /= length;
			m_v[1] /= length;
			m_v[2] /= length;
			return *this;
		}

		void Set(T x, T y, T z)
		{
			m_v[0] = x;
			m_v[1] = y;
			m_v[2] = z;
		}

		T Dot(const Vector3<T>& a) const
		{
			return m_v[0] * a.m_v[0] + m_v[1] * a.m_v[1] + m_v[2] * a.m_v[2];
		}

		Vector3<T> Cross(const Vector3<T>& vec) const
		{
			Vector3<T> v(
				m_v[1] * vec.m_v[2] - m_v[2] * vec.m_v[1],
				m_v[2] * vec.m_v[0] - m_v[0] * vec.m_v[2],
				m_v[0] * vec.m_v[1] - m_v[1] * vec.m_v[0]);
			return v;
		}

		Vector3<T>& operator = (const Vector3<T>& vec)
		{
			memcpy(m_v, vec.m_v, sizeof(m_v));
			return *this;
		}

		Vector3<T> operator -()
		{
			return Vector3<T>(-m_v[0], -m_v[1], -m_v[2]);
		}
		/**/

		System::string ToString() const
		{
			return System::string::Format(L"(%.3f; %.3f; %.3f)", m_v[0], m_v[1], m_v[2]);
		}

		void Save(std::ostream& stream) 
		{
			stream.write((char*)m_v, sizeof(m_v));
		}

		void Load(std::istream& stream) 
		{
			stream.read((char*)m_v, sizeof(m_v));
		}

	};

	template<class T>
	static Vector3<T> operator + (const Vector3<T>& a, const Vector3<T>& b)
	{
		return Vector3<T>(a[0] + b[0], a[1] + b[1], a[2] + b[2]);
	}

	template<class T>
	static Vector3<T> operator -(const Vector3<T>& a, const Vector3<T>& b)
	{
		return Vector3<T>(a[0] - b[0], a[1] - b[1], a[2] - b[2]);
	}

	template<class T>
	static Vector3<T> operator *(const Vector3<T>& a, T d)
	{
		return Vector3<T>(a[0] * d, a[1] * d, a[2] * d);
	}

	template<class T>
	static Vector3<T> operator *(T d, const Vector3<T>& a)
	{
		return Vector3<T>(a[0] * d, a[1] * d, a[2] * d);
	}

	template<class T>
	static Vector3<T> operator *(const Vector3<T>& a, const Vector3<T>& b)
	{
		return Vector3<T>(a[0] * b[0], a[1] * b[1], a[2] * b[2]);
	}

	template<class T>
	static Vector3<T> operator /(const Vector3<T>& a, T d)
	{
		return Vector3<T>(a[0] / d, a[1] / d, a[2] / d);
	}

	template<class T>
	static bool operator ==(const Vector3<T>& a, const Vector3<T>& b)
	{
		return a[0] == b[0] && a[1] == b[1] && a[2] == b[2];
	}

	template<class T>
	static bool operator !=(const Vector3<T>& a, const Vector3<T>& b)
	{
		return !(a == b);
	}

	//
	//	instantiated abstract class for some exported types
	//
	template class LIB_MATH Vector3<float>;
	template class LIB_MATH Vector3<int>;

	typedef Vector3<float> vec3;
	typedef Vector3<int> ivec3;	
}

#endif
