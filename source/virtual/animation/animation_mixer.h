#ifndef _H_PUNK_UTILITY_ANIMATION_MixER
#define _H_PUNK_UTILITY_ANIMATION_MixER

#include "../../config.h"
#include "../../system/object.h"

namespace System { class string; }

namespace Virtual
{
	class PUNK_ENGINE_API AnimationMixer : public System::Object
	{
	public:
		virtual ~AnimationMixer();
	};
}

#endif