#include "frustum.h"
#include "math.h"
#include "relations.h"

namespace Math
{
	Frustum::Frustum()
	{
		m_fov = PI/4.0f;
		m_zfar = 1000.0f;
		m_znear = 1.0f;
		m_aspect = 3.0f / 4.0f;
		UpdateMatrix();
		CalculatePlanes();
	}

	const Plane& Frustum::GetPlane(FrustumPlane value) const
	{
		return m_planes[value];
	}

	void Frustum::CalculatePlanes()
	{
		float e = 1 / tan(m_fov / 2.0);
		float a = m_aspect;
		float lr_coeff = 1 / sqrtf(1 + e*e);
		float tb_coeff = 1 / sqrtf(a*a + e*e);
		Plane planes2[6];
		Math::vec3 points2[8];

        m_planes[PLANE_NEAR].Set(m_projection_matrix.GetRow(3) + m_projection_matrix.GetRow(2)).Normalize();
        planes2[PLANE_NEAR].Set(0, 0, -1, -m_znear).Normalize();

        m_planes[PLANE_FAR].Set(m_projection_matrix.GetRow(3) - m_projection_matrix.GetRow(2)).Normalize();
		planes2[PLANE_FAR].Set(0, 0, 1, m_zfar);

		m_planes[PLANE_LEFT].Set((m_projection_matrix.GetRow(3) + m_projection_matrix.GetRow(0)).Normalize());
		planes2[PLANE_LEFT].Set(e * lr_coeff, 0, -lr_coeff, 0);

		m_planes[PLANE_RIGHT].Set((m_projection_matrix.GetRow(3) - m_projection_matrix.GetRow(0)).Normalize());
		planes2[PLANE_RIGHT].Set(-e * lr_coeff, 0, -lr_coeff, 0);

		m_planes[PLANE_BOTTOM].Set((m_projection_matrix.GetRow(3) + m_projection_matrix.GetRow(1)).Normalize());
		planes2[PLANE_BOTTOM].Set(0, e * tb_coeff, -a * tb_coeff, 0);

		m_planes[PLANE_TOP].Set((m_projection_matrix.GetRow(3) - m_projection_matrix.GetRow(1)).Normalize());
		planes2[PLANE_TOP].Set(0, -e * tb_coeff, -a * tb_coeff, 0);

		CrossThreePlane(m_planes[PLANE_NEAR], m_planes[PLANE_LEFT], m_planes[PLANE_TOP], m_points[NLT]);
		CrossThreePlane(m_planes[PLANE_NEAR], m_planes[PLANE_LEFT], m_planes[PLANE_BOTTOM], m_points[NLB]);
		CrossThreePlane(m_planes[PLANE_NEAR], m_planes[PLANE_RIGHT], m_planes[PLANE_TOP], m_points[NRT]);
		CrossThreePlane(m_planes[PLANE_NEAR], m_planes[PLANE_RIGHT], m_planes[PLANE_BOTTOM], m_points[NRB]);
		CrossThreePlane(m_planes[PLANE_FAR], m_planes[PLANE_LEFT], m_planes[PLANE_TOP], m_points[FLT]);
		CrossThreePlane(m_planes[PLANE_FAR], m_planes[PLANE_LEFT], m_planes[PLANE_BOTTOM], m_points[FLB]);
		CrossThreePlane(m_planes[PLANE_FAR], m_planes[PLANE_RIGHT], m_planes[PLANE_TOP], m_points[FRT]);
		CrossThreePlane(m_planes[PLANE_FAR], m_planes[PLANE_RIGHT], m_planes[PLANE_BOTTOM], m_points[FRB]);

		CrossThreePlane(planes2[PLANE_NEAR], planes2[PLANE_LEFT], planes2[PLANE_TOP], points2[NLT]);
		CrossThreePlane(planes2[PLANE_NEAR], planes2[PLANE_LEFT], planes2[PLANE_BOTTOM], points2[NLB]);
		CrossThreePlane(planes2[PLANE_NEAR], planes2[PLANE_RIGHT], planes2[PLANE_TOP], points2[NRT]);
		CrossThreePlane(planes2[PLANE_NEAR], planes2[PLANE_RIGHT], planes2[PLANE_BOTTOM], points2[NRB]);
		CrossThreePlane(planes2[PLANE_FAR], planes2[PLANE_LEFT], planes2[PLANE_TOP], points2[FLT]);
		CrossThreePlane(planes2[PLANE_FAR], planes2[PLANE_LEFT], planes2[PLANE_BOTTOM], points2[FLB]);
		CrossThreePlane(planes2[PLANE_FAR], planes2[PLANE_RIGHT], planes2[PLANE_TOP], points2[FRT]);
		CrossThreePlane(planes2[PLANE_FAR], planes2[PLANE_RIGHT], planes2[PLANE_BOTTOM], points2[FRB]);

		//float e = m_znear
		//float a = 1.0f / e;
		//m_planes[PLANE_NEAR].Set(vec3(0,0,-1), m_znear);
		//m_planes[PLANE_FAR].Set(vec3(0,0,1), m_zfar);
		//m_planes[PLANE_LEFT].Set(vec3(e/sqrt(e*e+1), 0, -1/sqrt(e*e+1)), 0);
		//m_planes[PLANE_RIGHT].Set(vec3(-e/sqrt(e*e+1), 0, -1/sqrt(e*e+1)), 0);
		//m_planes[PLANE_BOTTOM].Set(vec3(0, e/sqrt(e*e+a*a), -1/sqrt(e*e+a*a)), 0);
		//m_planes[PLANE_TOP].Set(vec3(0, -e/sqrt(e*e+a*a), -1/sqrt(e*e+a*a)), 0);
	}

	/*void Frustum::Set(float left, float right, float top, float bottom, float znear, float zfar)
	{
		m_left = left;
		m_right = right;
		m_top = top;
		m_bottom = bottom;
		UpdateMatrix();
		CalculatePlanes();
	}
*/
	//void Frustum::Set(float fov, float width, float height, float znear, float zfar)
	//{
	//	Set(fov, height/width, znear, zfar);
	//}

	void Frustum::Set(float fov, float width, float height, float znear, float zfar)
	{
		m_fov = fov;
		m_aspect = width / height;
		m_znear = znear;
		m_zfar = zfar;
		UpdateMatrix();
		CalculatePlanes();
	}

	const mat4& Frustum::GetProjectionMatrix() const
	{
		return m_projection_matrix;
	}

	const ClipSpace Frustum::ToClipSpace() const
	{
		ClipSpace res;
		//	skip near plane
		for (int i = 0; i != 6; ++i)
		{
			res.Add(m_planes[i]);
		}
		return res;
	}

	void Frustum::UpdateMatrix()
	{
		m_projection_matrix = mat4::CreatePerspectiveProjection(m_fov, m_aspect, m_znear, m_zfar);
	}

	bool Frustum::Save(std::ostream& stream) const
	{
		for (int i = 0; i < 6; ++i)
			if (!m_planes[i].Save(stream))
				return (out_error() << "Can't save frustum" << std::endl, false);

		if (!m_projection_matrix.Save(stream))
			return (out_error() << "Can't save frustum" << std::endl, false);

		stream.write((char*)&m_fov, sizeof(m_fov));
		stream.write((char*)&m_aspect, sizeof(m_aspect));
		stream.write((char*)&m_znear, sizeof(m_znear));
		stream.write((char*)&m_zfar, sizeof(m_zfar));

		return true;
	}

	bool Frustum::Load(std::istream& stream)
	{
		
		for (int i = 0; i < 6; ++i)
			if (!m_planes[i].Load(stream))
				return (out_error() << "Can't load frustum" << std::endl, false);

		if (!m_projection_matrix.Load(stream))
			return (out_error() << "Can't load frustum" << std::endl, false);

		stream.read((char*)&m_fov, sizeof(m_fov));
		stream.read((char*)&m_aspect, sizeof(m_aspect));
		stream.read((char*)&m_znear, sizeof(m_znear));
		stream.read((char*)&m_zfar, sizeof(m_zfar));

		return true;
	}

	const Math::vec3& Frustum::GetPoint(FrustumPoints value) const
	{
		return m_points[value];
	}

    /**
      * Creates a clip space from current frustum and point.
      */
    const ClipSpace BuildClipSpaceFromPoint(const Frustum& f, const Math::vec3& p)
    {
        if (ClassifyPoint(p, f) == Relation::INSIDE)
            return f.ToClipSpace();

        ClipSpace result;
        //  true - point in front of the plane, false otherwise
        bool front[6];
        for (int i = 0; i != 6; ++i)
        {
			Math::Frustum::FrustumPlane plane = (Math::Frustum::FrustumPlane)i;
			front[i] = ClassifyPoint(p, f.GetPlane(plane)) == Relation::FRONT;
            //  planes for which point is in fornt of them construct add into the resulting clipspace
            if (front[i])
				result.Add(f.GetPlane(plane));
        }

        //  for each plane that forms boundary (front[i] == true) create a plane, the goes
        //  through the
        for (int i = 0; i != 6; ++i)
        {
			Frustum::FrustumPlane plane_a = (Frustum::FrustumPlane)i;
            if (!front[i])
                continue;
			const Plane& a = f.GetPlane(plane_a);
            for (int j = 0; j != 6; ++j)
            {
				Frustum::FrustumPlane plane_b = (Frustum::FrustumPlane)j;
				if (front[j] || !Frustum::IsAdjacent(plane_a, plane_b))
                    continue;
				const Plane& b = f.GetPlane(plane_b);
                Line3D line;
                if (CrossPlanePlane(a, b, line) != Relation::INTERSECT)
                    continue;
				Plane plane;
				plane.Set(line, p);
				result.Add(plane);
            }
        }

        return result;
    }

	bool Frustum::IsAdjacent(Frustum::FrustumPlane a, Frustum::FrustumPlane b)
	{
		switch (a)
		{
		case FrustumPlane::PLANE_TOP:
			if (b == PLANE_BOTTOM)
				return false;
			else
				return true;
		case FrustumPlane::PLANE_FAR:
			if (b == PLANE_NEAR)
				return false;
			else
				return true;
		case FrustumPlane::PLANE_LEFT:
			if (b == PLANE_RIGHT)
				return false;
			else
				return true;
		case FrustumPlane::PLANE_NEAR:
			if (b == PLANE_FAR)
				return false;
			else
				return true;
		case FrustumPlane::PLANE_RIGHT:
			if (b == PLANE_LEFT)
				return false;
			else
				return true;
		case FrustumPlane::PLANE_BOTTOM:
			if (b == PLANE_TOP)
				return false;
			else
				return true;
		}
		return false;
	}
}

