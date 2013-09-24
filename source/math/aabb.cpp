/*
File: AxisAlignedBox.cpp
Author: Abramaŭ Mikałaj and a guy who wrote that amazing clip functions
Description: Bounding box emplementation
*/

#include "../system/logger.h"
#include "aabb.h"
#include "line3d.h"
#include "helper.h"
#include <algorithm>
#include <limits>

namespace Math
{

	void AxisAlignedBox::Create(const float* data, unsigned offset, int count)
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

	AxisAlignedBox Merge(const AxisAlignedBox* b1, const AxisAlignedBox* b2)
	{
		AxisAlignedBox res;
        res.MinPoint()[0] = b1->MinPoint()[0] < b2->MinPoint()[0] ? b1->MinPoint()[0] : b2->MinPoint()[0];
        res.MinPoint()[1] = b1->MinPoint()[1] < b2->MinPoint()[1] ? b1->MinPoint()[1] : b2->MinPoint()[1];
        res.MinPoint()[2] = b1->MinPoint()[2] < b2->MinPoint()[2] ? b1->MinPoint()[2] : b2->MinPoint()[2];

        res.MaxPoint()[0] = b1->MaxPoint()[0] > b2->MaxPoint()[0] ? b1->MaxPoint()[0] : b2->MaxPoint()[0];
        res.MaxPoint()[1] = b1->MaxPoint()[1] > b2->MaxPoint()[1] ? b1->MaxPoint()[1] : b2->MaxPoint()[1];
        res.MaxPoint()[2] = b1->MaxPoint()[2] > b2->MaxPoint()[2] ? b1->MaxPoint()[2] : b2->MaxPoint()[2];

		return res;
	}

    const vec3& AxisAlignedBox::MinPoint() const
	{
		return m_min;
	}

	const vec3& AxisAlignedBox::MaxPoint() const
	{
		return m_max;
	}

	vec3& AxisAlignedBox::MinPoint() 
	{
		return m_min;
	}

	vec3& AxisAlignedBox::MaxPoint()
	{
		return m_max;
	}

//	const vec3* AxisAlignedBox::TransformedPoints() const
//	{
//		return m_transformed_points;
//	}

//	const AxisAlignedBox& AxisAlignedBox::TransformNode(const Math::mat4& transform, Math::vec3& min, Math::vec3& max) const
//	{
//		m_transformed_points[0] = (transform * vec4(m_min[0], m_min[1], m_min[2], 1)).XYZ();
//		min = max = m_transformed_points[0];

//		m_transformed_points[1] = (transform * vec4(m_min[0], m_min[1], m_max[2], 1)).XYZ();

//		min[0] = Min(min[0], m_transformed_points[1][0]); min[1] = Min(min[1], m_transformed_points[1][1]); min[2] = Min(min[2], m_transformed_points[1][2]);
//		max[0] = Max(max[0], m_transformed_points[1][0]); max[1] = Max(max[1], m_transformed_points[1][1]); max[2] = Max(max[2], m_transformed_points[1][2]);

//		m_transformed_points[2] = (transform * vec4(m_min[0], m_max[1], m_min[2], 1)).XYZ();
//		min[0] = Min(min[0], m_transformed_points[2][0]); min[1] = Min(min[1], m_transformed_points[2][1]); min[2] = Min(min[2], m_transformed_points[2][2]);
//		max[0] = Max(max[0], m_transformed_points[2][0]); max[1] = Max(max[1], m_transformed_points[2][1]); max[2] = Max(max[2], m_transformed_points[2][2]);
//		m_transformed_points[3] = (transform * vec4(m_min[0], m_max[1], m_max[2], 1)).XYZ();
//		min[0] = Min(min[0], m_transformed_points[3][0]); min[1] = Min(min[1], m_transformed_points[3][1]); min[2] = Min(min[2], m_transformed_points[3][2]);
//		max[0] = Max(max[0], m_transformed_points[3][0]); max[1] = Max(max[1], m_transformed_points[3][1]); max[2] = Max(max[2], m_transformed_points[3][2]);
//		m_transformed_points[4] = (transform * vec4(m_max[0], m_min[1], m_min[2], 1)).XYZ();
//		min[0] = Min(min[0], m_transformed_points[4][0]); min[1] = Min(min[1], m_transformed_points[4][1]); min[2] = Min(min[2], m_transformed_points[4][2]);
//		max[0] = Max(max[0], m_transformed_points[4][0]); max[1] = Max(max[1], m_transformed_points[4][1]); max[2] = Max(max[2], m_transformed_points[4][2]);
//		m_transformed_points[5] = (transform * vec4(m_max[0], m_min[1], m_max[2], 1)).XYZ();
//		min[0] = Min(min[0], m_transformed_points[5][0]); min[1] = Min(min[1], m_transformed_points[5][1]); min[2] = Min(min[2], m_transformed_points[5][2]);
//		max[0] = Max(max[0], m_transformed_points[5][0]); max[1] = Max(max[1], m_transformed_points[5][1]); max[2] = Max(max[2], m_transformed_points[5][2]);
//		m_transformed_points[6] = (transform * vec4(m_max[0], m_max[1], m_min[2], 1)).XYZ();
//		min[0] = Min(min[0], m_transformed_points[6][0]); min[1] = Min(min[1], m_transformed_points[6][1]); min[2] = Min(min[2], m_transformed_points[6][2]);
//		max[0] = Max(max[0], m_transformed_points[6][0]); max[1] = Max(max[1], m_transformed_points[6][1]); max[2] = Max(max[2], m_transformed_points[6][2]);
//		m_transformed_points[7] = (transform * vec4(m_max[0], m_max[1], m_max[2], 1)).XYZ();
//		min[0] = Min(min[0], m_transformed_points[7][0]); min[1] = Min(min[1], m_transformed_points[7][1]); min[2] = Min(min[2], m_transformed_points[7][2]);
//		max[0] = Max(max[0], m_transformed_points[7][0]); max[1] = Max(max[1], m_transformed_points[7][1]); max[2] = Max(max[2], m_transformed_points[7][2]);
//		return *this;
//	}

//	const AxisAlignedBox& AxisAlignedBox::TransformNode(const Math::mat4& transform) const
//	{
//		Math::vec3 p1, p2;
//		return TransformNode(transform, p1, p2);
//	}

//	vec3& AxisAlignedBox::operator [] (int index)
//	{
//		return m_border_points[index];
//	}

//	const vec3& AxisAlignedBox::operator [] (int index) const
//	{
//		return m_border_points[index];
//	}

//	bool AxisAlignedBox::DoCrossLine(const Line3D& line) const
//	{
//		if (!ClipSegment3D(line.GetOrigin(), line.GetDestination(), m_min, m_max))
//			return false;
//		else
//			return true;
//	}    

    void AxisAlignedBox::Set(const vec3& min_point, const vec3& max_point)
    {
        m_min = max_point;
        m_max = min_point;
    }

    void SaveBoundingBox(System::Buffer *buffer, const AxisAlignedBox& value)
    {
        SaveVector3f(buffer, value.m_min);
        SaveVector3f(buffer, value.m_max);
    }

    void LoadBoundingBox(System::Buffer *buffer, AxisAlignedBox& value)
    {
        LoadVector3f(buffer, value.m_min);
        LoadVector3f(buffer, value.m_max);
    }
}
