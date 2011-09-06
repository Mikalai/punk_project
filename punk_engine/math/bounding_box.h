/*
File: BoundingBox.h
Author: Abramov Nickolai
Description: A bounding box
*/

#ifndef _H_BOUNDING_BOX
#define _H_BOUNDING_BOX

#include "config.h"
#include "mat4.h"
#include "vec3.h"

namespace Math
{
	class LIB_MATH BoundingBox
	{
		mutable vec3 m_transformed_points[8];

		vec3 m_border_points[8];
		vec3 m_min;
		vec3 m_max;

	public:

		void Create(const float* data, unsigned offset, int count);
		bool DoCrossTriangle(const float* p1, const float* p2, const float* p3) const;
		bool IsPointIn(const float *p) const;

		const vec3& Min() const;
		const vec3& Max() const;
		const vec3* TransformedPoints() const;

		vec3& operator [] (int index);
		const vec3& operator [] (int index) const;

		const BoundingBox& Transform(const mat4& transform) const;

		friend LIB_MATH BoundingBox Merge(const BoundingBox* b1, const BoundingBox* b2);
	};

	LIB_MATH BoundingBox Merge(const BoundingBox* b1, const BoundingBox* b2);

}

#endif
