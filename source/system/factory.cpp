#include "logger.h"
#include "factory.h"
#include "../utility/utility.h"
#include "../math/vec2.h"
#include "../math/vec3.h"
#include "../math/vec4.h"
#include "../math/mat2.h"
#include "../math/mat3.h"
#include "../math/mat4.h"
#include "../math/bounding_box.h"
#include "../string/string.h"
#include "../system/buffer.h"
#include "../system/logger.h"
#include "../system/binary_file.h"
#include "compound_object.h"

namespace System
{
	Factory* m_instance;

	PUNK_ENGINE Factory* GetFactory()
	{
		if (!m_instance)
			m_instance = new Factory();
		return m_instance;
	}

	Factory::~Factory()
	{
		out_message() << "Factory destroyed" << std::endl;
	}

	bool Factory::RegisterCreator(ObjectType type, ResourceCreator* creator)
	{
		auto it = m_creator.find(type);
		if (it != m_creator.end())
			return (out_warning() << "Can't register second creator for the same type " << System::AsString(type).Data() << ". Unregister first" << std::endl, false);
		m_creator[type] = creator;

		return (out_message() << L"Creator for " << System::AsString(type).Data() << L" was registered" << std::endl, true);
	}

	bool Factory::UnregisterCreator(ObjectType type)
	{
		auto it = m_creator.find(type);
		if (it == m_creator.end())
			return (out_error() << "Can't unregister creator for type " << type << std::endl, false);
		m_creator.erase(it);
		return true;
	}

	Proxy<Object> Factory::Create(ObjectType type)
	{
		auto it = m_creator.find(type);
		if (it == m_creator.end())
			return (out_error() << "Can't create object because creator for " << AsString(type) << " was not registered" << std::endl, Proxy<Object>(nullptr));

		return it->second->Create();
	}

	Proxy<Object> Factory::Create(const string& name, ObjectType type)
	{
		auto it = m_creator.find(type);
		if (it == m_creator.end())
			return (out_error() << "Can't create object because creator for " << AsString(type) << " was not registered" << std::endl, Proxy<Object>(nullptr));

		return it->second->Create(name);
	}

	bool Factory::SaveToStream(std::ostream& stream, Proxy<Object> o)
	{
		bool flag = o->IsModified();
		stream.write((char*)&flag, sizeof(flag));
		ObjectType type = o->GetType();
		stream.write((char*)&type, sizeof(type));
		if (flag)
		{
			if (!o->Save(stream))
				return (out_error() << "Can't save object by the factory" << std::endl, false);
		}
		else
		{
			if (!o->GetStorageName().Save(stream))
				return (out_error() << "Can't save reference to the object" << std::endl, false);
		}
		return true;
	}

	Proxy<Object> Factory::LoadFromStream(std::istream& stream)
	{
		bool flag = false;
		ObjectType type = ObjectType::RESOURCE_NONE;
		stream.read((char*)&flag, sizeof(flag));			
		stream.read((char*)&type, sizeof(type));
		if (flag)
		{
			System::Proxy<Object> o = GetFactory()->Create(type);
			if (!o->Load(stream))
				return (out_error() << "Can't load compound object" << std::endl, System::Proxy<Object>(nullptr));
			return o;
		}
		else
		{
			System::string storage;
			storage.Load(stream);
			System::Proxy<Object> o = GetFactory()->Create(storage, type);
			return o;
		}		
	}

	//Factory* GetFactory()
	//{
	//	if (!m_instance.get())
	//		m_instance.reset(new Factory);
	//	return m_instance.get();
	//}

	//void Factory::Destroy()
	//{
	//	m_instance.reset(nullptr);
	//}
	
	Proxy<Object> Factory::CreateFromTextFile(const string& path)
	{		
		return Utility::LoadWorld(path);
	}

}
