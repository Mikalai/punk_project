/*
*	Newton-Raphson Method is used to find roots of the function
*/

#ifndef _H_PUNK_MATH_NRM
#define _H_PUNK_MATH_NRM

#include <exception>
#define _USE_MATH_DEFINES
#include <math.h>

namespace Math
{
	template<typename Real>
	class NewtonRaphsonSolver
	{
	public:
		NewtonRaphsonSolver(Real eps = 1e-4);
		Real Solve(Real (*f)(Real), Real (*df)(Real), Real x0);
		void SetAccuracy(Real accuracy) { m_eps = accuracy; }
		Real GetAccuracy() const { return m_eps; }
		int GetIterationsCount() const { return m_iter_count; }
	private:
		Real Next(Real (*f)(Real), Real (*df)(Real), Real prev);
		Real FindRootIter(Real (*f)(Real), Real (*df)(Real), Real x0);
		Real FindRootEps(Real (*f)(Real), Real (*df)(Real), Real x0);

	private:
		///	iterations count used
		int m_iter_count;
		///	accuracy
		Real m_eps;
	};

	template<typename Real>
	NewtonRaphsonSolver<Real>::NewtonRaphsonSolver(Real eps) 
		: m_eps(eps)
		, m_iter_count(0)
	{}

	template<typename Real> 
	inline Real NewtonRaphsonSolver<Real>::Solve(Real (*f)(Real), Real (*df)(Real), Real x0)
	{
		return FindRootEps(f, df, x0);
	}

	template<class Real>
	inline Real NewtonRaphsonSolver<Real>::Next(Real (*f)(Real), Real (*df)(Real), Real prev)
	{
		Real next = prev - f(prev) / df(prev);
		return next;
	}	

	template<class Real> 
	inline Real NewtonRaphsonSolver<Real>::FindRootEps(Real (*f)(Real), Real (*df)(Real), Real x0)
	{
		Real x_prev = x0;
		Real x_next = Next(f, df, x0);
		m_iter_count = 1;
		while (fabs(x_prev - x_next) > m_eps)
		{
			x_prev = x_next;
			x_next = Next(f, df, x_prev);
			m_iter_count++;
		}
		return x_next;
	}
}

#endif	//	_H_NRM