#ifndef _H_PUNK_SYSTEM_ASSERT
#define _H_PUNK_SYSTEM_ASSERT

#include "../../config.h"
#include "../../string/string.h"

namespace System
{
	//	Redefinition of assertion function with smart stack tracer
#ifdef _DEBUG
	PUNK_ENGINE_PUBLIC int CustomAssertFunction(bool exp, const string&, char* func, int line, char* file);

#define Assert(exp, description) \
	{	static bool ignore_other = false;	\
	if (!ignore_other)	\
	{	\
	int result = CustomAssertFunction((int)(exp), description, __FUNCSIG__, __LINE__, __FILE__); \
	switch (result)\
	{\
	case IDABORT:\
	{ _asm { int 3 } }	\
	case IDIGNORE:	\
	ignore_other = true; break;	\
	}	\
	}\
	}	

#else
	//	no assertion in release mode
#define Assert(exp, description)
#endif

}

#endif	//	_H_PUNK_SYSTEM_ASSERT