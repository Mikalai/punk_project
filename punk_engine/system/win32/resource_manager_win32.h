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
		typedef std::map<Descriptor, BaseResource* > ResourceCollection;
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

		Descriptor AllocateResource()
		{
			T* res = new T();
			res->SetHandle(Descriptor(U, m_instance_id));
			m_instance_id++;
			m_resources[res->GetHandle()] = res;
			return res->GetHandle();
		}

		//! Starts controlling manager created somewhere
		Descriptor ManageResource(BaseResource* res)
		{
			res->SetHandle(Descriptor(U, m_instance_id++));
			m_resources[res->GetHandle()] = res;
			return res->GetHandle();
		}

		T* GetResource(Descriptor h)
		{
			T* res = static_cast<T*>(m_resources.at(h));
			return res;
		}



		/*! Manual dropping selected resource to hdd */
		void DropResourceToHdd(Descriptor h)
		{
			T* res = GetResource(h);
			res->DropToHdd();
		}

		/*! Restore resource from hdd */
		void RestoreResourceFromHdd(Descriptor h)
		{
			T* res = GetResource(h);
			res->RestoreFromHdd();
		}

		/*! This will completely destroy resource. It will not be able to restore it any moder */
		void DestroyResource(Descriptor h)
		{
			m_resources.erase(h);
		}
		
		/*! This will drop all unused items to hdd */
		void OptimizeMemoryUsage()
		{
			time_t now;
			time(&now);
			for (ResourceCollection::iterator i = m_resources.begin(); i != m_resources.end(); ++i)
			{
				T* res = static_cast<T*>((*i).second);
				if (difftime(now, res->GetLastTimeAccess()) > m_gc_time)
				{
					res->DropToHdd();
				}
			}
		}

		void SetGCTime(unsigned time_s)
		{
			m_gc_time = time_s;
		}

		unsigned GetGCTime() const
		{
			return m_gc_time;
		}
	};

	template<class T, unsigned U>
	unsigned ResourceManager<T, U>::m_instance_id = 1;
}

#endif