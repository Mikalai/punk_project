#ifndef _H_PUNK_MATH_ROOT_FIND
#define _H_PUNK_MATH_ROOT_FIND

#include "helper.h"

namespace Math
{
	//	c[3]*x^3 + c[2]*x^2 + c[1]*x + c[0] = 0
	enum RootFindResult
	{
		RESULT_NO_SOLUTION,
		RESULT_ONE_SOLUTION,
		RESULT_TWO_SOLUTIONS,
		RESULT_THREE_SOLUTIONS,
		RESULT_FOUR_SOLUTIONS
	};

	template<class T>
	RootFindResult SolveQuadric(const T c[3], T out[2])
	{
		T A = c[1] / c[2];
		T B = c[0] / c[2];

		T D = A*A - 4*B;

		if (D > 0)
		{
			out[0] = (-A + sqrt(D)) / T(2.0);
			out[1] = (-A - sqrt(D)) / T(2.0);
			return RootFindResult::RESULT_TWO_SOLUTIONS;
		}
		else if (Abs(D) < T(1e-6))
		{
			out[0] = -A / T(2.0);
			return RootFindResult::RESULT_ONE_SOLUTION;
		}
		else
		{
			return RootFindResult::RESULT_NO_SOLUTION;
		}
	}

	template<class T>
	RootFindResult SolveCubic(const T c[4], T out[3])
	{
		T A = c[2] / c[3];
		T B = c[1] / c[3];
		T C = c[0] / c[3];

		T p = B / T(3.0) - A*A / T(9.0);
		T q = A*A*A/T(27) - A*B/T(6) + C/T(2.0);

		T D = -(q*q + p*p*p);

		if (Abs(D) < 1e-6)
		{
			T r = pow(-q, T(1.0)/T(3.0));
			out[0] = T(2) * r;
			out[1] = out[2] = -r;

			out[0] -= A/T(3.0);
			out[1] -= A/T(3.0);
			out[2] -= A/T(3.0);
			return RootFindResult::RESULT_TWO_SOLUTIONS;
		}

		if (D < 0.0)
		{
			T r = pow(-q + sqrt(-D), T(1.0)/T(3.0));
			T s = pow(-q - sqrt(-D), T(1.0)/T(3.0));
			out[0] = r + s;

			out[0] -= A/T(3.0);
			return RootFindResult::RESULT_ONE_SOLUTION;
			//	y2 = -(u+v)/2 + sqrt(3)/2*(u-v)i
			//	y3 = -(u+v)/2 - sqrt(3)/2*(u-v)i
		}

		if (D > 0.0)
		{
			T cos_phy = - q / sqrt(-(p*p*p));
			if (cos_phy < -1)
				cos_phy = -1;
			else if (cos_phy > 1)
				cos_phy = 1;
			T phy = acos(cos_phy);
			out[0] = 2 * sqrt(-p)*cos(phy/T(3));
			out[1] = -2*sqrt(-p)*cos((phy/T(3)+T(3.141519265358979323846)/T(3) ));
			out[2] = -2*sqrt(-p)*cos((phy/T(3)-T(3.141519265358979323846)/T(3) ));

			out[0] = out[0] - A/T(3.0);
			out[1] = out[1] - A/T(3.0);
			out[2] = out[2] - A/T(3.0);
			return RootFindResult::RESULT_THREE_SOLUTIONS;
		}

		return RootFindResult::RESULT_NO_SOLUTION;
	}

	template<class T>
	RootFindResult SolveQuartic(const T c[5], T out[4])
	{
		T A = c[3] / c[4];
		T B = c[2] / c[4];
		T C = c[1] / c[4];
		T D = c[0] / c[4];

		T p = B - T(3.0/8.0)*A*A;
		T q = A*A*A / T(8.0) - A*B/T(2.0) + C;
		T r = T(-3.0/256.0)*A*A*A*A + A*A*B/T(16.0) - A*C/T(4.0) + D;

		T c0[] = {r*p/T(2.0) - q*q/T(8.0), -r, -p/T(2.0), T(1.0)};
		T out0[4];
		RootFindResult res = SolveCubic(c0, out0);

		if (res == RootFindResult::RESULT_NO_SOLUTION)
			return RootFindResult::RESULT_NO_SOLUTION;

		T z = out0[0];

		T out1[4];
		T out2[4];
		RootFindResult res1, res2;
		if (q >= 0)
		{
			T c1[] = {z - sqrt(z*z-r), sqrt(T(2.0)*z-p), 1};
			T c2[] = {z + sqrt(z*z-r),-sqrt(T(2.0)*z-p), 1};
			res1 = SolveQuadric(c1, out1);
			res2 = SolveQuadric(c2, out2);
		}
		else
		{
			T c1[] = {z + sqrt(z*z-r), sqrt(T(2.0)*z-p), 1};
			T c2[] = {z - sqrt(z*z-r),-sqrt(T(2.0)*z-p), 1};
			res1 = SolveQuadric(c1, out1);
			res2 = SolveQuadric(c2, out2);
		}

		if (res1 == RootFindResult::RESULT_NO_SOLUTION && res2 == RootFindResult::RESULT_NO_SOLUTION)
			return RootFindResult::RESULT_NO_SOLUTION;

		if (res1 == RootFindResult::RESULT_ONE_SOLUTION && res2 == RootFindResult::RESULT_NO_SOLUTION)
		{
			out[0] = out1[0] - A / T(4.0);
			return RootFindResult::RESULT_ONE_SOLUTION;
		}
		if (res1 == RootFindResult::RESULT_NO_SOLUTION && res2 == RootFindResult::RESULT_ONE_SOLUTION)
		{
			out[0] = out2[0] - A / T(4.0);
			return RootFindResult::RESULT_ONE_SOLUTION;
		}
		if (res1 == RootFindResult::RESULT_ONE_SOLUTION && res2 == RootFindResult::RESULT_ONE_SOLUTION)
		{
			out[0] = out1[0] - A / T(4.0);
			out[1] = out2[0] - A / T(4.0);
			return RootFindResult::RESULT_TWO_SOLUTIONS;
		}
		if (res1 == RootFindResult::RESULT_TWO_SOLUTIONS && res2 == RootFindResult::RESULT_NO_SOLUTION)
		{
			out[0] = out1[0] - A / T(4.0);
			out[1] = out1[1] - A / T(4.0);
			return RootFindResult::RESULT_TWO_SOLUTIONS;
		}
		if (res1 == RootFindResult::RESULT_NO_SOLUTION && res2 == RootFindResult::RESULT_TWO_SOLUTIONS)
		{
			out[0] = out2[0] - A / T(4.0);
			out[1] = out2[1] - A / T(4.0);
			return RootFindResult::RESULT_TWO_SOLUTIONS;
		}
		if (res1 == RootFindResult::RESULT_ONE_SOLUTION && res2 == RootFindResult::RESULT_TWO_SOLUTIONS)
		{
			out[0] = out1[0] - A / T(4.0);
			out[1] = out2[0] - A / T(4.0);
			out[2] = out2[1] - A / T(4.0);
			return RootFindResult::RESULT_THREE_SOLUTIONS;
		}
		if (res1 == RootFindResult::RESULT_TWO_SOLUTIONS && res2 == RootFindResult::RESULT_ONE_SOLUTION)
		{
			out[0] = out1[0] - A / T(4.0);
			out[1] = out1[1] - A / T(4.0);
			out[2] = out2[0] - A / T(4.0);
			return  RootFindResult::RESULT_THREE_SOLUTIONS;
		}
		if (res1 == RootFindResult::RESULT_TWO_SOLUTIONS && res2 == RootFindResult::RESULT_TWO_SOLUTIONS)
		{
			out[0] = out1[0] - A / T(4.0);
			out[1] = out1[1] - A / T(4.0);
			out[2] = out2[0] - A / T(4.0);
			out[3] = out2[1] - A / T(4.0);
			return  RootFindResult::RESULT_FOUR_SOLUTIONS;
		}
		return RootFindResult::RESULT_NO_SOLUTION;
	}
}

#endif
