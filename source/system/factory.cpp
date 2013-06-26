#include "logger.h"
#include "factory.h"
#include "../utility/module.h"
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

	PUNK_ENGINE_API Factory* GetFactory()
	{
		if (!m_instance)
			m_instance = new Factory();
		return m_instance;
	}

	Factory::~Factory()
	{
	}

	bool Factory::Init()
	{
		for (auto creator : m_creator)
		{
			creator.second->Init();
		}
		return true;
	}

	bool Factory::RegisterCreator(ObjectType type, ResourceCreator* creator)
	{
		auto it = m_creator.find(type);
		if (it != m_creator.end())
			throw System::PunkInvalidArgumentException(L"Can't register second creator for the same type " + AsString(type) + L". Unregister first");
		m_creator[type] = creator;

		return true;
	}

	bool Factory::UnregisterCreator(ObjectType type)
	{
		auto it = m_creator.find(type);
		if (it == m_creator.end())
			throw System::PunkInvalidArgumentException(L"Can't unregister creator for type " + AsString(type));
		m_creator.erase(it);
		return true;
	}

	Object* Factory::Create(ObjectType type)
	{
		auto it = m_creator.find(type);
		if (it == m_creator.end())
			throw System::PunkInvalidArgumentException(L"Can't create object because creator for " + AsString(type) + L" was not registered");
		return it->second->Create();
	}

	Object* Factory::Create(const string& name, ObjectType type)
	{
		auto it = m_creator.find(type);
		if (it == m_creator.end())
			throw System::PunkInvalidArgumentException(L"Can't create object because creator for " + AsString(type) + L" was not registered");

		return it->second->Create(name);
	}

	bool Factory::SaveToStream(std::ostream& stream, Object* o)
	{
		bool flag = o->IsModified();
		stream.write((char*)&flag, sizeof(flag));
		ObjectType type = o->GetType();
		stream.write((char*)&type, sizeof(type));
		if (flag)
		{
			o->Save(stream);
		}
		else
		{
			o->GetStorageName().Save(stream);
		}
		return true;
	}

	Object* Factory::LoadFromStream(std::istream& stream)
	{
		bool flag = false;
		ObjectType type = ObjectType::RESOURCE_NONE;
		stream.read((char*)&flag, sizeof(flag));
		stream.read((char*)&type, sizeof(type));
		if (flag)
		{
			std::unique_ptr<Object> o(GetFactory()->Create(type));
			o->Load(stream);
			return o.release();
		}
		else
		{
			System::string storage;
			storage.Load(stream);
			Object* o = GetFactory()->Create(storage, type);
			return o;
		}
	}

	Object* Factory::CreateFromTextFile(const string& path)
	{
        return 0;

//		return Utility::LoadWorld(path);
	}

}
