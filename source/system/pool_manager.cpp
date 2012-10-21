#include "pool_manager.h"

namespace System
{
	void PoolManager::AddCleaner(PoolManager::CleanFunc func)
	{
		m_cleaners.push_back(func);
	}

	PoolManager::~PoolManager()
	{
		for (std::vector<CleanFunc>::iterator it = m_cleaners.begin(); it != m_cleaners.end(); ++it)
		{
			(*it)();
		}
	}

	PoolManager* PoolManager::Instance() 
	{
		if (!m_instance.get())
			m_instance.reset(new PoolManager);
		return m_instance.get();
	}

	void PoolManager::Destroy()
	{
		m_instance.reset(0);
	}

	std::auto_ptr<PoolManager> PoolManager::m_instance;
}
