#ifndef _H_PUNK_MATH_ELLIPSOID
#define _H_PUNK_MATH_ELLIPSOID

#include "../config.h"
#include "vec3.h"

namespace Math
{
	class PUNK_ENGINE_PUBLIC Ellipsoid
	{
	public:
		Ellipsoid(float rx, float ry, float rz);
		
		float GetRadiusX() const { return m_rx; }
		float GetRadiusY() const { return m_ry; }
		float GetRadiusZ() const { return m_rz; }
		void SetRadiusX(float value) { m_rx = value; }
		void SetRadiusY(float value) { m_ry = value; }
		void SetRadiusZ(float value) { m_rz = value; }

		void SetDimension(float rx, float ry, float rz) { (m_rx = rx, m_ry = ry, m_rz = rz); }
		void SetCenter(const vec3& value) { m_center = value; }
		const vec3& GetCenter() const { return m_center; }

	private:
		float m_rx;
		float m_ry;
		float m_rz;
		vec3 m_center;
	};
}

#endif	//	_H_LPW_ELLIPSOID