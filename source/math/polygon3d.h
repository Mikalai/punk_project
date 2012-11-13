#ifndef _H_PUNK_MATH_POLYGON_3D
#define _H_PUNK_MATH_POLYGON_3D

#include <vector>
#include "../config.h"

#include "vec3.h"


namespace Math
{
	class Plane;

	class PUNK_ENGINE Polygon3D
	{
	public:
		typedef std::vector<vec3> Points;

	public:

		void Append(const vec3& p);		
		const Points& GetPoints() const { return m_points; }
		
		bool IsPlanar();
		bool IsTriangle();

		//	modifies current polygon
		Polygon3D& MakePlanar();

	private:		
		Points m_points;
		bool m_is_planar;		
	};
}

#endif