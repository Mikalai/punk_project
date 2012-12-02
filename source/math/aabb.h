/*
File: AxisAlignedBox.h
Author: Abramaŭ Mikałaj
Description: A bounding box
*/

#ifndef _H_PUNK_MATH_AABB
#define _H_PUNK_MATH_AABB

#include <iosfwd>
#include "../config.h"
#include "mat4.h"
#include "vec3.h"

namespace Math
{
	class Line3D;

	class PUNK_ENGINE AxisAlignedBox
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

		const vec3& MinPoint() const;
		const vec3& MaxPoint() const;
		vec3& MinPoint();
		vec3& MaxPoint();		
		const vec3* TransformedPoints() const;

		vec3& operator [] (int index);
		const vec3& operator [] (int index) const;

		const AxisAlignedBox& TransformNode(const Math::mat4& transform, Math::vec3& Min, Math::vec3& Max) const;
		const AxisAlignedBox& TransformNode(const mat4& transform) const;

		bool Save(std::ostream& stream) const;
		bool Load(std::istream& stream);

		friend PUNK_ENGINE AxisAlignedBox Merge(const AxisAlignedBox* b1, const AxisAlignedBox* b2);

		std::wostream& out_formatted(std::wostream& stream);
	};

	PUNK_ENGINE AxisAlignedBox Merge(const AxisAlignedBox* b1, const AxisAlignedBox* b2);

}

#endif	//	_H_PUNK_MATH_AABB
