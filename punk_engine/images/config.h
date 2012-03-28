#ifndef _H_PUNK_IMAGE_CONFIG
#define _H_PUNK_IMAGE_CONFIG

#ifdef _WIN32
#ifdef PUNK_IMAGE_EXPORTS
#define MODULE_IMAGE __declspec(dllexport)
#else
#define MODULE_IMAGE __declspec(dllimport)
#endif
#endif

#ifdef __linux__
#endif

#endif