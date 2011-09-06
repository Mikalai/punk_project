#ifndef _LIGHT
#define _LIGHT

#include "os.h"

using namespace Math;

namespace Driver
{
	class Light
	{
	public:
		vec3 m_Position;
		vec3 m_Direction;
		vec4 m_Ambient;
		vec4 m_Diffuse;
		vec4 m_Specular;
		float m_SpecularPower;
		bool m_IsOn;

		Light();
	};

}
#endif
