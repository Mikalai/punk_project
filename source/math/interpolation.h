#ifndef _H_PUNK_INTERPOLATION
#define _H_PUNK_INTERPOLATION

#include <cmath>
#include "constants.h"

namespace Math
{
	template<typename T, typename K>
	T linear_interpolation(const T& a, const T& b, const K& k)
	{
		T res = b*k + (1-k)*a;
		return res;
	}

	template<typename T, typename K>
	T cosine_interpolation(const T& a, const T& b, const K& value)
	{
		K t = value * PI;
		K tt = (K(1) - cos(t)) * 0.5f;
		return a*(K(1)-tt) + b*tt;
	}

	template<typename T>
	T cubic_interpolation(const T& v0, const T& v1, const T& v2, const T& v3, const T& value)
	{
		T a = (v3-v2) - (v0 - v1);
		T b = (v0 - v1) - a;
		T c = v2 - v0;
		T d = v1;
		T x = value;

		return a*x*x*x + b*x*x + c*x + d;	//	maybe it should be optimized a little
	}

	//
	//	used for linear interpolation of quaternions
	//
	template<class T, class U>
	T spherical_linear_interpolation(const T& q1, const T& q2, const U& t)
	{
		float cos_value = q1.Dot(q2);
		if (cos_value > 1.0)
			cos_value = 1.0;

		U theta = std::acos(cos_value);
		if (theta != 0)
		{
			T _q1 = std::sin(theta*(1-t))/std::sin(theta)*q1;
			T _q2 = std::sin(theta*t)/std::sin(theta)*q2;
			return _q1 + _q2;
		}
		else
			return linear_interpolation(q1, q2, t);
	}
}

#endif
