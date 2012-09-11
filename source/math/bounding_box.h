/*
File: BoundingBox.h
Author: Abramau Mikalai
Description: A bounding box
*/

#ifndef _H_BOUNDING_BOX
#define _H_BOUNDING_BOX

#include <iosfwd>
#include "../config.h"
#include "mat4.h"
#include "vec3.h"

namespace Math
{
	class Line3D;

	class PUNK_ENGINE BoundingBox
	{
		mutable vec3 m_transformed_points[8];

		vec3 m_border_points[8];
		vec3 m_min;
		vec3 m_max;

	public:
		
		void Create(const float* data, unsigned offset, int count);
		bool DoCrossTriangle(const vec3& p1, const vec3& p2, const vec3& p3) const;
		bool IsPointIn(const float *p) const;
		bool DoCrossLine(const Line3D& line) const;

		const vec3& Min() const;
		const vec3& Max() const;
		vec3& Min();
		vec3& Max();		
		const vec3* TransformedPoints() const;

		vec3& operator [] (int index);
		const vec3& operator [] (int index) const;

		const BoundingBox& Transform(const Math::mat4& transform, Math::vec3& min, Math::vec3& max) const;
		const BoundingBox& Transform(const mat4& transform) const;

		void Save(std::ostream& stream);
		void Load(std::istream& stream);

		friend PUNK_ENGINE BoundingBox Merge(const BoundingBox* b1, const BoundingBox* b2);
	};

	PUNK_ENGINE BoundingBox Merge(const BoundingBox* b1, const BoundingBox* b2);

}

#endif
