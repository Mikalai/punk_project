#ifndef _H_PUNK_SYSTEM_OBJECT
#define _H_PUNK_SYSTEM_OBJECT

#include "../config.h"
#include "hresource.h"
#include "../string/string.h"
#include "smart_pointers/proxy.h"

namespace System
{
	class PUNK_ENGINE Object
	{
	public:
		Object() {}
		virtual ~Object() {}

		void SetName(const string& value) { m_name = value; }
		const string& GetName() const { return m_name; }

		void SetText(const string& value) { m_text = value; }
		const string& GetText() const { return m_text; }

		void SetOwner(Proxy<Object> owner) { m_owner = owner; }
		const Proxy<Object> GetOwner() const { return m_owner; }
		Proxy<Object> GetOwner() { return m_owner; }

		const System::string& GetStorageName() const { return m_storage_name; }
		void SetStorageName(const System::string& name) { m_storage_name = name; }

		ObjectType GetType() const { return m_type; }
		void SetType(ObjectType type) { m_type = type; }

		bool IsModified() const { return m_modified; }
		void Invalidate() { m_modified = true; }

		virtual bool Save(std::ostream& stream) const;
		virtual bool Load(std::istream& stream);

	private:

		/**
		*	If object if modified than it should be saved in the save file as
		*	a whole set. If object is not modified than only a storage name
		*	can be saved
		*/
		bool m_modified;
		ObjectType m_type;
		string m_storage_name;
		string m_name;
		string m_text;
		Proxy<Object> m_owner;		
	};
}

#endif	//	_H_PUNK_SYSTEM_OBJECT