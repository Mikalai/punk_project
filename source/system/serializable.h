#ifndef _H_PUNK_SYSTEM_SERIALIZABLE
#define _H_PUNK_SYSTEM_SERIALIZABLE

#include "../config.h"
#include "string.h"
#include <iosfwd>

namespace System
{
	class Serializable 
	{
	public:
		virtual bool Save(std::ostream& stream) const = 0;
		virtual bool Load(std::istream& stream) = 0;
	};
};

#endif