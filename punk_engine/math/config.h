#ifndef _H_PUNK_MATH_CONFIG
#define _H_PUNK_MATH_CONFIG

#ifdef _WIN32
#ifdef PUNK_MATH_EXPORTS
#define LIB_MATH __declspec(dllexport)
#else
#define LIB_MATH __declspec(dllimport)
#endif
#endif

#ifdef __linux__
#endif

#endif