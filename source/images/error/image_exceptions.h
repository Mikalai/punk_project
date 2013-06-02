#ifndef _H_PUNK_IMAGE_EXCEPTIONS
#define _H_PUNK_IMAGE_EXCEPTIONS

#include "../../system/errors/module.h"

namespace ImageModule
{
	class PUNK_ENGINE_API ImageException : public System::PunkException
	{
	public:
		ImageException() : System::PunkException(L"ImageException") {}
		ImageException(const System::string& msg) : System::PunkException(L"ImageException: " + msg) {}
	};
}

#endif	//	_H_PUNK_IMAGE_EXCEPTIONS