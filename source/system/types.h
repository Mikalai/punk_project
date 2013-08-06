#ifndef _H_PUNK_SYSTEM_TYPES
#define _H_PUNK_SYSTEM_TYPES

#include "handler.h"
#include "atomicint.h"

namespace System
{
	typedef signed char Int8;
	typedef unsigned char UInt8;
	typedef signed short int Int16;
	typedef unsigned short int UInt16;
	typedef signed int Int32;
	typedef unsigned int UInt32;

#ifdef _WIN32
	typedef signed __int64 Int64;
	typedef unsigned __int64 UInt64;
#endif	//	_WIN32
}

#endif // _H_PUNK_SYSTEM_TYPES
