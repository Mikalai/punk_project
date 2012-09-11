#ifndef _H_PUNK_SYSTEM_ABSTRACT_MANAGER
#define _H_PUNK_SYSTEM_ABSTRACT_MANAGER

#include "../string/string.h"
#include "hresource.h"

namespace System
{
	class PermanentData;

	class AbstractManager
	{
	public:
		virtual int GetResourceType() const = 0;
		virtual HResource Load(const string& name) = 0;
		virtual PermanentData* Get(int index) = 0;
	};
}

#endif	//	_H_PUNK_SYSTEM_ABSTRACT_MANAGER