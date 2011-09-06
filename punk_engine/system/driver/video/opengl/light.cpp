#include "light.h"

namespace Driver
{
	Light::Light()
	{
		m_Ambient[0] = 94.0f/255.f;
		m_Ambient[1] = 94.0f/255.f;
		m_Ambient[2] = 94.0f/255.f;
		m_Ambient[3] = 1.0f;

		m_Diffuse[0] = 226.0f/255.0f;
		m_Diffuse[1] = 226.0f/255.0f;
		m_Diffuse[2] = 226.0f/255.0f;
		m_Diffuse[3] = 1.0f;

		m_Specular[0] = 125.0f/255.0f;
		m_Specular[1] = 125.0f/255.0f;
		m_Specular[2] = 125.0f/255.0f;
		m_Specular[3] = 1.0f;

		m_Position[0] = 0.0f;
		m_Position[1] = 5.0f;
		m_Position[2] = 5.0f;
		m_Position[3] = 0.0f;

		m_Direction[0] = 0.0f;
		m_Direction[1] = 0.0f;
		m_Direction[2] = -1.0f;

		m_SpecularPower = 25;
	}

}
