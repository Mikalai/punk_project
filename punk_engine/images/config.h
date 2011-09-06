#ifndef _H_PUNK_IMAGE_CONFIG
#define _H_PUNK_IMAGE_CONFIG

#ifdef _WIN32
#ifdef PUNK_IMAGE_EXPORTS
#define LIB_IMAGE __declspec(dllexport)
#else
#define LIB_IMAGE __declspec(dllimport)
#endif
#endif

#ifdef __linux__
#endif

#endif