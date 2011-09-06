#pragma once

#include "../math/Vector3.h"
#include "../math/Vector4.h"

struct __declspec(dllexport) Color
{
	float r, g, b, a;
	Color() : r(1.0f), g(1.0f), b(1.0f), a(1.0f) {}
	Color(float r, float g, float b, float a = 1) : r(r), g(g), b(b), a(a) {}
	Color(const Color& c) {r = c.r; g = c.g; b = c.b; a = c.a;}
	Color& operator = (const Color& c) 
	{ 
		if (&c != this)
		{
			r = c.r; g = c.g; b = c.b; a = c.a; 
		}
		return *this;
	}
	bool operator != (const Color& c)
	{
		return !(*this == c);
	}

	bool operator == (const Color& c2)
	{
		return r == c2.r && g == c2.g && b == c2.b && a == c2.a;
	}
	Color& operator += (const Color& c)
	{
		r += c.r; g += c.g; b += c.b; a += c.a;
		return *this;
	}
	Color& operator -= (const Color& c)
	{
		r -= c.r; g -= c.g; b -= c.b; a -= c.a;
		return *this;
	}
};

inline Color operator + (Color& c1, Color& c2)
{
	return Color(c1.r+c2.r, c1.g+c2.g, c1.b+c2.b, c1.a + c2.a);
}

inline Color operator - (Color& c1, Color& c2)
{
	return Color(c1.r-c2.r, c1.g-c2.g, c1.b-c2.b, c1.a - c2.a);
}

inline Color operator * (Color& c1, float f)
{
	return Color(c1.r*f, c1.g*f, c1.b*f, c1.a*f);
}

inline Color operator / (Color& c1, float f)
{
	return Color(c1.r/f, c1.g/f, c1.b/f, c1.a/f);
}

