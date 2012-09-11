/*
File: Camera.h
Author: Abramau Mikalai
Description: There is a class that simplify working with
view matrix
*/

#ifndef _H_PUNK_OPENGL_CAMERA
#define _H_PUNK_OPENGL_CAMERA

#include "frustum.h"

namespace Math
{
	class PUNK_ENGINE Camera : public Frustum
	{
	protected:
		float m_latitude;
		float m_longitude;
		float m_distance;
		void UpdateMatrix();
	public:
		Camera();
		Camera(const Camera& camera);
		Camera& operator = (const Camera& camera);

		void SetLatitude(float value);
		void SetLongitude(float value);
		void AdvanceLatitude(float value);
		void AdvanceLongitude(float value);
		float GetLatitude() const;
		float GetLongitude() const;
	};
}

#endif	//_CAMERA_H
