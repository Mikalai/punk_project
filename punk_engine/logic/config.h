#ifndef _H_PUNK_LOGIC_CONFIG
#define _H_PUNK_LOGIC_CONFIG

#ifdef PUNK_LOGIC_EXPORTS
#define PUNK_LOGIC_MODULE __declspec(dllexport)
#else
#define PUNK_LOGIC_EXPORTS __declspec(dllimport)
#endif

#endif