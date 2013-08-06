#ifdef _WIN32
#ifndef _H_PUNK_ERROR_WIN32
#define _H_PUNK_ERROR_WIN32

#ifndef NOMINMAX
#define NOMINMAX
#endif // NOMINMAX

#include <Windows.h>
#include "../../config.h"
#include "../../string/string.h"

namespace System
{
#ifdef _DEBUG
	extern PUNK_ENGINE_API void CheckOSError(const System::string& msg);
	extern PUNK_ENGINE_API void CheckOSError(LONG code, const System::string& msg);
#define CHECK_SYS_ERROR(X) CheckOSError(X);
#define CHECK_SYS_ERROR_CODE(CODE, X) CheckOSError(CODE, X)
#else
#define CHECK_SYS_ERROR(X)
#define CHECK_SYS_ERROR_CODE(CODE, X)
#endif	//	_DEBUG

}

#endif	//	_H_PUNK_ERROR_WIN32
#endif	//	_WIN32
