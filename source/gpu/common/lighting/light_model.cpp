#include "light_model.h"

namespace GPU
{
	using LightModelDesc = std::pair<LightModel, System::string>;
	static const LightModelDesc g_light_models[] = {
		LightModelDesc(LightModel::PerVertexDiffuse, L"Per-vertex diffuse"),
		LightModelDesc(LightModel::PerFragmentDiffuse, L"Per-pixel diffuse"),
		LightModelDesc(LightModel::PerVertexDiffuseSpecular, L"Per-vertex diffuse+specular"),
		LightModelDesc(LightModel::PerFragmentlDiffuseSpecular, L"Per-pixel diffuse+specular"),
		LightModelDesc(LightModel::BumpMapping, L"Bump mapping"),
	};

	const System::string AsString(const LightModel& v)
	{
		for (size_t i = 0; i != std::extent<decltype(g_light_models)>::value; ++i)
		{
			if (g_light_models[i].first == v)
				return g_light_models[i].second;
		}
		return L"ERROR";
	}

	using LightAttenuationDesc = std::pair<LightAttenuation, System::string>;
	static const LightAttenuationDesc g_light_attenuations[] = {
		LightAttenuationDesc(LightAttenuation::Constant, L"Constant"),
		LightAttenuationDesc(LightAttenuation::Linear, L"Linear"),
		LightAttenuationDesc(LightAttenuation::Quadratic, L"Quadratic")
	};

	const System::string AsString(LightAttenuation value)
	{
		for (size_t i = 0; i != std::extent<decltype(g_light_attenuations)>::value; ++i)
		{
			if (g_light_attenuations[i].first == value)
				return g_light_attenuations[i].second;
		}
		return L"ERROR";
	}

	using LightTypeDesc = std::pair<LightType, System::string>;
	static const LightTypeDesc g_light_types[] = {
		LightTypeDesc(LightType::Point, L"Point"),
		LightTypeDesc(LightType::Spot, L"Spot")
	};

	const System::string AsString(LightType value)
	{
		for (size_t i = 0; i != std::extent<decltype(g_light_types)>::value; ++i)
		{
			if (g_light_types[i].first == value)
				return g_light_types[i].second;
		}
		return L"ERROR";
	}
}
