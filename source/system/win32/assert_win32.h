#ifndef _H_PUNK_SYSTEM_ASSERT
#define _H_PUNK_SYSTEM_ASSERT

#include "../../config.h"

//
//	A LITTLE SMARTER ASSERT BEGIN
//	Redefinition of assertion function with smart stack tracer
//
#if defined (_DEBUG)
PUNK_ENGINE int CustomAssertFunction(bool exp, char* description, char* func, int line, char* file);

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
#define Assert(exp, description)
#endif

#endif	//	_H_PUNK_SYSTEM_ASSERT