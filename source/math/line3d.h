#ifndef LINE_H
#define LINE_H

#include "../config.h"
#include "vec3.h"
#include "math_relations.h"

namespace Math
{
	class PUNK_ENGINE Plane;
	class Triangle3D;

	class PUNK_ENGINE Line3D
	{
		vec3 m_origin;
		vec3 m_destination;
		vec3 m_direction;
	public:       
		enum Location {LOCATION_ON, LOCATION_OUT, LOCATION_CROSS, LOCATION_PARALLEL, LOCATION_BELONG};

		Line3D();
		Line3D(const vec3& org, const vec3& dir);
		Location Classify(const vec3& Point) const;
		const vec3 PointAt(float t) const;
		Location Classify(const Plane& p) const;
		const vec3& Direction() const;
		const vec3& Origin() const;
		void SetOrigin(const vec3& origin);
		const vec3& Destination() const;
		void SetDestination(const vec3& destination);
		float SegmentLength() const;
		IntersectionType CrossTriangle(const Triangle3D& p, float& t) const;
		IntersectionType CrossPlane(const Plane& p, vec3& t);
	};
}
#endif // LINE_H
