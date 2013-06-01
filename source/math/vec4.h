/*
MODULE FOR WORKING WITH 4 DIMENSIONAL VECTOR
AUTHOR: Mikalai Abramau
*/

#ifndef _H_VEC4_MATH
#define _H_VEC4_MATH

#include <iosfwd>
#include <stdio.h>
#include <cmath>

#include "../string/string.h"
#include "vec3.h"
#include "vec2.h"

namespace Math
{
	template<class T>
	class  Vector4
	{		
		static const int Size_c = 4;
		static constexpr float Eps = 1e-3;
		T m_v[Size_c];
	public:

		Vector4<T>(const Vector4<T>& vec)
		{
			memcpy(m_v, vec.m_v, sizeof(m_v));
		}

		Vector4<T>()
		{
			memset(m_v, 0, sizeof(m_v));
		}

		Vector4<T>(T x, T y, T z, T w)
		{
			m_v[0] = (fabs(x) < Eps) ? 0 : x;
			m_v[1] = (fabs(y) < Eps) ? 0 : y;
			m_v[2] = (fabs(z) < Eps) ? 0 : z;
			m_v[3] = (fabs(w) < Eps) ? 0 : w;
		}

		Vector4<T>(T x)
		{
			m_v[0] = (fabs(x) < Eps) ? 0 : x;
			m_v[1] = (fabs(x) < Eps) ? 0 : x;
			m_v[2] = (fabs(x) < Eps) ? 0 : x;
			m_v[3] = (fabs(x) < Eps) ? 0 : x;
		}

		Vector4<T>(const Vector4<T>& origin, const Vector4<T>& destination)
		{
			for (int i = 0; i < Size_c; i++)
			{
				float v = destination[i] - origin[i];
				m_v[i] = (fabs(v) < Eps) ? 0 : v;
			}
		}

		Vector4<T>(const Vector3<T>& vec, T d)
		{
			float x = vec.X();
			float y = vec.Y();
			float z = vec.Z();
			float w = d;
			m_v[0] = (fabs(x) < Eps) ? 0 : x;
			m_v[1] = (fabs(y) < Eps) ? 0 : y;
			m_v[2] = (fabs(z) < Eps) ? 0 : z;
			m_v[3] = (fabs(w) < Eps) ? 0 : w;
		}

		T& operator[] (int i)
		{
			return m_v[i];
		}

		const T& operator[] (int i) const
		{
			return m_v[i];
		}

		operator T* ()
		{
			return m_v;
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

		const T& W() const
		{
			return m_v[3];
		}

		T& W() 
		{
			return m_v[3];
		}

		Vector4<T>& operator = (const Vector4<T>& vec)
		{
#ifdef _WIN32
			memcpy_s(m_v, sizeof(m_v), vec.m_v, sizeof(m_v));
#else
            memcpy(m_v, vec.m_v, sizeof(m_v));
#endif
			return *this;
		}

		Vector4<T>& operator /= (const T& v)
		{
			for (int i = 0; i < Size_c; i++)
			{
                float t = m_v[i] / v;
                m_v[i] = (fabs(v) < Eps) ? 0 : t;
			}
			return *this;
		}

        Vector4<T>& operator *= (const T& v)
        {
            for (int i = 0; i < Size_c; i++)
            {
                float t = m_v[i] * v;
                m_v[i] = (fabs(v) < Eps) ? 0 : t;
            }
            return *this;
        }

		T Length()
		{
			//
			//	it will always convert to float
			//
			return static_cast<T>(sqrtf(float(m_v[0]*m_v[0]+m_v[1]*m_v[1]+m_v[2]*m_v[2]+m_v[3]*m_v[3])));
		}

		Vector4<T>& Normalize()
		{
			double length = Length();
			for (int i = 0; i < Size_c; i++)
			{
				m_v[i] /= (T)length;
			}
			return *this;
		}

		const T Dot(const Vector4<T>& vec) const
		{
			return m_v[0] * vec.m_v[0] + m_v[1] * vec.m_v[1] + m_v[2] * vec.m_v[2] + m_v[3] * vec.m_v[3];
		}

		void Set(T x)
		{
			m_v[0] = (fabs(x) < Eps) ? 0 : x;
			m_v[1] = (fabs(x) < Eps) ? 0 : x;
			m_v[2] = (fabs(x) < Eps) ? 0 : x;
			m_v[3] = (fabs(x) < Eps) ? 0 : x;
		}

		void Set(T x, T y, T z, T w)
		{
			m_v[0] = (fabs(x) < Eps) ? 0 : x;
			m_v[1] = (fabs(y) < Eps) ? 0 : y;
			m_v[2] = (fabs(z) < Eps) ? 0 : z;
			m_v[3] = (fabs(w) < Eps) ? 0 : w;
		}

        const Vector4<T> ComponentMul(const Vector4<T>& v)
		{
			return Vector4<T>(m_v[0]*v[0], m_v[1]*v[1], m_v[2]*v[2], m_v[3]*v[3]);
		}

        const System::string ToString() const
		{
			return System::string::Format(L"(%.3f; %.3f; %.3f; %.3f)", m_v[0], m_v[1], m_v[2], m_v[3]);
		}

        const Vector2<T> XY() const
		{
			return Vector2<T>(m_v[0], m_v[1]);
		}

        const Vector2<T> YX() const
		{
			return Vector2<T>(m_v[1], m_v[0]);
		}

        const Vector2<T> XZ() const
		{
			return Vector2<T>(m_v[0], m_v[2]);
		}

        const Vector2<T> ZX() const
		{
			return Vector2<T>(m_v[2], m_v[0]);
		}

        const Vector2<T> YZ() const
		{
			return Vector2<T>(m_v[1], m_v[2]);
		}

        const Vector2<T> ZY() const
		{
			return Vector2<T>(m_v[2], m_v[1]);
		}

        const Vector2<T> XW() const
		{
			return Vector2<T>(m_v[0], m_v[3]);
		}

        const Vector2<T> WX() const
		{
			return Vector2<T>(m_v[3], m_v[0]);
		}

        const Vector2<T> WZ() const
		{
			return Vector2<T>(m_v[3], m_v[2]);
		}

        const Vector2<T> ZW() const
		{
			return Vector2<T>(m_v[2], m_v[3]);
		}

        const Vector2<T> YW() const
		{
			return Vector2<T>(m_v[1], m_v[3]);
		}

        const Vector2<T> WY() const
		{
			return Vector2<T>(m_v[3], m_v[1]);
		}

        const Vector3<T> XYZ() const
		{
			return Vector3<T>(m_v[0], m_v[1], m_v[2]);
		}

        const Vector3<T> XZY() const
		{
			return Vector3<T>(m_v[0], m_v[2], m_v[1]);
		}

        const Vector3<T> YXZ() const
		{
			return Vector3<T>(m_v[1], m_v[0], m_v[2]);
		}

        const Vector3<T> YZX() const
		{
			return Vector3<T>(m_v[1], m_v[2], m_v[0]);
		}

        const Vector3<T> ZXY() const
		{
			return Vector3<T>(m_v[2], m_v[0], m_v[1]);
		}

        const Vector3<T> ZYX() const
		{
			return Vector3<T>(m_v[2], m_v[1], m_v[0]);
		}

        const Vector4<T> XYZW() const
		{
			return Vector4<T>(m_v[0], m_v[1], m_v[2], m_v[3]);
		}

        const Vector4<T> XYWZ() const
		{
			return Vector4<T>(m_v[0], m_v[1], m_v[3], m_v[2]);
		}

        const Vector4<T> XZYW() const
		{
			return Vector4<T>(m_v[0], m_v[2], m_v[1], m_v[3]);
		}

        const Vector4<T> XZWY() const
		{
			return Vector4<T>(m_v[0], m_v[2], m_v[3], m_v[1]);
		}

        const Vector4<T> XWYZ() const
		{
			return Vector4<T>(m_v[0], m_v[3], m_v[1], m_v[2]);
		}

        const Vector4<T> XWZY() const
		{
			return Vector4<T>(m_v[0], m_v[3], m_v[2], m_v[1]);
		}

        const Vector4<T> YXZW() const
		{
			return Vector4<T>(m_v[1], m_v[0], m_v[2], m_v[3]);
		}

        const Vector4<T> YXWZ() const
		{
			return Vector4<T>(m_v[1], m_v[0], m_v[3], m_v[2]);
		}

        const Vector4<T> YZXW() const
		{
			return Vector4<T>(m_v[1], m_v[2], m_v[0], m_v[3]);
		}

        const Vector4<T> YZWX() const
		{
			return Vector4<T>(m_v[1], m_v[2], m_v[3], m_v[0]);
		}

        const Vector4<T> YWZX() const
		{
			return Vector4<T>(m_v[1], m_v[3], m_v[2], m_v[0]);
		}

        const Vector4<T> YWXZ() const
		{
			return Vector4<T>(m_v[1], m_v[3], m_v[0], m_v[2]);
		}


        const Vector4<T> ZXYW() const
		{
			return Vector4<T>(m_v[2], m_v[0], m_v[1], m_v[3]);
		}

        const Vector4<T> ZXWY() const
		{
			return Vector4<T>(m_v[2], m_v[0], m_v[3], m_v[1]);
		}

        const Vector4<T> ZYXW() const
		{
			return Vector4<T>(m_v[2], m_v[1], m_v[0], m_v[3]);
		}

        const Vector4<T> ZYWX() const
		{
			return Vector4<T>(m_v[2], m_v[1], m_v[3], m_v[0]);
		}

        const Vector4<T> ZWXY() const
		{
			return Vector4<T>(m_v[2], m_v[3], m_v[0], m_v[1]);
		}

        const Vector4<T> ZWYX() const
		{
			return Vector4<T>(m_v[2], m_v[3], m_v[1], m_v[0]);
		}

        const Vector4<T> WXYZ() const
		{
			return Vector4<T>(m_v[3], m_v[0], m_v[1], m_v[2]);
		}

        const Vector4<T> WXZY() const
		{
			return Vector4<T>(m_v[3], m_v[0], m_v[2], m_v[1]);
		}

        const Vector4<T> WYXZ() const
		{
			return Vector4<T>(m_v[3], m_v[1], m_v[0], m_v[2]);
		}

        const Vector4<T> WYZX() const
		{
			return Vector4<T>(m_v[3], m_v[1], m_v[2], m_v[0]);
		}

        const Vector4<T> WZXY() const
		{
			return Vector4<T>(m_v[3], m_v[2], m_v[0], m_v[1]);
		}

        const Vector4<T> WZYX() const
		{
			return Vector4<T>(m_v[3], m_v[2], m_v[1], m_v[0]);
		}

		static bool TestModule()
		{
			float x = 1;
			float y = 2;
			float z = 3;
			float w = 4;

			Vector4<float> v(x,y,z,w);

			if (v.X() != x)
			{
				return false;
			}

			if (v.Y() != y)
			{
				return false;
			}

			if (v.Z() != z)
			{
				return false;
			}

			if (v.W() != w)
			{
				return false;
			}

			if (v.XY() != Vector2<float>(x, y))
			{
				return false;
			}

			if (v.XZ() != Vector2<float>(x, z))
			{
				return false;
			}

			if (v.XW() != Vector2<float>(x, w))
			{
				return false;
			}

			if (v.YX() != Vector2<float>(x, w))
			{
				return false;
			}
			return true;
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
	};

	template<class T>
	static Vector4<T> operator +(const Vector4<T>& a, const Vector4<T>& b)
	{
		return Vector4<T>(a[0] + b[0], a[1] + b[1], a[2] + b[2], a[3] + b[3]);
	}

	template<class T>
	static Vector4<T> operator -(const Vector4<T>& a, const Vector4<T>& b)
	{
		return Vector4<T>(a[0] - b[0], a[1] - b[1], a[2] - b[2], a[3] - b[3]);
	}

	template<class T>
	static Vector4<T> operator *(const Vector4<T>& a, T d)
	{
		return Vector4<T>(a[0] * d, a[1] * d, a[2] * d, a[3] * d);
	}

	template<class T>
	static Vector4<T> operator *(T d, const Vector4<T>& a)
	{
		return Vector4<T>(a[0] * d, a[1] * d, a[2] * d, a[3] * d);
	}

	template<class T>
	static Vector4<T> operator /(const Vector4<T>& a, double d)
	{
		return new Vector4<T>(a[0] / d, a[1] / d, a[2] / d, a[3] / d);
	}

	template<class T>
	static bool operator ==(const Vector4<T>& a, const Vector4<T>& b)
	{
		return a[0] == b[0] && a[1] == b[1] && a[2] == b[2] && a[3] == b[3];
	}

	template<class T>
	static bool operator !=(const Vector4<T>& a, const Vector4<T>& b)
	{
		return !(a == b);
	}

	class PUNK_ENGINE_PUBLIC vec4 : public Vector4<float> 
	{
	public:
		vec4() : Vector4<float>() {}
		vec4(float x, float y, float z, float w) : Vector4<float>(x, y, z, w) {}
		vec4(float x) : Vector4<float>(x) {}
		vec4(const vec4& origin, const vec4& destination) : Vector4<float>(origin, destination) {}
		vec4(const vec3& p, float d = 1) : Vector4<float>(p, d) {}
		vec4(const vec4& vec) : Vector4<float>(vec) {}
		vec4(const Vector4<float>& vec) : Vector4<float>(vec) {}
	};

	class PUNK_ENGINE_PUBLIC ivec4 : public Vector4<int> 
	{
	public:
		ivec4() : Vector4<int>() {}
		ivec4(int x, int y, int z, int w) : Vector4<int>(x, y, z, w) {}
		ivec4(int x) : Vector4<int>(x) {}
		ivec4(const ivec4& vec) : Vector4<int>(vec) {}
		ivec4(const Vector4<int>& vec) : Vector4<int>(vec) {}
	};	
}

#endif
