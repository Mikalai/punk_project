#ifdef USE_OPENAL

#include "alext.h"
#include "al_error.h"
#include "al_format.h"

namespace Audio
{
	ALint AudioFormatToOpenALFormat(Format value)
	{
		switch (value)
		{
		case Audio::Format::MONO8:
			return AL_FORMAT_MONO8;
		case Audio::Format::MONO16:
			return AL_FORMAT_MONO16;
		case Audio::Format::STEREO8:
			return AL_FORMAT_STEREO8;
		case Audio::Format::STEREO16:
			return AL_FORMAT_STEREO16;
		default:
			throw System::PunkException(L"Invalid audio format");
		}
	}
}

#endif // USE_OPENAL
