#ifndef _H_PUNK_SYSTEM_FACTORY
#define _H_PUNK_SYSTEM_FACTORY

#include <map>
#include "../config.h"
#include "hresource.h"
#include "resource_creator.h"

namespace System
{
	class PUNK_ENGINE Factory
	{
	public:
		
		bool RegisterCreator(ObjectType type, ResourceCreator* creator);
		bool UnregisterCreator(ObjectType type);
		Proxy<Object> Create(ObjectType type);
		Proxy<Object> Create(const string& name, ObjectType type);

		Proxy<Object> CreateFromTextFile(const string& path);

		bool SaveToStream(std::ostream& stream, Proxy<Object> object);
		Proxy<Object> LoadFromStream(std::istream& stream);

		static Factory* Instance();
		static void Destroy();

	private:
		static std::auto_ptr<Factory> m_instance;
		std::map<ObjectType, ResourceCreator*> m_creator;
	};
}

#endif	//	_H_PUNK_SYSTEM_FACTORY