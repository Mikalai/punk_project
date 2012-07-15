#ifndef _H_RESOURCE_MANAGER2
#define _H_RESOURCE_MANAGER2

#include <vector>
#include <memory>
#include <fstream>
#include <list>
#include <algorithm>
#include <iterator>
#include <string>

#include "string.h"
#include "folder.h"

#include "logger.h"


namespace System
{
	template<class T> 
	struct Policy
	{
		static const System::string GetResourceFile() { return L"BAD_FILE"; }
		static const System::string GetExtension() { return L"BAD_EXTENSION"; }
		static const System::string GetFolder() { return L"BAD_FILDER"; }
	};

	template<class T, template<class> class Policy> 
	class Resource2
	{
		int m_index;
		System::string m_location;
		std::auto_ptr<T> m_resource;

		Resource2<T, Policy>(const Resource2<T, Policy>&);
		Resource2<T, Policy>& operator = (const Resource2<T, Policy>&);

		void LoadResource()
		{
			m_resource.reset(new T());			
			System::Logger::Instance()->WriteMessage(L"Loading " + Policy<T>::GetFolder() + m_location);
			std::ifstream inp((Policy<T>::GetFolder() + m_location).Data(), std::ios_base::binary);
			m_resource->Load(inp);
			inp.close();
		}

	public:
		Resource2()
			: m_index(-1)
			, m_location(L"/")
		{}

		void Init(int index, const System::string& location)
		{
			m_location = location;
			m_index = index;
		}

		T* Get() 
		{
			if (!m_resource.get())
			{
				LoadResource();
			}
			return m_resource.get();
		}

		void Unload()
		{
			m_resource.reset(0)
		}

		int GetTimeIntervalAccess();

		void Save()
		{
			wchar_t* name = wcsstr(m_location.Data(), L".");
			const System::string file(name + Policy<T>::GetExtension());
			char buf[2048];
			file.ToANSI(buf, 2048);
			std::wofstream out(buf);
			out << m_index << L' ' << m_location.Data() << std::endl;
			out.close();
		}

		void Load(const System::string resource_file)
		{
			std::wifstream inp(file.Data());
			out << m_index << L' ' << m_location.Data() << std::endl;
			out.close();
		}

		const System::string& GetLocation() const { return m_location; }
		int GetIndex() const { return m_index; }
	};

	template<class T, template<class U> class Policy>
	class ResourceManager2
	{
	public:
		typedef std::shared_ptr<Resource2<T, Policy>> ResourcePtr;
		typedef std::vector<ResourcePtr> Collection;
		typedef typename Collection::iterator iterator;
		typedef typename Collection::const_iterator const_iterator;
	private:
		std::list<System::string> ReadResourcFile()
		{
			System::Logger::Instance()->WriteMessage(L"Reading all resources in " + Policy<T>::GetFolder());
			std::list<System::string> already_index;

			System::Folder fld;
			fld.Open(Policy<T>::GetFolder());
			std::wifstream inp(Policy<T>::GetResourceFile().Data());
			if (inp.is_open())
			{
				while (!inp.eof())
				{
					int index;
					wchar_t buf[2048];
					inp >> index;
					inp >> buf;	
					if (wcslen(buf) == 0)
						break;
					already_index.push_back(System::string(buf));
					System::Logger::Instance()->WriteMessage(L"Found resource " + System::string::Convert(index) + L" -> " + buf);
				}
			}
			else
			{
				System::Logger::Instance()->WriteWarning(System::string(L"Resource file ") + Policy<T>::GetResourceFile() + L" was not created in " + Policy<T>::GetFolder() + L" yet. ");
			}
			fld.Close();
			System::Logger::Instance()->WriteMessage(L"Reading resources complete");
			return already_index;
		}

		void UpdateResourceFile(const std::list<System::string>& files)
		{
			int k = 0;
			System::Folder fld;
			fld.Open(Policy<T>::GetFolder());
			std::wofstream out(Policy<T>::GetResourceFile().Data());
			for each(System::string file in files)
			{
				out << k << L' ' << file.Data() << std::endl;
				k++;
			}
			out.close();
			fld.Close();
		}

		void LoadResources()
		{			
			m_items.clear();
			System::Logger::Instance()->WriteMessage(L"Loading resources from " + Policy<T>::GetFolder());
			System::Folder fld;
			fld.Open(Policy<T>::GetFolder());
			std::wifstream inp(Policy<T>::GetResourceFile().Data());
			if (inp.is_open())
			{
				while (!inp.eof())
				{
					int index;
					wchar_t buf[2048];				
					inp >> index;
					if (inp.eof())
						break;
					inp >> buf;
					if (wcslen(buf) == 0)
						break;

					std::shared_ptr<Resource2<T, Policy>> res(new Resource2<T, Policy>);
					res->Init(index, buf);
					//	we should place a resource in specifed by index position
					m_items.resize(std::max((int)m_items.size(), index + 1));
					m_items[index] = res;
					System::Logger::Instance()->WriteMessage(L"Resource " + System::string::Convert(index) + L" " + buf + L" has been cached");
				}							
			}
			else
			{
				System::Logger::Instance()->WriteWarning(L"Resource file '" + Policy<T>::GetResourceFile() + L"' was not found in " + Policy<T>::GetFolder());
			}
			System::Logger::Instance()->WriteMessage(L"Loading resources complete");
			fld.Close();
		}
		
		ResourceManager2<T, Policy>(const ResourceManager2<T, Policy>& );
		ResourceManager2<T, Policy>& operator = (const ResourceManager2<T, Policy>&);

	public:		

		ResourceManager2<T, Policy>()
		{
			Init();
			Policy<T>::OnInit();
		}

		~ResourceManager2<T, Policy>()
		{
			Policy<T>::OnDestroy();
		}

		void Init()
		{
			System::Logger::Instance()->WriteMessage(L"Start caching resources of the manager");
			std::list<System::string> indexed = ReadResourcFile();
			System::Folder fld;
			fld.Open(Policy<T>::GetFolder());
			System::Logger::Instance()->WriteMessage(L"Look for files: " + Policy<T>::GetExtension());
			std::list<System::string> all_files = fld.Find(Policy<T>::GetExtension().Data());		

			std::list<System::string> unindexed;
			for each (System::string file in all_files)
			{
				auto it = std::find(indexed.begin(), indexed.end(), file);
				if (it == indexed.end())
				{
					unindexed.push_back(file);
				}
			}

			fld.Close();
			std::copy(unindexed.begin(), unindexed.end(), std::back_inserter(indexed));			
			UpdateResourceFile(indexed);
			System::Logger::Instance()->WriteMessage(L"Resource caching complete");

			LoadResources();
		}

		T* Get(int index)
		{
			return m_items[index]->Get();
		}

		const Collection& GetAll() const { return m_items; }

		static ResourceManager2<T, Policy>* Instance()
		{
			if (!m_instance.get())
			{
				m_instance.reset(new ResourceManager2<T, Policy>);
			}
			return m_instance.get();
		}

		static void Destroy()
		{
			m_instance.reset(0);
		}

	private:

		static std::auto_ptr<ResourceManager2> m_instance;

		Collection m_items;
	};

	template<class T, template <class U> class Policy> 
	std::auto_ptr<ResourceManager2<T, Policy>> ResourceManager2<T, Policy>::m_instance;
}

#endif _H_RESOURCE_MANAGER2