#include <algorithm>
#include "resource_manager.h"

//__int64 ResourceManager::ManageResource(Resource* r)
//{
//	m_resources.push_back(r);
//	return (__int64)(m_resources.size() - 1);
//}
//
//void ResourceManager::ReleaseResource(Resource* r)
//{
//	auto it = std::find(m_resources.begin(), m_resources.end(), r);
//	if (it != m_resources.end())
//		m_resources.erase(it);
//}
//
//void ResourceManager::ReleaseResource(__int64 code)
//{
//	if (code >= m_resources.size())
//		return;
//	m_resources.erase(m_resources.begin() + code);
//}
//
//Resource* ResourceManager::operator[] (__int64 code)
//{
//	return m_resources[code];
//}
//
//const Resource* ResourceManager::operator[] (__int64 code) const
//{
//	return m_resources[code];
//}
//
//void ResourceManager::PackResources()
//{
//	for each (Resource* var in m_resources)
//	{
//		if (!var->WasAccessedLately())
//			var->Unload();
//	}
//}
