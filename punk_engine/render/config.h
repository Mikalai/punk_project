#ifndef _H_PUNK_RENDER_CONFIG
#define _H_PUNK_RENDER_CONFIG

#ifdef _WIN32
#ifdef PUNK_RENDER_EXPORTS
#define LIB_RENDER __declspec(dllexport)
#else
#define LIB_RENDER __declspec(dllimport)
#endif
#endif

#ifdef __linux__
#endif

#endif