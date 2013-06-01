#ifndef FOG_MODE_H
#define FOG_MODE_H

#include "../../../config.h"
#include "../../../string/string.h"

namespace GPU
{
	enum class FogMode { Linear, Exponent, Exponent2 };

	extern const System::string PUNK_ENGINE_PUBLIC AsString(FogMode mode);
}

#endif // FOG_MODE_H
