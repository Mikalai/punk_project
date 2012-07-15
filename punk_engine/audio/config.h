#ifndef _H_PUNK_AUDIO_CONFIG
#define _H_PUNK_AUDIO_CONFIG

#ifdef PUNK_AUDIO_EXPORTS
#define PUNK_AUDIO_MODULE __declspec(dllexport)
#else
#define PUNK_AUDIO_MODULE __declspec(dllimport)
#endif

#endif	//	_H_PUNK_AUDIO_CONFIG
