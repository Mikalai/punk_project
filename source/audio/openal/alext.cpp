#ifdef USE_OPENAL

#ifdef _WIN32
#include <windows.h>
#endif

#include "alext.h"

namespace Audio
{
	LPALENABLE alEnable;
	LPALDISABLE alDisable;
	LPALISENABLED alIsEnabled;
	LPALGETSTRING alGetString;
	LPALGETBOOLEANV alGetBooleanv;
	LPALGETINTEGERV alGetIntegerv;
	LPALGETFLOATV alGetFloatv;
	LPALGETDOUBLEV alGetDoublev;
	LPALGETBOOLEAN alGetBoolean;
	LPALGETINTEGER alGetInteger;
	LPALGETFLOAT alGetFloat;
	LPALGETDOUBLE alGetDouble;
	LPALGETERROR alGetError;
	LPALISEXTENSIONPRESENT alIsExtensionPresent;
	LPALGETPROCADDRESS alGetProcAddress;
	LPALGETENUMVALUE alGetEnumValue;
	LPALLISTENERF alListenerf;
	LPALLISTENER3F alListener3f;
	LPALLISTENERFV alListenerfv;
	LPALLISTENERI alListeneri;
	LPALLISTENER3I alListener3i;
	LPALLISTENERIV alListeneriv;
	LPALGETLISTENERF alGetListenerf;
	LPALGETLISTENER3F alGetListener3f;
	LPALGETLISTENERFV alGetListenerfv;
	LPALGETLISTENERI alGetListeneri;
	LPALGETLISTENER3I alGetListener3i;
	LPALGETLISTENERIV alGetListeneriv;
	LPALGENSOURCES alGenSources;
	LPALDELETESOURCES alDeleteSources;
	LPALISSOURCE alIsSource;
	LPALSOURCEF alSourcef;
	LPALSOURCE3F alSource3f;
	LPALSOURCEFV alSourcefv;
	LPALSOURCEI alSourcei;
	LPALSOURCE3I alSource3i;
	LPALSOURCEIV alSourceiv;
	LPALGETSOURCEF alGetSourcef;
	LPALGETSOURCE3F alGetSource3f;
	LPALGETSOURCEFV alGetSourcefv;
	LPALGETSOURCEI alGetSourcei;
	LPALGETSOURCE3I alGetSource3i;
	LPALGETSOURCEIV alGetSourceiv;
	LPALSOURCEPLAYV alSourcePlayv;
	LPALSOURCESTOPV alSourceStopv;
	LPALSOURCEREWINDV alSourceRewindv;
	LPALSOURCEPAUSEV alSourcePausev;
	LPALSOURCEPLAY alSourcePlay;
	LPALSOURCESTOP alSourceStop;
	LPALSOURCEREWIND alSourceRewind;
	LPALSOURCEPAUSE alSourcePause;
	LPALSOURCEQUEUEBUFFERS alSourceQueueBuffers;
	LPALSOURCEUNQUEUEBUFFERS alSourceUnqueueBuffers;
	LPALGENBUFFERS alGenBuffers;
	LPALDELETEBUFFERS alDeleteBuffers;
	LPALISBUFFER alIsBuffer;
	LPALBUFFERDATA alBufferData;
	LPALBUFFERF alBufferf;
	LPALBUFFER3F alBuffer3f;
	LPALBUFFERFV alBufferfv;
	LPALBUFFERI alBufferi;
	LPALBUFFER3I alBuffer3i;
	LPALBUFFERIV alBufferiv;
	LPALGETBUFFERF alGetBufferf;
	LPALGETBUFFER3F alGetBuffer3f;
	LPALGETBUFFERFV alGetBufferfv;
	LPALGETBUFFERI alGetBufferi;
	LPALGETBUFFER3I alGetBuffer3i;
	LPALGETBUFFERIV alGetBufferiv;
	LPALDOPPLERFACTOR alDopplerFactor;
	LPALDOPPLERVELOCITY alDopplerVelocity;
	LPALSPEEDOFSOUND alSpeedOfSound;
	LPALDISTANCEMODEL alDistanceModel;

	LPALCCREATECONTEXT alcCreateContext;
	LPALCMAKECONTEXTCURRENT alcMakeContextCurrent;
	LPALCPROCESSCONTEXT alcProcessContext;
	LPALCSUSPENDCONTEXT alcSuspendContext;
	LPALCDESTROYCONTEXT alcDestroyContext;
	LPALCGETCURRENTCONTEXT alcGetCurrentContext;
	LPALCGETCONTEXTSDEVICE alcGetContextsDevice;
	LPALCOPENDEVICE alcOpenDevice;
	LPALCCLOSEDEVICE alcCloseDevice;
	LPALCGETERROR alcGetError;
	LPALCISEXTENSIONPRESENT alcIsExtensionPresent;
	LPALCGETPROCADDRESS alcGetProcAddress;
	LPALCGETENUMVALUE alcGetEnumValue;
	LPALCGETSTRING alcGetString;
	LPALCGETINTEGERV alcGetIntegerv;
	LPALCCAPTUREOPENDEVICE alcCaptureOpenDevice;
	LPALCCAPTURECLOSEDEVICE alcCaptureCloseDevice;
	LPALCCAPTURESTART alcCaptureStart;
	LPALCCAPTURESTOP alcCaptureStop;
	LPALCCAPTURESAMPLES alcCaptureSamples;

	HINSTANCE g_openal32;
	ALCdevice* g_device;
	ALCcontext* g_context;

	void* GetOpenALProcAddress(const char *name, ALCdevice* device)
	{
		if (alGetProcAddress == 0)
		{
			if (g_openal32 == 0)
				g_openal32 = LoadLibraryW(L"OpenAL32.dll");
			if (g_openal32 == 0)
				return 0;
			alGetProcAddress = (LPALGETPROCADDRESS)::GetProcAddress(g_openal32, "alGetProcAddress");
			if (alGetProcAddress == 0)
				return 0;
		}

		if (alcGetProcAddress == 0)
		{
			if (g_openal32 == 0)
				g_openal32 = LoadLibraryW(L"OpenAL32.dll");
			if (g_openal32 == 0)
				return 0;
			alcGetProcAddress = (LPALCGETPROCADDRESS)::GetProcAddress(g_openal32, "alcGetProcAddress");
		}
		void* res = alGetProcAddress(name);
		if (res == 0)
			if (device)
				res = alcGetProcAddress(device, name);
		if (res == 0)
			res = (void*)GetProcAddress(g_openal32, name);

		return res;

	}

	bool DestroyOpenAL()
	{
		alcMakeContextCurrent(NULL);
		alcDestroyContext(g_context);
		alcCloseDevice(g_device);
		FreeLibrary(g_openal32);
		return true;
	}

	bool InitFunctionPointers()
	{
		alEnable = (LPALENABLE)GetOpenALProcAddress("alEnable");
		alDisable = (LPALDISABLE)GetOpenALProcAddress("alDisable");
		alIsEnabled = (LPALISENABLED)GetOpenALProcAddress("alIsEnabled");
		alGetString = (LPALGETSTRING)GetOpenALProcAddress("alGetString");
		alGetBooleanv = (LPALGETBOOLEANV)GetOpenALProcAddress("alGetBooleanv");
		alGetIntegerv = (LPALGETINTEGERV)GetOpenALProcAddress("alGetIntegerv");
		alGetFloatv = (LPALGETFLOATV)GetOpenALProcAddress("alGetFloatv");
		alGetDoublev = (LPALGETDOUBLEV)GetOpenALProcAddress("alGetDoublev");
		alGetBoolean = (LPALGETBOOLEAN)GetOpenALProcAddress("alGetBoolean");
		alGetInteger = (LPALGETINTEGER)GetOpenALProcAddress("alGetInteger");
		alGetFloat = (LPALGETFLOAT)GetOpenALProcAddress("alGetFloat");
		alGetDouble = (LPALGETDOUBLE)GetOpenALProcAddress("alGetDouble");
		alGetError = (LPALGETERROR)GetOpenALProcAddress("alGetError");
		alIsExtensionPresent = (LPALISEXTENSIONPRESENT)GetOpenALProcAddress("alIsExtensionPresent");
		alGetProcAddress = (LPALGETPROCADDRESS)GetOpenALProcAddress("alGetProcAddress");
		alGetEnumValue = (LPALGETENUMVALUE)GetOpenALProcAddress("alGetEnumValue");
		alListenerf = (LPALLISTENERF)GetOpenALProcAddress("alListenerf");
		alListener3f = (LPALLISTENER3F)GetOpenALProcAddress("alListener3f");
		alListenerfv = (LPALLISTENERFV)GetOpenALProcAddress("alListenerfv");
		alListeneri = (LPALLISTENERI)GetOpenALProcAddress("alListeneri");
		alListener3i = (LPALLISTENER3I)GetOpenALProcAddress("alListener3i");
		alListeneriv = (LPALLISTENERIV)GetOpenALProcAddress("alListeneriv");
		alGetListenerf = (LPALGETLISTENERF)GetOpenALProcAddress("alGetListenerf");
		alGetListener3f = (LPALGETLISTENER3F)GetOpenALProcAddress("alGetListener3f");
		alGetListenerfv = (LPALGETLISTENERFV)GetOpenALProcAddress("alGetListenerfv");
		alGetListeneri = (LPALGETLISTENERI)GetOpenALProcAddress("alGetListeneri");
		alGetListener3i = (LPALGETLISTENER3I)GetOpenALProcAddress("alGetListener3i");
		alGetListeneriv = (LPALGETLISTENERIV)GetOpenALProcAddress("alGetListeneriv");
		alGenSources = (LPALGENSOURCES)GetOpenALProcAddress("alGenSources");
		alDeleteSources = (LPALDELETESOURCES)GetOpenALProcAddress("alDeleteSources");
		alIsSource = (LPALISSOURCE)GetOpenALProcAddress("alIsSource");
		alSourcef = (LPALSOURCEF)GetOpenALProcAddress("alSourcef");
		alSource3f = (LPALSOURCE3F)GetOpenALProcAddress("alSource3f");
		alSourcefv = (LPALSOURCEFV)GetOpenALProcAddress("alSourcefv");
		alSourcei = (LPALSOURCEI)GetOpenALProcAddress("alSourcei");
		alSource3i = (LPALSOURCE3I)GetOpenALProcAddress("alSource3i");
		alSourceiv = (LPALSOURCEIV)GetOpenALProcAddress("alSourceiv");
		alGetSourcef = (LPALGETSOURCEF)GetOpenALProcAddress("alGetSourcef");
		alGetSource3f = (LPALGETSOURCE3F)GetOpenALProcAddress("alGetSource3f");
		alGetSourcefv = (LPALGETSOURCEFV)GetOpenALProcAddress("alGetSourcefv");
		alGetSourcei = (LPALGETSOURCEI)GetOpenALProcAddress("alGetSourcei");
		alGetSource3i = (LPALGETSOURCE3I)GetOpenALProcAddress("alGetSource3i");
		alGetSourceiv = (LPALGETSOURCEIV)GetOpenALProcAddress("alGetSourceiv");
		alSourcePlayv = (LPALSOURCEPLAYV)GetOpenALProcAddress("alSourcePlayv");
		alSourceStopv = (LPALSOURCESTOPV)GetOpenALProcAddress("alSourceStopv");
		alSourceRewindv = (LPALSOURCEREWINDV)GetOpenALProcAddress("alSourceRewindv");
		alSourcePausev = (LPALSOURCEPAUSEV)GetOpenALProcAddress("alSourcePausev");
		alSourcePlay = (LPALSOURCEPLAY)GetOpenALProcAddress("alSourcePlay");
		alSourceStop = (LPALSOURCESTOP)GetOpenALProcAddress("alSourceStop");
		alSourceRewind = (LPALSOURCEREWIND)GetOpenALProcAddress("alSourceRewind");
		alSourcePause = (LPALSOURCEPAUSE)GetOpenALProcAddress("alSourcePause");
		alSourceQueueBuffers = (LPALSOURCEQUEUEBUFFERS)GetOpenALProcAddress("alSourceQueueBuffers");
		alSourceUnqueueBuffers = (LPALSOURCEUNQUEUEBUFFERS)GetOpenALProcAddress("alSourceUnqueueBuffers");
		alGenBuffers = (LPALGENBUFFERS)GetOpenALProcAddress("alGenBuffers");
		alDeleteBuffers = (LPALDELETEBUFFERS)GetOpenALProcAddress("alDeleteBuffers");
		alIsBuffer = (LPALISBUFFER)GetOpenALProcAddress("alIsBuffer");
		alBufferData = (LPALBUFFERDATA)GetOpenALProcAddress("alBufferData");
		alBufferf = (LPALBUFFERF)GetOpenALProcAddress("alBufferf");
		alBuffer3f = (LPALBUFFER3F)GetOpenALProcAddress("alBuffer3f");
		alBufferfv = (LPALBUFFERFV)GetOpenALProcAddress("alBufferfv");
		alBufferi = (LPALBUFFERI)GetOpenALProcAddress("alBufferi");
		alBuffer3i = (LPALBUFFER3I)GetOpenALProcAddress("alBuffer3i");
		alBufferiv = (LPALBUFFERIV)GetOpenALProcAddress("alBufferiv");
		alGetBufferf = (LPALGETBUFFERF)GetOpenALProcAddress("alGetBufferf");
		alGetBuffer3f = (LPALGETBUFFER3F)GetOpenALProcAddress("alGetBuffer3f");
		alGetBufferfv = (LPALGETBUFFERFV)GetOpenALProcAddress("alGetBufferfv");
		alGetBufferi = (LPALGETBUFFERI)GetOpenALProcAddress("alGetBufferi");
		alGetBuffer3i = (LPALGETBUFFER3I)GetOpenALProcAddress("alGetBuffer3i");
		alGetBufferiv = (LPALGETBUFFERIV)GetOpenALProcAddress("alGetBufferiv");
		alDopplerFactor = (LPALDOPPLERFACTOR)GetOpenALProcAddress("alDopplerFactor");
		alDopplerVelocity = (LPALDOPPLERVELOCITY)GetOpenALProcAddress("alDopplerVelocity");
		alSpeedOfSound = (LPALSPEEDOFSOUND)GetOpenALProcAddress("alSpeedOfSound");
		alDistanceModel = (LPALDISTANCEMODEL)GetOpenALProcAddress("alDistanceModel");

		alcCreateContext = (LPALCCREATECONTEXT)GetOpenALProcAddress("alcCreateContext");
		alcMakeContextCurrent = (LPALCMAKECONTEXTCURRENT)GetOpenALProcAddress("alcMakeContextCurrent");
		alcProcessContext = (LPALCPROCESSCONTEXT)GetOpenALProcAddress("alcProcessContext");
		alcSuspendContext = (LPALCSUSPENDCONTEXT)GetOpenALProcAddress("alcSuspendContext");
		alcDestroyContext = (LPALCDESTROYCONTEXT)GetOpenALProcAddress("alcDestroyContext");
		alcGetCurrentContext = (LPALCGETCURRENTCONTEXT)GetOpenALProcAddress("alcGetCurrentContext");
		alcGetContextsDevice = (LPALCGETCONTEXTSDEVICE)GetOpenALProcAddress("alcGetContextsDevice");
		alcOpenDevice = (LPALCOPENDEVICE)GetOpenALProcAddress("alcOpenDevice");
		alcCloseDevice = (LPALCCLOSEDEVICE)GetOpenALProcAddress("alcCloseDevice");
		alcGetError = (LPALCGETERROR)GetOpenALProcAddress("alcGetError");
		alcIsExtensionPresent = (LPALCISEXTENSIONPRESENT)GetOpenALProcAddress("alcIsExtensionPresent");
		alcGetProcAddress = (LPALCGETPROCADDRESS)GetOpenALProcAddress("alcGetProcAddress");
		alcGetEnumValue = (LPALCGETENUMVALUE)GetOpenALProcAddress("alcGetEnumValue");
		alcGetString = (LPALCGETSTRING)GetOpenALProcAddress("alcGetString");
		alcGetIntegerv = (LPALCGETINTEGERV)GetOpenALProcAddress("alcGetIntegerv");
		alcCaptureOpenDevice = (LPALCCAPTUREOPENDEVICE)GetOpenALProcAddress("alcCaptureOpenDevice");
		alcCaptureCloseDevice = (LPALCCAPTURECLOSEDEVICE)GetOpenALProcAddress("alcCaptureCloseDevice");
		alcCaptureStart = (LPALCCAPTURESTART)GetOpenALProcAddress("alcCaptureStart");
		alcCaptureStop = (LPALCCAPTURESTOP)GetOpenALProcAddress("alcCaptureStop");
		alcCaptureSamples = (LPALCCAPTURESAMPLES)GetOpenALProcAddress("alcCaptureSamples");

		return true;
	}

	bool InitOpenAL()
	{
		InitFunctionPointers();

		g_device = alcOpenDevice(NULL);
		if (g_device)
		{
			g_context = alcCreateContext(g_device, NULL);
			alcMakeContextCurrent(g_context);
		}
		else
			return false;
		return true;
	}

	bool Init()
	{
		if (!InitOpenAL())
			return false;
		return true;
	}

	bool Destroy()
	{
		if (!DestroyOpenAL())
			return false;
		return true;
	}
}

#endif // USE_OPENAL
