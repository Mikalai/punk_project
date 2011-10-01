#ifndef _H_PUNK_SCENE_CONFIG
#define _H_PUNK_SCENE_CONFIG

#ifdef _WIN32
#ifdef PUNK_SCENE_EXPORTS
#define LIB_SCENE __declspec(dllexport)
#else
#define LIB_SCENE __declspec(dllimport)
#endif
#endif

#ifdef __linux__
#endif

#endif