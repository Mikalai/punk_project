#ifndef LIGHT_MODEL_H
#define LIGHT_MODEL_H

#include "../../../config.h"
#include "../../../string/string.h"

namespace Gpu
{
	enum class LightModel {
		PerVertexDiffuse,
		PerFragmentDiffuse,
		PerVertexDiffuseSpecular,
		PerFragmentlDiffuseSpecular,
        BumpMappingDiffuse,
        BumpMappingDiffuseSpecular
	};

	enum class LightAttenuation {
		Constant,
		Linear,
		Quadratic
	};

	enum class LightType {
		Point,
        Direction,
        Spot
	};

	extern PUNK_ENGINE_API const System::string AsString(LightModel value);
	extern PUNK_ENGINE_API const System::string AsString(LightAttenuation  value);
	extern PUNK_ENGINE_API const System::string AsString(LightType value);
}

#endif // LIGHT_MODEL_H
