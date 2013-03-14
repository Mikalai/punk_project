#include "frustum.h"
#include "math.h"

namespace Math
{
	Frustum::Frustum()
	{
		m_left = -1.0f;
		m_right = 1.0f;
		m_top = m_right*3.0f / 4.0f;
		m_bottom = - m_right*3.0f / 4.0f;
		m_fov = PI/4.0f;
		m_zfar = 1000.0f;
		m_znear = 1.0f;
		m_aspect = 3.0f / 4.0f;
		UpdateMatrix();
		CalculatePlanes();
	}

	void Frustum::CalculatePlanes()
	{
		m_planes[PLANE_NEAR].Set((m_projection_matrix.GetRow(3) + m_projection_matrix.GetRow(2)).Normalize());
		m_planes[PLANE_FAR].Set((m_projection_matrix.GetRow(3) - m_projection_matrix.GetRow(2)).Normalize());
		m_planes[PLANE_LEFT].Set((m_projection_matrix.GetRow(3) + m_projection_matrix.GetRow(0)).Normalize());
		m_planes[PLANE_RIGHT].Set((m_projection_matrix.GetRow(3) - m_projection_matrix.GetRow(0)).Normalize());
		m_planes[PLANE_BOTTOM].Set((m_projection_matrix.GetRow(3) + m_projection_matrix.GetRow(1)).Normalize());
		m_planes[PLANE_TOP].Set((m_projection_matrix.GetRow(3) - m_projection_matrix.GetRow(1)).Normalize());

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

	void Frustum::Set(float fov, float aspect, float znear, float zfar)
	{
		m_fov = fov;
		m_aspect = aspect;
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
		for (int i = 0; i < 5; ++i)
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
}