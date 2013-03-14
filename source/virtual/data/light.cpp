#include <memory>
#include "../../utility/descriptors/light_desc.h"
#include "light.h"
#include "lights/point_light.h"

namespace Virtual
{
	Light* Light::CreateLight(const Utility::LightDesc& value)
	{
		if (value.m_type == L"POINT")
		{
			std::unique_ptr<PointLight> light(new PointLight(value));
			return light.release();
		}
		else
			return nullptr;
	}
}
