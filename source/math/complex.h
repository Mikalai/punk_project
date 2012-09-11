#ifndef _H_PUNK_COMPLEX
#define _H_PUNK_COMPLEX

#include <stdio.h>
#include "../system/buffer.h"
#include "vec2.h"

namespace Math
{
	template<typename T>
	class Complex
	{
		static wchar_t m_buffer[128];

		T m_real;
		T m_image;
	public:

		Complex() : m_real(T()), m_image(T())
		{
		}

		Complex(T real, T image) : m_real(real), m_image(image) {}

		Complex(T angle) : m_real(cos(angle)), m_image(sin(angle)) {}

		T& Real()
		{
			return m_real;
		}
		
		const T& Real() const
		{
			return m_real;
		}

		T& ImageModule()
		{
			return m_image;
		}

		const T& ImageModule() const
		{
			return m_image;
		}

		const wchar_t ToString() const
		{
			swprintf(m_buffer, L"(%.3f; %.3f)", m_real, m_image);
			return m_buffer;
		}

		void Save(System::Buffer& buffer) const
		{
			buffer.WriteReal32(m_real);
			buffer.WriteReal32(m_image);
		}

		void Load(System::Buffer& buffer)
		{
			m_real = buffer.ReadReal32();
			m_image = buffer.ReadReal32();
		}

		T SquareLength() const
		{
			return m_real*m_real + m_image*m_image;
		}

		T Length() const
		{
			return sqrt(m_real*m_real + m_image*m_image);
		}

		Complex<T> Conjugated() const
		{
			return Complex<T>(m_real, -m_image);
		}

		Complex<T> Normalized() const
		{
			T inv_length = T(1) / Length();
			return Complex<T>(m_real * inv_length, m_image * inv_length);
		}

		T Argument() const
		{
			T inv_length = T(1) / Length();
			T a = m_real * inv_length;
			T b = m_image * inv_length;

			if (a == 0 && b >= 0)
				return M_PI/2.0;
			else if (a == 0 && b < 0)
				return 3.0*M_PI/2.0;
			else if (a > 0 && b > 0)
				return atan(b/a);
			else
				return M_PI + atan(b/a);
		}

		friend Complex<T> operator + (const Complex<T>& c1, const Complex<T>& c2);
	};

	template<typename T>
	wchar_t Complex<T>::m_buffer[128];

	template<typename T>
	Complex<T> operator + (const Complex<T>& c1, const Complex<T>& c2)
	{
		return Complex<T>(c1.m_real + c2.m_real, c1.m_image + c2.m_image);
	}

	template<typename T>
	Complex<T> operator - (const Complex<T>& c1, const Complex<T>& c2)
	{
		return Complex<T>(c1.m_real - c2.m_real, c1.m_image - c2.m_image);
	}

	template<typename T>
	Complex<T> operator * (const Complex<T>& c1, const Complex<T>& c2)
	{
		return Complex<T>(c1.m_real*c2.m_real - c1.m_image*c2.m_image, c1.m_real*c2.m_image + c2.m_real*c1.m_image);
	}

	template<typename T>
	Vector2<T> operator * (const Complex<T>& c, const Vector2<T>& v)
	{
		return Vector2<T>(c.Real()*v.X() - c.ImageModule()*v.Y(), c.Real()*v.Y() + v.X()*c.ImageModule());
	}

	typedef Complex<float> complex;
}

#endif	//_H_PUNK_COMPLEX