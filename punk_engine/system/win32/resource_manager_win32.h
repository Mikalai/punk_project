#ifndef _H_PUNK_RESOURCE_MANAGER_WIN32
#define _H_PUNK_RESOURCE_MANAGER_WIN32

#include <map>
#include <algorithm>
#include "window_win32.h"
#include "../error.h"
#include "config_file_win32.h"
#include "resource_win32.h"

namespace System
{
	/*!
		This class is going to be used to manipulate resources. The idea
		is to create such way of resource controlling that it will be 
		easy to store, restore game state at any place
	*/
	template<class T, unsigned U>
	class ResourceManager
	{
		static unsigned m_instance_id;		
		typedef std::map<Handle, BaseResource* > ResourceCollection;
		ResourceCollection m_resources;
	
		ResourceManager& operator = (const ResourceManager&);
		ResourceManager(const ResourceManager&);

		unsigned m_gc_time;

	public:

		ResourceManager()
		{
			ConfigFile conf;
			conf.Open(Window::GetInstance()->GetTitle());
			if (!conf.IsExistOption(L"gc_time"))
				conf.WriteOptionInt(L"gc_time", 60);

			m_gc_time = (unsigned)conf.ReadOptionInt(L"gc_time");
			conf.Close();
		}

		~ResourceManager()
		{
			for (ResourceCollection::iterator i = m_resources.begin(); i != m_resources.end(); ++i)
				delete (*i).second;
			m_resources.clear();
		}

		Handle AllocateResource()
		{
			T* res = new T();
			res->SetHandle(Handle(U, m_instance_id));
			m_instance_id++;
			m_resources[res->GetHandle()] = res;
			return res->GetHandle();
		}

		//! Starts controlling manager created somewhere
		Handle ManageResource(BaseResource* res)
		{
			res->SetHandle(Handle(U, m_instance_id++));
			m_resources[res->GetHandle()] = res;
			return res->GetHandle();
		}

		T* GetResource(Handle h)
		{
			T* res = static_cast<T*>(m_resources.at(h));
			return res;
		}



		/*! Manual dropping selected resource to hdd */
		void DropResourceToHdd(Handle h)
		{
			T* res = GetResource(h);
			res->DropToHdd();
		}

		/*! Restore resource from hdd */
		void RestoreResourceFromHdd(Handle h)
		{
			T* res = GetResource(h);
			res->RestoreFromHdd();
		}

		/*! This will completely destroy resource. It will not be able to restore it any moder */
		void DestroyResource(Handle h)
		{
			m_resources.erase(h);
		}
		
		/*! This will drop all unused items to hdd */
		void OptimizeMemoryUsage()
		{
			time_t now;
			time(&now);
			for (ResourceCollection::iterator i = m_resources.begin(); i != m_resource.end(); ++i)
			{
				T* res = *i;
				if (difftime(now, res->GetLastTimeAccess()) > m_gc_time)
				{
					res->DropToHdd();
				}
			}
		}
	};

	template<class T, unsigned U>
	unsigned ResourceManager<T, U>::m_instance_id = 1;
}

#endif