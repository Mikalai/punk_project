#ifndef _H_PUNK_AUDIO_OPENAL_ERROR
#define _H_PUNK_AUDIO_OPENAL_ERROR

#include "../../system/errors/exceptions.h"

namespace Audio
{
	class PunkAudioOpenALInvalidName final : public System::PunkException 
	{
	public:
		PunkAudioOpenALInvalidName() : PunkException(L"PunkAudioOpenALInvalidName") {}
		PunkAudioOpenALInvalidName(const System::string& msg) : PunkException(L"PunkAudioOpenALInvalidName: " + msg) {}
	};

	class PunkAudioOpenALInvalidEnum final : public System::PunkException 
	{
	public:
		PunkAudioOpenALInvalidEnum() : PunkException(L"PunkAudioOpenALInvalidEnum") {}
		PunkAudioOpenALInvalidEnum(const System::string& msg) : PunkException(L"PunkAudioOpenALInvalidEnum: " + msg) {}
	};

	class PunkAudioOpenALInvalidValue final : public System::PunkException 
	{
	public:
		PunkAudioOpenALInvalidValue() : PunkException(L"PunkAudioOpenALInvalidValue") {}
		PunkAudioOpenALInvalidValue(const System::string& msg) : PunkException(L"PunkAudioOpenALInvalidValue: " + msg) {}
	};

	class PunkAudioOpenALInvalidOperation final : public System::PunkException 
	{
	public:
		PunkAudioOpenALInvalidOperation() : PunkException(L"PunkAudioOpenALInvalidOperation") {}
		PunkAudioOpenALInvalidOperation(const System::string& msg) : PunkException(L"PunkAudioOpenALInvalidOperation: " + msg) {}
	};

	class PunkAudioOpenALOutOfMemory final : public System::PunkException 
	{
	public:
		PunkAudioOpenALOutOfMemory() : PunkException(L"PunkAudioOpenALOutOfMemory") {}
		PunkAudioOpenALOutOfMemory(const System::string& msg) : PunkException(L"PunkAudioOpenALOutOfMemory: " + msg) {}
	};

	extern void ValidateOpenAL(const System::string& msg);
}

#endif	//	_H_PUNK_AUDIO_OPENAL_ERROR