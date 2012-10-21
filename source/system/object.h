#ifndef _H_PUNK_SYSTEM_OBJECT
#define _H_PUNK_SYSTEM_OBJECT

#include "../config.h"
#include "hresource.h"
#include "../string/string.h"

namespace System
{
	class PUNK_ENGINE Object
	{
		System::string m_storage_name;
		union
		{
			struct
			{				
				ObjectType m_type;				
				unsigned m_id;
			};
			unsigned __int64 m_code;
		};

	public:
		Object() {}

		const System::string& GetStorageName() const { return m_storage_name; }
		void SetStorageName(const System::string& name) { m_storage_name = name; }

		ObjectType GetType() const { return m_type; }
		void SetType(ObjectType type) { m_type = type; }

		virtual bool Save(std::ostream& stream);
		virtual bool Load(std::istream& stream);
	};
}

#endif	//	_H_PUNK_SYSTEM_OBJECT