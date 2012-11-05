#ifndef LINE_H
#define LINE_H

#include "../config.h"
#include "vec3.h"
#include "relations.h"

namespace Math
{
	class PUNK_ENGINE Line3D
	{
		vec3 m_origin;
		vec3 m_destination;
		vec3 m_direction;
	public:       

		Line3D();
		Line3D(const vec3& org, const vec3& dir);
		const vec3 PointAt(float t) const;		
		const vec3& Direction() const;
		const vec3& Origin() const;
		void SetOrigin(const vec3& origin);
		const vec3& Destination() const;
		void SetDestination(const vec3& destination);
		float SegmentLength() const;
	};
}
#endif // LINE_H
