#include "camera.h"
#include "constants.h"

namespace Math
{
	Camera::Camera()
		: Frustum()
		, m_latitude(0)
		, m_longitude(0)
	{UpdateMatrix();}

	Camera::Camera(const Camera& camera)
		: Frustum(camera)
		, m_latitude(camera.m_latitude)
		, m_longitude(camera.m_longitude)
	{UpdateMatrix();}

	Camera& Camera::operator = (const Camera& camera)
	{
		if (this != &camera)
		{
			Frustum::operator = (camera);
			m_latitude = camera.m_latitude;
			m_longitude = camera.m_longitude;
		}
		return *this;
	}

	void Camera::SetLatitude(float lat)
	{
		m_latitude = lat;
		UpdateMatrix();
	}

	void Camera::SetLongitude(float lon)
	{
		m_longitude = lon;
		UpdateMatrix();
	}

	void Camera::AdvanceLatitude(float lat)
	{
		m_latitude += lat;
		if (m_latitude > PI/2.0f)
			m_latitude = PI/2.0f;
		if (m_latitude < -PI/2.0f)
			m_latitude = -PI/2.0f;
		UpdateMatrix();
	}

	void Camera::AdvanceLongitude(float lon)
	{
		m_longitude += lon;
		if (m_longitude > 2*PI)
			m_longitude = 0;
		if (m_longitude < 0)
			m_longitude = 2*PI;
		UpdateMatrix();
	}

	float Camera::GetLatitude() const
	{
		return m_latitude;
	}

	float Camera::GetLongitude() const
	{
		return m_longitude;
	}

	void Camera::UpdateMatrix() 
	{
		m_direction = vec3(cos(m_latitude)*sin(m_longitude), sin(m_latitude), cos(m_latitude)*cos(m_longitude));
		Frustum::UpdateMatrix();
	}
}

