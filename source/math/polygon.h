#ifndef _H_PUNK_MATH_POLYGON
#define _H_PUNK_MATH_POLYGON

#include "../config.h"
#include "vec3.h"

namespace Math
{
	class Plane;
	class Triangle3D;

	class PUNK_ENGINE Polygon3D
	{
	public:
		Polygon3D();
		explicit Polygon3D(const Triangle3D& tr);
		void AddPoint(const vec3& point);
		const vec3 GeometryCenter();

		static const Polygon3D CreateConvex(const PointArray& points);

		bool IsPlanar() const;

		//	modify itself 
		Polygon3D& MakePlanar();

		void Split(const Plane& plane);

	private:
		PointArray m_points;
	};
}

#endif