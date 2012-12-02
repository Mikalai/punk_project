#ifndef _H_PUNK_SYSTEM_STORABLE_DATA
#define _H_PUNK_SYSTEM_STORABLE_DATA

#include <iosfwd>
#include "../config.h"
#include "hresource.h"
#include "../string/string.h"

namespace System
{
	class PUNK_ENGINE StorableData
	{
		System::string m_storage_name;
	public:

		void SetStorageName(const System::string& value) { m_storage_name = value; }
		const System::string GetStorageName() const { return m_storage_name; }

		virtual bool Save(std::ostream& stream) const;
		virtual bool Load(std::istream& stream);

		virtual ~StorableData() {}
	};
}

#endif	//	_H_PUNK_SYSTEM_STORABLE_DATA