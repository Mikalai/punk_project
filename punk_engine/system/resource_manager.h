#ifndef _H_RESOURCE_MANAGER
#define _H_RESOURCE_MANAGER

#include <vector>
#include "resource.h"

namespace System
{

	template<class T>
	class ResourceManager
	{	
		std::vector<Resource<T>> m_resources;
	public:

		__int64 ManageResource(Resource<T> r)
		{
			m_resources.push_back(r);
			return m_resources.size() - 1;
		}

		void ReleaseResource(__int64 code)
		{
			m_resources[code].Clean();
			m_resources.erase(m_resources.begin() + code);
		}

		Resource<T>& operator [] (__int64 code)
		{
			return m_resources[code];
		}

		const Resource<T>* operator [] (__int64 code) const
		{
			return m_resources[code];
		}

		void PackResources()
		{
			for each (Resource<T> r in m_resources)
			{
				if (r.WasAccessedLately())
					r.Unload();
			}
		}

		~ResourceManager()
		{
			for each (Resource<T> r in m_resources)
			{
				r.Clean();
			}
		}
	};
}

#endif