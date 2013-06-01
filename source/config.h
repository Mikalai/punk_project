#ifndef _H_PUNK_ENGINE_PUBLIC_CONFIG
#define _H_PUNK_ENGINE_PUBLIC_CONFIG

#if defined _WIN32 || defined __CYGWIN__
  #ifdef PUNK_ENGINE_EXPORTS
    #ifdef __GNUC__
      #define PUNK_ENGINE_PUBLIC __attribute__ ((dllexport))
    #else
      #define PUNK_ENGINE_PUBLIC __declspec(dllexport)
    #endif
  #else
    #ifdef __GNUC__
      #define PUNK_ENGINE_PUBLIC __attribute__ ((dllimport))
    #else
      #define PUNK_ENGINE_PUBLIC __declspec(dllimport)
    #endif
  #endif
  #define PUNK_ENGINE_PUBLIC
#else
  #if __GNUC__ >= 4
    #define PUNK_ENGINE_PUBLIC __attribute__ ((visibility ("default")))
    #define PUNK_ENGINE_LOCAL  __attribute__ ((visibility ("hidden")))
  #else
    #define PUNK_ENGINE_PUBLIC
    #define
  #endif
#endif

#ifdef _WIN32
#define PUNK_STDCALL __stdcall
#define PUNK_CDECL __cdecl
#define PUNK_INFINITE INFINITE

#define punk_memcpy(DST, DST_SIZE, SRC, SRC_SIZE) memcpy_s((DST), (DST_SIZE), (SRC), (SRC_SIZE))
#elif defined __linux__
#define PUNK_STDCALL
#define PUNK_CDECL __attribute__((__cdecl__))
#define PUNK_INFINITE ~0u

#define punk_memcpy(DST, DST_SIZE, SRC, SRC_SIZE) memcpy((DST), (SRC), (DST_SIZE))
#endif

#endif	//	_H_PUNK_IMAGE_CONFIG
