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
		virtual const Math::vec3 GetPosition() const = 0;

		static Light* CreateLight(const Utility::LightDesc& value);
	};
}

#endif