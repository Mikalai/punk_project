/*
File: BoundingBox.cpp
Author: Abramau Mikalai and a guy who wrote that amazing clip functions
Description: Bounding box emplementation
*/

#include "bounding_box.h"
#include "line3d.h"

#include <algorithm>
#include <limits>

namespace Math
{
	bool ClipSegment(float min, float max, float a, float b, float d, float* t0, float* t1)
	{
		if (fabs(d) < std::numeric_limits<float>().epsilon())
		{
			if (d > 0.0f)
			{
				return !(b < min || a > max);
			}
			else
			{
				return !(a < min || b > max);
			}
		}

		float u0, u1;

		u0 = (min - a) / (d);
		u1 = (max - a) / (d);

		if (u0 > u1)
		{
			float temp = u0;
			u0 = u1;
			u1 = temp;
		}

		if (u1 < *t0 || u0 > *t1)
		{
			return false;
		}

		*t0 = max(u0, *t0);
		*t1 = max(u1, *t1);

		if (*t1 < *t0)
		{
			return false;
		}

		return true;
	}

	bool ClipSegment3D(const vec3& A, const vec3& B, const vec3& Min, const vec3& Max)
	{
		float t0 = 0.0f, t1 = 1.0f;
//		float S[3] = {A[0], A[1], A[2]};
		float D[3] = {B[0]-A[0], B[1]-A[1], B[2]-A[2]};

		if (!ClipSegment(Min[0], Max[0], A[0], B[0], D[0], &t0, &t1))
		{
			return false;
		}

		if (!ClipSegment(Min[1], Max[1], A[1], B[1], D[1], &t0, &t1))
		{
			return false;
		}

		if (!ClipSegment(Min[2], Max[2], A[2], B[2], D[2], &t0, &t1))
		{
			return false;
		}

		return true;
	}

	bool ClipSegment2D(const vec2& A, const vec2& B, const vec2& Min, const vec2& Max)
	{
		float t0 = 0.0f, t1 = 1.0f;
//		float S[2] = {A[0], A[1]};
		float D[2] = {B[0]-A[0], B[1]-A[1]};

		if (!ClipSegment(Min[0], Max[0], A[0], B[0], D[0], &t0, &t1))
		{
			return false;
		}

		if (!ClipSegment(Min[1], Max[1], A[1], B[1], D[1], &t0, &t1))
		{
			return false;
		}

		return true;
	}

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

	vec3& BoundingBox::Min() 
	{
		return m_min;
	}

	vec3& BoundingBox::Max()
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

	bool BoundingBox::DoCrossLine(const Line3D& line) const
	{
		if (!ClipSegment3D(line.Origin(), line.Destination(), m_min, m_max))
			return false;
		else
			return true;
	}

	bool BoundingBox::DoCrossTriangle(const vec3& pp1, const vec3& pp2, const vec3& pp3) const
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

		if (ClipSegment3D(pp1, pp2, m_min, m_max))
			return true;
		if (ClipSegment3D(pp2, pp3, m_min, m_max))
			return true;
		if (ClipSegment3D(pp3, pp1, m_min, m_max))
			return true;

		return false;
	}
}
