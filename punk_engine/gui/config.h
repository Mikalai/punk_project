#ifndef _H_PUNK_GUI_CONFIG
#define _H_PUNK_GUI_CONFIG

#ifdef _WIN32
#ifdef PUNK_GUI_EXPORTS
#define LIB_GUI __declspec(dllexport)
#else
#define LIB_GUI __declspec(dllimport)
#endif
#endif

#ifdef __linux__
#endif

#endif