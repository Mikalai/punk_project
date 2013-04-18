#ifndef _H_PUNK_ENGINE_CONFIG
#define _H_PUNK_ENGINE_CONFIG

#ifdef _WIN32
#ifdef PUNK_ENGINE_EXPORTS
#define PUNK_ENGINE __declspec(dllexport)
#else
#define PUNK_ENGINE __declspec(dllimport)
#endif
#endif

#ifdef __linux__
#endif

#endif	//	_H_PUNK_IMAGE_CONFIG
