#ifndef _H_PUNK_ENGINE_PUBLIC_CONFIG
#define _H_PUNK_ENGINE_PUBLIC_CONFIG

#if defined _WIN32 || defined __CYGWIN__
  #ifdef PUNK_ENGINE_EXPORTS
    #ifdef __GNUC__
      #define PUNK_ENGINE_PUBLIC __attribute__ ((dllexport))
    #else
      #define PUNK_ENGINE_PUBLIC __declspec(dllexport) // Note: actually gcc seems to also supports this syntax.
    #endif
  #else
    #ifdef __GNUC__
      #define PUNK_ENGINE_PUBLIC __attribute__ ((dllimport))
    #else
      #define PUNK_ENGINE_PUBLIC __declspec(dllimport) // Note: actually gcc seems to also supports this syntax.
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

#endif	//	_H_PUNK_IMAGE_CONFIG
