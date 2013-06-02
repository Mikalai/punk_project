#ifndef _H_PUNK_PHYSICS_EXCEPTIONS
#define _H_PUNK_PHYSICS_EXCEPTIONS

#include "../../system/errors/module.h"

namespace Physics
{
	class PUNK_ENGINE_API PunkPhysicsException : public System::PunkException
	{
	public:
		PunkPhysicsException() : PunkException(L"PunkPhysicsException") {}
		PunkPhysicsException(const System::string& msg) : PunkException(L"PunkPhysicsException: " + msg) {}
	};
}

#endif	//	_H_PUNK_PHYSICS_EXCEPTIONS