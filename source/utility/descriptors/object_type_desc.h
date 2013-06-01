#ifndef _H_PUNK_VIRTUAL_OBJECT_TYPE_DESC
#define _H_PUNK_VIRTUAL_OBJECT_TYPE_DESC

#include "../../config.h"

namespace System
{
	class string;
}

namespace Utility
{
	class PUNK_ENGINE_PUBLIC ObjectTypeDesc
	{
	public:
		bool BuildFromString(const System::string& value);
	};
}

#endif	//	_H_PUNK_VIRTUAL_OBJECT_TYPE_DESC