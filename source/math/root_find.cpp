#include "root_find.h"
//	c[3]*x^3 + c[2]*x^2 + c[1]*x + c[0] = 0

enum Result
{
	RESULT_NO_SOLUTION,
	RESULT_ONE_SOLUTION,
	RESULT_TWO_SOLUTIONS,
	RESULT_THREE_SOLUTIONS,
	RESULT_FOUR_SOLUTIONS
};

Result SolveQuadric(double c[3], double out[2])
{
	double A = c[1] / c[2];
	double B = c[0] / c[2];

	double D = A*A - 4*B;

	if (D > 0)
	{
		out[0] = (-A + sqrt(D)) / 2.0;
		out[1] = (-A - sqrt(D)) / 2.0;
		return RESULT_TWO_SOLUTIONS;
	}
	else if (D >= 0 && D <= 1e-6)
	{
		out[0] = -A / 2.0;
		return RESULT_ONE_SOLUTION;
	}
	else
	{
		return RESULT_NO_SOLUTION;
	}
}

Result SolveCubic(double c[4], double out[3])
{
	double A = c[2] / c[3];
	double B = c[1] / c[3];
	double C = c[0] / c[3];

	double p = B / 3.0 - A*A / 9.0;
	double q = A*A*A/27.0 - A*B/6.0 + C/2.0;

	double D = q*q + p*p*p;
	
	if (fabs(D) < 1e-10)
	{
		double cos_phy = - q / sqrt(-(p*p*p));
		double phy = acos(cos_phy);
		out[0] = 2 * sqrt(-p)*cos(phy/3);
		out[1] = -2.0*sqrt(-p)*cos((phy+3.141519265358979323846)/3.0);

		out[0] = out[0] - A/3.0;
		out[1] = out[1] - A/3.0;
		out[2] = out[1];
		return RESULT_TWO_SOLUTIONS;		
	}

	if (D > 0.0)
	{
		double qq, s;
		qq = -q+sqrt(D);
		s = (qq >= 0) ? 1 : -1;
		double u = s*pow(fabs(qq), 1.0/3.0);
		qq = -q-sqrt(D);
		s = (qq >= 0) ? 1 : -1;
		double v = s*pow(fabs(qq), 1.0/3.0);
		out[0] = u + v;
		out[0] = out[0] - A/3.0;
		return RESULT_ONE_SOLUTION;
		//	y2 = -(u+v)/2 + sqrt(3)/2*(u-v)i
		//	y3 = -(u+v)/2 - sqrt(3)/2*(u-v)i
	}



	if (D < 0.0)
	{
		double cos_phy = - q / sqrt(-(p*p*p));
		double phy = acos(cos_phy);
		out[0] = 2 * sqrt(-p)*cos(phy/3);
		out[1] = -2*sqrt(-p)*cos((phy+3.141519265358979323846)/3.0);
		out[2] = -2*sqrt(-p)*cos((phy-3.141519265358979323846)/3.0);

		out[0] = out[0] - A/3.0;
		out[1] = out[1] - A/3.0;
		out[2] = out[2] - A/3.0;
		return RESULT_THREE_SOLUTIONS;
	}
}

Result SolveQuartic(double c[5], double out[4])
{
	double A = c[3] / c[4];
	double B = c[2] / c[4];
	double C = c[1] / c[4];
	double D = c[0] / c[4];

	double p = B - 3.0/8.0*A*A;
	double q = A*A*A / 8.0 - A*B/2.0 + C;
	double r = -3.0/256.0*A*A*A*A + A*A*B/16.0 - A*C/4.0 + D;

	double c0[] = {r*p/2.0 - q*q/8.0, -r, -p/2.0, 1.0};
	double out0[4];
	Result res = SolveCubic(c0, out0);

	if (res == RESULT_NO_SOLUTION)
		return RESULT_NO_SOLUTION;

	double z = out0[0];

	double out1[4];
	double out2[4];
	Result res1, res2;
	if (q >= 0)
	{
		double c1[] = {z - sqrt(z*z-r), sqrt(2.0*z-p), 1};
		double c2[] = {z + sqrt(z*z-r),-sqrt(2.0*z-p), 1};	
		res1 = SolveQuadric(c1, out1);	
		res2 = SolveQuadric(c2, out2);	
	}
	else
	{
		double c1[] = {z + sqrt(z*z-r), sqrt(2.0*z-p), 1};
		double c2[] = {z - sqrt(z*z-r),-sqrt(2.0*z-p), 1};	
		res1 = SolveQuadric(c1, out1);	
		res2 = SolveQuadric(c2, out2);	
	}

	if (res1 == RESULT_NO_SOLUTION && res2 == RESULT_NO_SOLUTION)
		return RESULT_NO_SOLUTION;

	if (res1 == RESULT_ONE_SOLUTION && res2 == RESULT_NO_SOLUTION)
	{
		out[0] = out1[0] - A / 4.0;
		return RESULT_ONE_SOLUTION;
	}
	if (res1 == RESULT_NO_SOLUTION && res2 == RESULT_ONE_SOLUTION)
	{
		out[0] = out2[0] - A / 4.0;
		return RESULT_ONE_SOLUTION;
	}
	if (res1 == RESULT_ONE_SOLUTION && res2 == RESULT_ONE_SOLUTION)
	{
		out[0] = out1[0] - A / 4.0;
		out[1] = out2[0] - A / 4.0;
		return RESULT_TWO_SOLUTIONS;
	}
	if (res1 == RESULT_TWO_SOLUTIONS && res2 == RESULT_NO_SOLUTION)
	{
		out[0] = out1[0] - A / 4.0;
		out[1] = out1[1] - A / 4.0;
		return RESULT_TWO_SOLUTIONS;
	}
	if (res1 == RESULT_NO_SOLUTION && res2 == RESULT_TWO_SOLUTIONS)
	{
		out[0] = out2[0] - A / 4.0;
		out[1] = out2[1] - A / 4.0;
		return RESULT_TWO_SOLUTIONS;
	}
	if (res1 == RESULT_ONE_SOLUTION && res2 == RESULT_TWO_SOLUTIONS)
	{
		out[0] = out1[0] - A / 4.0;
		out[1] = out2[0] - A / 4.0;
		out[2] = out2[1] - A / 4.0;
		return RESULT_THREE_SOLUTIONS;
	}
	if (res1 == RESULT_TWO_SOLUTIONS && res2 == RESULT_ONE_SOLUTION)
	{
		out[0] = out1[0] - A / 4.0;
		out[1] = out1[1] - A / 4.0;
		out[2] = out2[0] - A / 4.0;
		return  RESULT_THREE_SOLUTIONS;
	}
	if (res1 == RESULT_TWO_SOLUTIONS && res2 == RESULT_TWO_SOLUTIONS)
	{
		out[0] = out1[0] - A / 4.0;
		out[1] = out1[1] - A / 4.0;
		out[2] = out2[0] - A / 4.0;
		out[3] = out2[1] - A / 4.0;
		return  RESULT_FOUR_SOLUTIONS;
	}
	std::cout << "Something wrong in "__FUNCSIG__ << std::endl;
	return RESULT_NO_SOLUTION;
}