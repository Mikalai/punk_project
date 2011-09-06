#ifndef _H_PUNK_SYSTEM_CONFIG
#define _H_PUNK_SYSTEM_CONFIG

#ifdef _WIN32
#ifdef PUNK_SYSTEM_EXPORTS
#define LIB_SYSTEM __declspec(dllexport)
#else
#define LIB_SYSTEM __declspec(dllimport)
#endif

#pragma warning(disable : 4251)

#endif

#ifdef __linux__
#define LIB_SYSTEM
#endif

#endif