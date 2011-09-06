#ifndef _PUNK_ROOT_OBJECT
#define _PUNK_ROOT_OBJECT

#include "string.h"

namespace System
{
	class Object
	{
	public:
		virtual int GetHashCode();
		virtual string ToString();
	};
}

#endif