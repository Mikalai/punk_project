#ifndef _H_PUNK_RESOURCE_MANAGER_WIN32
#define _H_PUNK_RESOURCE_MANAGER_WIN32

#include <map>
#include <algorithm>
#include "../singletone.h"
#include "window_win32.h"
#include "../error.h"
#include "config_file_win32.h"
#include "resource_win32.h"

//
//	LIST OF ALL RESOURCES
//

namespace OpenGL
{
	class Texture2D;
	class TextTexture2D;
}

namespace GUI
{
	class Widget;
	class Button;
}

namespace System
{
	class ResourceManager;

	class MODULE_SYSTEM RecourceManager
	{
		class ResourceManagerImpl;
		std::auto_ptr<ResourceManagerImpl> impl_rm;
		static std::auto_ptr<ResourceManager> m_instance;
	public:
		
		Resource* GetResource(const Descriptor& desc);
		const Resource* GetResource(const Descriptor& desc) const;

		void Save(Buffer& buffer) const;
		void Load(Buffer& buffer);

		static ResourceManager* Instance();
		static void Destroy();

	};
}

///*	SingletoneInterface(ResourceManager, MODULE_SYSTEM);
//
//	/*!
//		This class is going to be used to manipulate resources. The idea
//		is to create such way of resource controlling that it will be 
//		easy to store, restore game state at any place
//	*/
///*	class MODULE_SYSTEM ResourceManager : public Singletone(ResourceManager)
//	{
//		typedef unsigned Type;
//		typedef unsigned Number;
//		typedef std::map<Number, BaseResource*> OneTypeResourceCollection;
//		static unsigned m_instance_id;		
//		typedef std::map<Type, OneTypeResourceCollection> ResourceCollection;
//		ResourceCollection m_resources;
//	
//		ResourceManager& operator = (const ResourceManager&);
//		ResourceManager(const ResourceManager&);
//
//		unsigned m_gc_time;
//
//		BaseResource* get_resource(Descriptor desc)
//		{
//			if (desc == Descriptor::Root())
//				return 0;
//			return m_resources.at(desc.Type()).at(desc.Number());
//		}
//
//	public:
//
//		ResourceManager()
//		{
//			ConfigFile conf;
//			conf.Open(Window::GetInstance()->GetTitle());
//			if (!conf.IsExistOption(L"gc_time"))
//				conf.WriteOptionInt(L"gc_time", 60);
//
//			m_gc_time = (unsigned)conf.ReadOptionInt(L"gc_time");
//			conf.Close();
//		}
//
//		~ResourceManager()
//		{
//			for (ResourceCollection::iterator i = m_resources.begin(); i != m_resources.end(); ++i)
//				for (OneTypeResourceCollection::iterator j = (*i).second.begin(); j != (*i).second.end(); j++)
//					delete (*j).second;
//			m_resources.clear();
//		}
//
//		template<class T>
//		Descriptor AllocateResource()
//		{
//			T* res = new T();
//			res->SetHandle(Descriptor(U, m_instance_id));
//			m_instance_id++;
//			m_resources[res->GetHandle().Type()][res->GetHandle().Number()] = res;
//			return res->GetHandle();
//		}
//
//		//! Starts controlling manager created somewhere
//		template<unsigned U>
//		Descriptor ManageResource(BaseResource* res)
//		{
//			res->SetHandle(Descriptor(U, m_instance_id++));
//			m_resources[res->GetHandle().Type()][res->GetHandle().Number()] = res;
//			return res->GetHandle();
//		}
//
//		template<class T>
//		Resource<T>* GetResource(Descriptor h)
//		{
//			Resource<T>* res = static_cast<Resource<T>*>(get_resource(h));
//			res->AddRef();
//			return res;
//		}
//
//		template<unsigned Type>
//		void* Get(Descriptor desc)
//		{
//			throw System::SystemError("Unsupported resource");
//		}
//
//		/*! Manual dropping selected resource to hdd */
//	/*	void DropResourceToHdd(Descriptor h)
//		{
//			BaseResource* res = get_resource(h);
//			res->DropToHdd();
//		}
//
//		/*! Restore resource from hdd */
//
//	/*	void RestoreResourceFromHdd(Descriptor h)
//		{
//			BaseResource* res = get_resource(h);
//			res->RestoreFromHdd();
//		}
//
//		/*! This will completely destroy resource. It will not be able to restore it any moder */
//		void DestroyResource(Descriptor h)
//		{
//			BaseResource* res = get_resource(h);
//			delete res;
//			m_resources.erase(h);
//		}
//		
//		/*! This will drop all unused items to hdd */
//		void OptimizeMemoryUsage()
//		{
//			time_t now;
//			time(&now);
//			for (ResourceCollection::iterator i = m_resources.begin(); i != m_resources.end(); ++i)
//			{
//				for (OneTypeResourceCollection::iterator j = (*i).second.begin(); j != (*i).second.end(); ++j)
//				{
//					BaseResource* res = (*j).second;
//					if (difftime(now, res->GetLastTimeAccess()) > m_gc_time)
//					{
//						if (res->GetRefCount() == 0)
//							res->DropToHdd();
//					}
//				}
//			}
//		}
//
//		void SetGCTime(unsigned time_s)
//		{
//			m_gc_time = time_s;
//		}
//
//		unsigned GetGCTime() const
//		{
//			return m_gc_time;
//		}
//	};	
// }

#endif
