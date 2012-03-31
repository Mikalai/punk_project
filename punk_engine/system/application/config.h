#ifndef _H_PUNK_APPLICATION_CONFIG
#define _H_PUNK_APPLICATION_CONFIG

#ifdef _WIN32
#ifdef PUNK_APPLICATION_EXPORTS
#define LIB_APPLICATION __declspec(dllexport)
#else
#define LIB_APPLICATION __declspec(dllimport)
#endif

#pragma warning(disable : 4251)

#endif

#ifdef __linux__
#define MODULE_SYSTEM
#endif

#endif