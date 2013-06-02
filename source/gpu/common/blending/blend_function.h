#ifndef BLEND_FUNCTION_H
#define BLEND_FUNCTION_H

#include "../../../config.h"
#include "../../../string/string.h"

namespace GPU
{
	enum class BlendFunction {
		SourceAlpha,
		One,
		OneMinusSrcAlpha
	};

	extern PUNK_ENGINE_API const System::string AsString(BlendFunction value);
}

#endif // BLEND_FUNCTION_H
