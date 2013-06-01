#ifndef _H_PUNK_SYSTEM_FACTORY
#define _H_PUNK_SYSTEM_FACTORY

#include <map>
#include "../config.h"
#include "hresource.h"
#include "resource_creator.h"

namespace System
{
	class PUNK_ENGINE_PUBLIC Factory
	{
	public:
		
		~Factory();

		bool Init();
		bool RegisterCreator(ObjectType type, ResourceCreator* creator);
		bool UnregisterCreator(ObjectType type);
		Object* Create(ObjectType type);
		Object* Create(const string& name, ObjectType type);

		Object* CreateFromTextFile(const string& path);

		bool SaveToStream(std::ostream& stream, Object* object);
		Object* LoadFromStream(std::istream& stream);

	///	static Factory* Instance();
	///	static void Destroy();

	private:		
		std::map<ObjectType, ResourceCreator*> m_creator;
	};

	PUNK_ENGINE_PUBLIC Factory* GetFactory();
}

#endif	//	_H_PUNK_SYSTEM_FACTORY