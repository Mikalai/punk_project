#ifndef _H_VEC3_MATH1
#define _H_VEC3_MATH1

#include <istream>
#include <ostream>
#include <vector>

#include <memory.h>
#include <math.h>

#include "../config.h"
#include "vec2.h"

namespace Math
{
	template<class T>
	class Vector3
	{
		static const int Size_c = 3;
		static constexpr float Eps = 1e-3;
		T m_v[Size_c];
	public:

		static const Vector3<T> Null() { return Vector3<T>(0,0,0); }

		Vector3<T>(const Vector3<T>& vec)
		{
			auto x = vec.m_v[0];
			auto y = vec.m_v[1];
			auto z = vec.m_v[2];
			m_v[0] = fabs(x) < Eps ? 0 : x;
			m_v[1] = fabs(y) < Eps ? 0 : y;
			m_v[2] = fabs(z) < Eps ? 0 : z;
		}

		Vector3<T>()
		{
			memset(m_v, 0, sizeof(m_v));
		}

		Vector3<T>(T x, T y, T z)
		{
			m_v[0] = fabs(x) < Eps ? 0 : x;
			m_v[1] = fabs(y) < Eps ? 0 : y;
			m_v[2] = fabs(z) < Eps ? 0 : z;
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

		Vector3<T>& Chop(T eps = T(0.00001))
		{
			for (int i = 0; i != 3; ++i)
				if (fabs(float(m_v[i])) < eps)
					m_v[i] = T(0);
			return *this;
		}

		const Vector3<T> ComponentMult(const Vector3<T>& v) const
		{
			return Vector3<T>(m_v[0]*v[0], m_v[1]*v[1], m_v[2]*v[2]);
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

		Vector3<T>& operator *= (T value)
		{
			m_v[0] *= value;
			m_v[1] *= value;
			m_v[2] *= value;
			return *this;
		}

		Vector3<T>& operator /= (T value)
		{
			m_v[0] /= value;
			m_v[1] /= value;
			m_v[2] /= value;
			return *this;
		}

		T& operator [] (int i)
		{
			return m_v[i];
		}

//		operator T* ()
//		{
//			return m_v;
//		}


//		operator const T* () const
//		{
//			return m_v;
//		}

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
			m_v[0] = fabs(x) < Eps ? 0 : x;
			m_v[1] = fabs(y) < Eps ? 0 : y;
			m_v[2] = fabs(z) < Eps ? 0 : z;
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
            return System::string("({0}; {1}; {2})").arg(m_v[0]).arg(m_v[1]).arg(m_v[2]);
		}

		bool Save(std::ostream& stream) const
		{
			stream.write((char*)m_v, sizeof(m_v));
			return true;
		}

		bool Load(std::istream& stream) 
		{
			stream.read((char*)m_v, sizeof(m_v));
			return true;
		}

		std::wostream& out_formatted(std::wostream& stream)
		{
			stream << ToString().Data();
			return stream;
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

	class PUNK_ENGINE_API vec3 : public Vector3<float> 
	{
	public:
		vec3() : Vector3<float>() {}
		vec3(float x, float y, float z) : Vector3<float>(x, y, z) {}
		vec3(const vec3& vec) : Vector3<float>(vec) {}
		vec3(const Vector3<float>& vec) : Vector3<float>(vec) {}
	};

	class PUNK_ENGINE_API ivec3 : public Vector3<int> 
	{
	public:
		ivec3() : Vector3<int>() {}
		ivec3(int x, int y, int z) : Vector3<int>(x, y, z) {}
		ivec3(const ivec3& vec) : Vector3<int>(vec) {}
		ivec3(const Vector3<int>& vec) : Vector3<int>(vec) {}
	};	

	typedef std::vector<vec3> PointArray;
}

#endif
