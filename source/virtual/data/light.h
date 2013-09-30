#ifndef _H_PUNK_VIRTUAL_LIGHT
#define _H_PUNK_VIRTUAL_LIGHT

#include "../../system/object.h"
#include "../../math/vec3.h"

namespace Utility { class LightDesc; }
namespace Virtual
{
	class PUNK_ENGINE_API Light : public System::Object
	{
	public:
        Light();
        Light(const Light&) = delete;
        Light& operator = (const Light&) = delete;
        virtual ~Light();

        PUNK_OBJECT(Light)
	};

    PUNK_OBJECT_UTIL(Light)
}

#endif
