#include "alext.h"
#include "al_error.h"

namespace Audio
{
	void ValidateOpenAL(const System::string& msg)
	{
		auto error = alGetError();
		switch (error)
		{
		case AL_NO_ERROR:
			return;
		case AL_INVALID_NAME:
			throw PunkAudioOpenALInvalidName(msg);
		case AL_INVALID_ENUM:
			throw PunkAudioOpenALInvalidEnum(msg);
		case AL_INVALID_OPERATION:
			throw PunkAudioOpenALInvalidOperation(msg);
		case AL_INVALID_VALUE:
			throw PunkAudioOpenALInvalidValue(msg);
		case AL_OUT_OF_MEMORY:
			throw PunkAudioOpenALOutOfMemory(msg);
		default:
			throw System::PunkException(msg);
		}
	}
}