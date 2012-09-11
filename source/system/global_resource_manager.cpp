#include "global_resource_manager.h"
#include "abstract_manager.h"
#include "logger.h"

namespace System
{
	std::auto_ptr<GlobalManager> GlobalManager::m_instance;

	GlobalManager* GlobalManager::Instance()
	{
		if (!m_instance.get())
			m_instance.reset(new GlobalManager);
		return m_instance.get();
	}

	void GlobalManager::Destroy()
	{
		m_instance.reset(0);
	}

	bool GlobalManager::RegisterManager(AbstractManager* manager)
	{
		auto it = m_managers.find(manager->GetResourceType());
		if (it != m_managers.end())
		{
			out_warning() << L"Resource manager for resource type " << manager->GetResourceType() << L" already registered. Won't register new manager for this code." << std::endl;
			return false;
		}
		m_managers[manager->GetResourceType()] = manager;
		return true;
	}

	bool GlobalManager::UnregisterManager(AbstractManager* manager)
	{
		auto it = m_managers.find(manager->GetResourceType());
		if (it == m_managers.end())
		{
			out_warning() << "Can't unregister manager with resource type " << manager->GetResourceType() << L" becaouse it was not registered." << std::endl;
			return false;
		}
		return true;
	}

	HResource GlobalManager::Load(int type, const string& name)
	{
		auto it = m_managers.find(type);
		if (it == m_managers.end())
		{
			out_error() << "Can't load " << name << L", because resource manager with type " << type << L" was not registered. " << std::endl;
			return HResource();
		}

		AbstractManager* manager = it->second;

		if (!manager)
		{
			out_error() << "Resource manager for type " << type << L" is corrupted" << std::endl;
			return HResource();
		}

		return manager->Load(name);
	}

	AbstractManager* GlobalManager::FindManager(int type)
	{
		auto it = m_managers.find(type);

		if (it == m_managers.end())
			return 0;

		return it->second;
	}
}
