#include "camera.h"
#include "..\math\math.h"

namespace Common
{
	static Camera* g_dummy_camera;
	static Camera* g_active_camera;

	void Camera::SetActiveCamera(Camera* camera)
	{
		g_active_camera = camera;
	}

	const Camera* Camera::GetActiveCamera()
	{
		if (g_active_camera)
			return g_active_camera;

		if (g_dummy_camera)
			return g_dummy_camera;

		g_dummy_camera = new Camera();

		return g_dummy_camera;
	}

	void Camera::Release()
	{
		if (g_dummy_camera)
			delete g_dummy_camera;
	}

	Camera::Camera() : Math::Frustum(), m_angle_around_y_axis(0), m_angle_around_x_axis(0) 
	{
		m_type = CAMERA_FREE;

		float tang = tanf(m_fov / 2.0f);
		m_near_height = m_znear * tang;
		m_near_width = m_near_height * m_aspect;
		m_far_height = m_zfar * tang;
		m_far_width = m_far_height * m_aspect;	

		Math::vec3 x(1,0,0);
		Math::vec3 y(0,1,0);
		Math::vec3 z(0,0,1);

		Math::vec3 p(0,0,0);

		Math::vec3 near_center = p - z * m_znear;
		Math::vec3 far_center = p - z * m_zfar;

		Math::vec3 near_top_left = near_center + y * m_near_height - x * m_near_width;
		Math::vec3 near_top_right = near_center + y * m_near_height + x * m_near_width;
		Math::vec3 near_bottom_left = near_center - y * m_near_height - x * m_near_width;
		Math::vec3 near_bottom_right = near_center - y * m_near_height + x * m_near_width;

		Math::vec3 far_top_left = far_center + y * m_far_height - x * m_far_width;
		Math::vec3 far_top_right = far_center + y * m_far_height + x * m_far_width;
		Math::vec3 far_bottom_left = far_center - y * m_far_height - x * m_far_width;
		Math::vec3 far_bottom_right = far_center - y * m_far_height + x * m_far_width;

		m_planes[PLANE_TOP].MakeFromPoints(near_top_right, near_top_left, far_top_left);
		m_planes[PLANE_BOTTOM].MakeFromPoints(near_bottom_left, near_bottom_right, far_bottom_right);
		m_planes[PLANE_LEFT].MakeFromPoints(near_top_left, near_bottom_left, far_bottom_left);
		m_planes[PLANE_RIGHT].MakeFromPoints(near_bottom_right, near_top_right, far_top_right);
		m_planes[PLANE_NEAR].MakeFromPoints(near_top_left, near_top_right, near_bottom_right);
		m_planes[PLANE_FAR].MakeFromPoints(far_top_right, far_top_left, far_bottom_left);

		StaticGeometry::Vertex* verts = new StaticGeometry::Vertex[8];
		verts[0].x = near_top_left[0];		verts[0].y = near_top_left[1];		verts[0].z = near_top_left[2];		verts[0].w = 0;
		verts[1].x = near_top_right[0];		verts[1].y = near_top_right[1];		verts[1].z = near_top_right[2];		verts[1].w = 0;
		verts[2].x = near_bottom_left[0];	verts[2].y = near_bottom_left[1];	verts[2].z = near_bottom_left[2];	verts[2].w = 0;
		verts[3].x = near_bottom_right[0];	verts[3].y = near_bottom_right[1];	verts[3].z = near_bottom_right[2];	verts[3].w = 0;
		verts[4].x = far_top_left[0];		verts[4].y = far_top_left[1];		verts[4].z = far_top_left[2];		verts[4].w = 0;
		verts[5].x = far_top_right[0];		verts[5].y = far_top_right[1];		verts[5].z = far_top_right[2];		verts[5].w = 0;
		verts[6].x = far_bottom_left[0];	verts[6].y = far_bottom_left[1];	verts[6].z = far_bottom_left[2];	verts[6].w = 0;
		verts[7].x = far_bottom_right[0];	verts[7].y = far_bottom_right[1];	verts[7].z = far_bottom_right[2];	verts[7].w = 0;

		unsigned short *index = new unsigned short[36];
		
		unsigned short ind[36] = {
			0,1,2,
			2,1,3,
			1,3,5,
			5,3,7,
			7,5,6,
			6,5,4,
			6,4,2,
			2,4,0,
			4,0,5,
			5,0,1,
			6,2,7,
			7,2,3};

			memcpy(index, ind, sizeof(unsigned short)*36);

		StaticGeometry geom;
		geom.Set(verts, 8, index, 36);

		m_vao = new Render::VertexArrayObject();
		m_vao->Create(geom, Render::VertexSolidColor::InitVertexBuffer);
	}

	void Camera::MoveForward(float length)
	{
		m_position += m_direction * length;
		UpdateMatrix();
	}

	void Camera::MoveBackward(float length)
	{
		m_position -= m_direction * length;
		UpdateMatrix();
	}

	void Camera::ShiftLeft(float length)
	{
		Math::vec3 dir = m_up.Cross(m_direction).Normalized();
		m_position += dir * length;
		UpdateMatrix();
	}

	void Camera::ShiftRight(float length)
	{
		Math::vec3 dir = m_direction.Cross(m_up).Normalized();
		m_position += dir * length;
		UpdateMatrix();
	}		

	void Camera::Rotate(float angle_around_y_axis, float angle_around_x_axis)
	{
		m_angle_around_x_axis += angle_around_x_axis;
		m_angle_around_y_axis += angle_around_y_axis;

		if (m_angle_around_x_axis > Math::PI/2.0f-0.001f)
			m_angle_around_x_axis = Math::PI/2.0f-0.001f;
		else if (m_angle_around_x_axis < -Math::PI/2.0f+0.001f)
			m_angle_around_x_axis = -Math::PI/2.0f+0.001f;

		if (m_angle_around_y_axis > 2*Math::PI)
			m_angle_around_y_axis = 0;
		else if (m_angle_around_y_axis < 0)
			m_angle_around_y_axis = 2*Math::PI;

		m_direction = (Math::mat4::CreateRotation(0,1,0, m_angle_around_y_axis).RotationPart()*
			Math::mat4::CreateRotation(1,0,0,m_angle_around_x_axis).RotationPart() *			
			Math::vec3(0,0,1)).Normalize();

		UpdateMatrix();
	}
}
