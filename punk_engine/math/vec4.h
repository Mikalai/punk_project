/*
MODULE FOR WORKING WITH 4 DIMENSIONAL VECTOR
AUTHOR: Mikalai Abramau
*/

#ifndef _H_VEC4_MATH
#define _H_VEC4_MATH

#include "../system/string.h"
#include <stdio.h>
#include <cmath>

namespace Math
{
	template<class T> class Vector3;
	template<class T> class Vector2;

	template<class T>
	class  Vector4
	{
		static const int Size_c = 4;
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
			m_v[0] = x;
			m_v[1] = y;
			m_v[2] = z;
			m_v[3] = w;
		}

		Vector4<T>(Vector4<T>& origin, Vector4<T>& destination)
		{
			for (int i = 0; i < Size_c; i++)
			{
				m_v[i] = destination[i] - origin[i];
			}
		}

		Vector4<T>(const Vector3<T>& vec, T d)
		{
			m_v[0] = vec.X();
			m_v[1] = vec.Y();
			m_v[2] = vec.Z();
			m_v[3] = d;
		}

		T& operator[] (int i)
		{
			return m_v[i];
		}

		T operator[] (int i) const
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
			memcpy_s(m_v, sizeof(m_v), vec.m_v, sizeof(m_v));
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

		T Dot(const Vector4<T>& vec)
		{
			return m_v[0] * vec.m_v[0] + m_v[1] * vec.m_v[1] + m_v[2] * vec.m_v[2] + m_v[3] * vec.m_v[3];
		}

		void Set(T x, T y, T z, T w)
		{
			m_v[0] = x;
			m_v[1] = y;
			m_v[2] = z;
			m_v[3] = w;
		}

		Vector4<T> ComponentMul(const Vector4<T>& v)
		{
			return Vector4<T>(m_v[0]*v[0], m_v[1]*v[1], m_v[2]*v[2], m_v[3]*v[3]);
		}

		System::string ToString() const
		{
			return System::string::Format(L"(%.3f; %.3f; %.3f; %.3f)", m_v[0], m_v[1], m_v[2], m_v[3]);
		}

	/*	void Save(System::Buffer& buffer) const
		{
			buffer.WriteReal32(m_v[0]);
			buffer.WriteReal32(m_v[1]);
			buffer.WriteReal32(m_v[2]);
			buffer.WriteReal32(m_v[3]);
		}

		void Load()
		{
			m_v[0] = buffer.ReadReal32();
			m_v[1] = buffer.ReadReal32();
			m_v[2] = buffer.ReadReal32();
			m_v[3] = buffer.ReadReal32();
		}
*/
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

		Vector2<T> XW() const
		{
			return Vector2<T>(m_v[0], m_v[3]);
		}

		Vector2<T> WX() const 
		{
			return Vector2<T>(m_v[3], m_v[0]);
		}

		Vector2<T> WZ() const
		{
			return Vector2<T>(m_v[3], m_v[2]);
		}

		Vector2<T> ZW() const
		{
			return Vector2<T>(m_v[2], m_v[3]);
		}

		Vector2<T> YW() const
		{
			return Vector2<T>(m_v[1], m_v[3]);
		}

		Vector2<T> WY() const
		{
			return Vector2<T>(m_v[3], m_v[1]);
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

		Vector4<T> XYZW() const
		{
			return Vector4<T>(m_v[0], m_v[1], m_v[2], m_v[3]);
		}

		Vector4<T> XYWZ() const
		{
			return Vector4<T>(m_v[0], m_v[1], m_v[3], m_v[2]);
		}

		Vector4<T> XZYW() const
		{
			return Vector4<T>(m_v[0], m_v[2], m_v[1], m_v[3]);
		}

		Vector4<T> XZWY() const
		{
			return Vector4<T>(m_v[0], m_v[2], m_v[3], m_v[1]);
		}

		Vector4<T> XWYZ() const
		{
			return Vector4<T>(m_v[0], m_v[3], m_v[1], m_v[2]);
		}

		Vector4<T> XWZY() const
		{
			return Vector4<T>(m_v[0], m_v[3], m_v[2], m_v[1]);
		}

		Vector4<T> YXZW() const
		{
			return Vector4<T>(m_v[1], m_v[0], m_v[2], m_v[3]);
		}

		Vector4<T> YXWZ() const
		{
			return Vector4<T>(m_v[1], m_v[0], m_v[3], m_v[2]);
		}

		Vector4<T> YZXW() const
		{
			return Vector4<T>(m_v[1], m_v[2], m_v[0], m_v[3]);
		}

		Vector4<T> YZWX() const
		{
			return Vector4<T>(m_v[1], m_v[2], m_v[3], m_v[0]);
		}

		Vector4<T> YWZX() const
		{
			return Vector4<T>(m_v[1], m_v[3], m_v[2], m_v[0]);
		}

		Vector4<T> YWXZ() const
		{
			return Vector4<T>(m_v[1], m_v[3], m_v[0], m_v[2]);
		}


		Vector4<T> ZXYW() const
		{
			return Vector4<T>(m_v[2], m_v[0], m_v[1], m_v[3]);
		}

		Vector4<T> ZXWY() const
		{
			return Vector4<T>(m_v[2], m_v[0], m_v[3], m_v[1]);
		}

		Vector4<T> ZYXW() const
		{
			return Vector4<T>(m_v[2], m_v[1], m_v[0], m_v[3]);
		}

		Vector4<T> ZYWX() const
		{
			return Vector4<T>(m_v[2], m_v[1], m_v[3], m_v[0]);
		}

		Vector4<T> ZWXY() const
		{
			return Vector4<T>(m_v[2], m_v[3], m_v[0], m_v[1]);
		}

		Vector4<T> ZWYX() const
		{
			return Vector4<T>(m_v[2], m_v[3], m_v[1], m_v[0]);
		}

		Vector4<T> WXYZ() const
		{
			return Vector4<T>(m_v[3], m_v[0], m_v[1], m_v[2]);
		}

		Vector4<T> WXZY() const
		{
			return Vector4<T>(m_v[3], m_v[0], m_v[2], m_v[1]);
		}

		Vector4<T> WYXZ() const
		{
			return Vector4<T>(m_v[3], m_v[1], m_v[0], m_v[2]);
		}

		Vector4<T> WYZX() const
		{
			return Vector4<T>(m_v[3], m_v[1], m_v[2], m_v[0]);
		}

		Vector4<T> WZXY() const
		{
			return Vector4<T>(m_v[3], m_v[2], m_v[0], m_v[1]);
		}

		Vector4<T> WZYX() const
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

			throw MathTestFailed();
			//	should be completed somewhen
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
		return new Vector4<T>(a[0] * d, a[1] * d, a[2] * d, a[3] * d);
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

//	template class LIB_MATH Vector4<float>;
//	template class LIB_MATH Vector4<int>;

	typedef Vector4<float> vec4;
	typedef Vector4<int> ivec4;
}

#endif
