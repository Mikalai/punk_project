#ifndef _H_PUNK_UTILITY_CONFIG
#define _H_PUNK_UTILITY_CONFIG

#ifdef PUNK_UTILITY_EXPORTS
#define LIB_UTILITY __declspec(dllexport)
#else
#define LIB_UTILITY __declspec(dllimport)
#endif

#ifdef _WIN32

#ifdef PUNK_UTILITY_EXPORTS
#define LIB_UTILITY __declspec(dllexport)
#else
#define LIB_UTILITY __declspec(dllimport)
#endif

#endif

#ifdef __linux__
#endif

#endif