#ifndef _H_CATMULL_ROM_SPLINE
#define _H_CATMULL_ROM_SPLINE

namespace Math
{
	template<class T>
	class CatmullRomSpline
	{
	public:
	public:
		static const T Interpolate(const T* pp1, const T* pp2, const T* pp3, const T* pp4, double u)
		{
			if (pp2 == 0 || pp3 == 0)
				return T();

			if (pp1 == 0 || pp2 == 0)
			{
				const T& p2 = *pp2;
				const T& p3 = *pp3;

				T result = p2*(1.0f-u) + u*p3;
				return result;
			}
			else
			{
				double u2 = u*u;
				double u3 = u2*u;

				const T& p1 = *pp1;
				const T& p2 = *pp2;
				const T& p3 = *pp3;
				const T& p4 = *pp4;

				T result = p1*(-0.5*u3+u2-0.5*u) + p2*(1.5*u3-2.5*u2+1) + p3*(-1.5*u3+2*u2+0.5*u) + p4*(0.5*u3-0.5*u2);
				return result;
			}
		}

		//	point = [0..4];
		static const T FastInterpolate(const T* pp1, const T* pp2, const T* pp3, const T* pp4, int point)
		{
			if (pp2 == 0 || pp3 == 0)
				return T();

			if (pp1 == 0 || pp4 == 0)
			{
				switch (point)
				{
				case 0:
					return *pp2;
				case 1:
					return 0.75**pp2 + 0.25**pp3;
				case 2:
					return 0.5**pp2 + 0.5**pp3;
				case 3:
					return 0.25*pp2 + 0.75**p3;
				case 4:
					return **pp3;
				default:
					return T();
				}
			}
			else
			{
				const T& p1 = *pp1;
				const T& p2 = *pp2;
				const T& p3 = *pp3;
				const T& p4 = *pp4;

				switch(point)
				{
				case 0:
					return *pp2;
				case 1:	
					{
						const T res = p1 * -0.0703125f + p2 * 0.8671875 + p3 * 0.2265625f + p4 * -0.0234375f;
						return res;
					}
				case 2:
					{
						const T res = p1 * -0.0625f + p2 * 0.5625f + p3 * 0.5625f + p4 * -0.0625f;
						return res;
					}
				case 3:
					{
						const T res = p1 * -0.234375f + p2 * 0.226563f + p3 * 0.8671875f + p4 * -0.0703125f;
						return res;
					}
				case 4:
					return *pp3;
				default:
					return T();
				}
			}
		}

	private:
		std::vector<T> m_data;
		double m_u;
		double m_du;
	};
}

#endif	//	_H_CATMULL_ROM_SPLINE