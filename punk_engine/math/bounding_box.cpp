/*
File: BoundingBox.cpp
Author: Abramov Nickolai
Description: Bounding box emplementation
*/

#include "bounding_box.h"
#include "low_level_math.h"

namespace Math
{
	void BoundingBox::Create(const float* data, unsigned offset, int count)
	{
		unsigned off = offset/sizeof(float);
		m_min[0] = m_max[0] = data[0];
		m_min[1] = m_max[1] = data[1];
		m_min[2] = m_max[2] = data[2];
		for (int i = 0; i < count; i ++)
		{
			if (m_min[0] > *(data + i*off + 0))
				m_min[0] = *(data + i*off + 0);
			if (m_min[1] > *(data + i*off + 1))
				m_min[1] = *(data + i*off + 1);
			if (m_min[2] > *(data + i*off + 2))
				m_min[2] = *(data + i*off + 2);
			if (m_max[0] < *(data + i*off + 0))
				m_max[0] = *(data + i*off + 0);
			if (m_max[1] < *(data + i*off + 1))
				m_max[1] = *(data + i*off + 1);
			if (m_max[2] < *(data + i*off + 2))
				m_max[2] = *(data + i*off + 2);
		}
	}

	BoundingBox Merge(const BoundingBox* b1, const BoundingBox* b2)
	{
		BoundingBox res;
		res.m_min[0] = b1->m_min[0] < b2->m_min[0] ? b1->m_min[0] : b2->m_min[0];
		res.m_min[1] = b1->m_min[1] < b2->m_min[1] ? b1->m_min[1] : b2->m_min[1];
		res.m_min[2] = b1->m_min[2] < b2->m_min[2] ? b1->m_min[2] : b2->m_min[2];

		res.m_max[0] = b1->m_max[0] > b2->m_max[0] ? b1->m_max[0] : b2->m_max[0];
		res.m_max[1] = b1->m_max[1] > b2->m_max[1] ? b1->m_max[1] : b2->m_max[1];
		res.m_max[2] = b1->m_max[2] > b2->m_max[2] ? b1->m_max[2] : b2->m_max[2];

		return res;
	}

	bool BoundingBox::IsPointIn(const float* p) const
	{
		if (p[0] >= m_min[0] && p[0] <= m_max[0] &&
			p[1] >= m_min[1] && p[1] <= m_max[1] &&
			p[2] >= m_min[2] && p[2] <= m_max[2])
			return true;
		return false;
	}

	const vec3& BoundingBox::Min() const
	{
		return m_min;
	}

	const vec3& BoundingBox::Max() const
	{
		return m_max;
	}

	const vec3* BoundingBox::TransformedPoints() const
	{
		return m_transformed_points;
	}

	const BoundingBox& BoundingBox::Transform(const Math::mat4& transform) const
	{
		m_transformed_points[0] = (transform * vec3(m_min[0], m_min[1], m_min[2]).ToHomogeneous()).XYZ();
		m_transformed_points[1] = (transform * vec3(m_min[0], m_min[1], m_max[2]).ToHomogeneous()).XYZ();
		m_transformed_points[2] = (transform * vec3(m_min[0], m_max[1], m_min[2]).ToHomogeneous()).XYZ();
		m_transformed_points[3] = (transform * vec3(m_min[0], m_max[1], m_max[2]).ToHomogeneous()).XYZ();
		m_transformed_points[4] = (transform * vec3(m_max[0], m_min[1], m_min[2]).ToHomogeneous()).XYZ();
		m_transformed_points[5] = (transform * vec3(m_max[0], m_min[1], m_min[2]).ToHomogeneous()).XYZ();
		m_transformed_points[6] = (transform * vec3(m_max[0], m_max[1], m_max[2]).ToHomogeneous()).XYZ();
		m_transformed_points[7] = (transform * vec3(m_max[0], m_max[1], m_max[2]).ToHomogeneous()).XYZ();

		return *this;
	}

	vec3& BoundingBox::operator [] (int index)
	{
		return m_border_points[index];
	}

	const vec3& BoundingBox::operator [] (int index) const
	{
		return m_border_points[index];
	}

	bool BoundingBox::DoCrossTriangle(const float* pp1, const float* pp2, const float* pp3) const
	{
		if (pp1[0] > m_max[0] && pp2[0] > m_max[0] && pp3[0] > m_max[0])
			return false;
		if (pp1[0] < m_min[0] && pp2[0] < m_min[0] && pp3[0] < m_min[0])
			return false;
		if (pp1[1] > m_max[1] && pp2[1] > m_max[1] && pp3[1] > m_max[1])
			return false;
		if (pp1[1] < m_min[1] && pp2[1] < m_min[1] && pp3[1] < m_min[1])
			return false;
		if (pp1[2] > m_max[2] && pp2[2] > m_max[2] && pp3[2] > m_max[2])
			return false;
		if (pp1[2] < m_min[2] && pp2[2] < m_min[2] && pp3[2] < m_min[2])
			return false;
		//
		//  the simpliest test
		//
		if (IsPointIn(pp1) ||
			IsPointIn(pp2) ||
			IsPointIn(pp3))
			return true;

		if (Math::glClipSegment3D(pp1, pp2, m_min, m_max))
			return true;
		if (Math::glClipSegment3D(pp2, pp3, m_min, m_max))
			return true;
		if (Math::glClipSegment3D(pp3, pp1, m_min, m_max))
			return true;

		return false;
	}
}
