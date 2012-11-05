#include "triangle2d.h"
#include <limits>

namespace Math
{
	Triangle2D::Triangle2D()
		: a()
		, b()
		, c()
	{}

	Triangle2D::Triangle2D(const vec2& v0, const vec2& v1, const vec2& v2)
	{
		//
		//  c.X() must be between a and b
		//
		a = v0.X() < v1.X() ? (v0.X() < v2.X() ? v0 : v2) : (v1.X() < v2.X() ? v1 : v2);
		b = v0.X() > v1.X() ? (v0.X() > v2.X() ? v0 : v2) : (v1.X() > v2.X() ? v1 : v2);
		if (v0 == a && v1 == b || v0 == b && v1 == a)
			c = v2;
		else if (v0 == a && v2 == b || v0 == b && v2 == a)
			c = v1;
		else if (v1 == a && v2 == b || v1 == b && v2 == a)
			c = v0;
		else
		{
			a = b = c = (v0 + v1 + v2) / 3.0f;
			//   throw new EX()ception("Fuck!!! I made a stupid mistake in Triangle2D");
		}
	}

	bool Triangle2D::IsPointIn(const vec2& p) const
	{
		float s1 = (a.X() - p.X()) * (b.Y() - p.Y()) - (a.Y() - p.Y()) * (b.X() - p.X());
		float s2 = (b.X() - p.X()) * (c.Y() - p.Y()) - (b.Y() - p.Y()) * (c.X() - p.X());
		float s3 = (c.X() - p.X()) * (a.Y() - p.Y()) - (c.Y() - p.Y()) * (a.X() - p.X());

		s1 = (fabs(s1) <= 1e-4) ? 0 : s1;
		s2 = (fabs(s2) <= 1e-4) ? 0 : s2;
		s3 = (fabs(s3) <= 1e-4) ? 0 : s3;
		
		if (s1 >= 0 && s2 >= 0 && s3 >= 0)
			return true;
		if (s1 <= 0 && s2 <= 0 && s3 <= 0)
			return true;


		return false;
	}
}
