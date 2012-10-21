#ifndef _H_PUNK_UTILITY_ANIMATION_MIXER
#define _H_PUNK_UTILITY_ANIMATION_MIXER

#include "../../config.h"
#include "../../system/object.h"

namespace System { class string; }

namespace Virtual
{
	class PUNK_ENGINE AnimationMixer : public System::Object
	{
	public:
		virtual ~AnimationMixer();
	};
}

#endif