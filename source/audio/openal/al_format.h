#ifndef _H_PUNK_OPENAL_FORMATS
#define _H_PUNK_OPENAL_FORMATS

#ifdef USE_OPENAL

#include "../audio_format.h"
#include "openal.h"

namespace Audio
{
	extern ALint AudioFormatToOpenALFormat(Format value);
}

#endif  //  USE_OPENAL

#endif	//	_H_PUNK_OPENAL_FORMATS
