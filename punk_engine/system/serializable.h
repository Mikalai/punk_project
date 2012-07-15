#ifndef _H_PUNK_SYSTEM_SERIALIZABLE
#define _H_PUNK_SYSTEM_SERIALIZABLE

#include "config.h"
#include "string.h"
#include <iosfwd>

namespace System
{
	class Serializable 
	{
	public:
		virtual void Save(std::ostream& stream) = 0;
		virtual void Load(std::istream& stream) = 0;
	};
};

#endif