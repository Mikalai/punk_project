#ifndef _H_PUNK_SYSTEM_STORABLE_DATA
#define _H_PUNK_SYSTEM_STORABLE_DATA

#include <iosfwd>

namespace System
{
	class StorableData
	{
	public:
		virtual void Save(std::ostream& stream) = 0;
		virtual void Load(std::istream& stream) = 0;
	};
}

#endif	//	_H_PUNK_SYSTEM_STORABLE_DATA