#ifndef _H_RESOURCE_MANAGER2
#define _H_RESOURCE_MANAGER2

#include <vector>
#include <memory>
#include <fstream>
#include <list>
#include <algorithm>
#include <iterator>
#include <string>
#include <map>

#include "string.h"
#include "folder.h"

#include "logger.h"
#include "abstract_manager.h"
#include "hresource.h"
#include "global_resource_manager.h"

namespace System
{
	template<class T> 
	struct Policy
	{
		static const System::string GetResourceFile() { return L"BAD_FILE"; }
		static const System::string GetExtension() { return L"BAD_EXTENSION"; }
		static const System::string GetFolder() { return L"BAD_FILDER"; }
		static const int GetResourceType() { return -1; }
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
			out_message() << L"Loading " + Policy<T>::GetFolder() + m_location << std::endl;
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

		void Set(T* item)
		{
			m_resource.reset(new T(*item));
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

	template<class T, template<class U> class Policy> class ResourceManager2;

	template<class T, template<class U> class Policy>
	class ResourceManager2 : public AbstractManager
	{
	public:
		static const int RESOURCE_TYPE = __COUNTER__;
		typedef std::shared_ptr<Resource2<T, Policy>> ResourcePtr;
		typedef std::vector<ResourcePtr> Collection;
		typedef typename Collection::iterator iterator;
		typedef typename Collection::const_iterator const_iterator;
	private:
		std::list<System::string> ReadResourcFile()
		{
			out_message() << L"Reading all resources in " + Policy<T>::GetFolder() << std::endl;
			std::list<System::string> already_index;

			System::Folder fld;
			if (!fld.Open(Policy<T>::GetFolder()))
				out_error() << L"Can't open folder: " << Policy<T>::GetFolder() << std::endl;
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
					out_message() << L"Found resource " + System::string::Convert(index) + L" -> " + buf << std::endl;
				}
			}
			else
			{
				out_error() << System::string(L"Resource file ") + Policy<T>::GetResourceFile() + L" was not created in " + Policy<T>::GetFolder() + L" yet. " << std::endl;
			}
			fld.Close();
			out_message() << L"Reading resources complete" << std::endl;
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
			out_message() << L"Loading resources from " + Policy<T>::GetFolder() << std::endl;
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
					inp.getline(buf, 2048);
					if (wcslen(buf) == 0)
						break;

					std::shared_ptr<Resource2<T, Policy>> res(new Resource2<T, Policy>);
					System::string file(buf);
					file = file.Trim(L" ");
					res->Init(index, file);
					//	we should place a resource in specifed by index position
					m_items.resize(std::max((int)m_items.size(), index + 1));
					m_items[index] = res;
					m_dictionary[file] = index;
					out_message() << L"Resource " + System::string::Convert(index) + L" " + file + L" has been cached" << std::endl;
				}							
			}
			else
			{
				out_error() << L"Resource file '" + Policy<T>::GetResourceFile() + L"' was not found in " + Policy<T>::GetFolder() << std::endl;
			}
			out_message() << L"Loading resources complete" << std::endl;
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
			out_message() << L"Start caching resources of the manager" << std::endl;
			std::list<System::string> indexed = ReadResourcFile();
			System::Folder fld;
			fld.Open(Policy<T>::GetFolder());
			out_message() << L"Look for files: " + Policy<T>::GetExtension() << std::endl;
			std::list<System::string> all_files = fld.Find(Policy<T>::GetExtension().Data());		

			///	remove not existed files
			std::list<System::string> really_indexed;
			for each (System::string file in indexed)
			{
				auto it = std::find(all_files.begin(), all_files.end(), file);
				if (it != all_files.end())
				{
					really_indexed.push_back(file);
				}
			}

			std::list<System::string> unindexed;
			for each (System::string file in all_files)
			{
				auto it = std::find(really_indexed.begin(), really_indexed.end(), file);
				if (it == really_indexed.end())
				{
					unindexed.push_back(file);
				}
			}	

			fld.Close();
			std::copy(unindexed.begin(), unindexed.end(), std::back_inserter(really_indexed));			
			UpdateResourceFile(really_indexed);
			out_message() << L"Resource caching complete" << std::endl;

			LoadResources();
		}

		void Manage(const System::string& name, T* item)
		{
			System::string location = name + Policy<T>::GetExtension().Replace(L"*", L"");
			System::Folder fld;
			fld.Open(Policy<T>::GetFolder());
			std::ofstream out(location.Data(), std::ios_base::binary);
			item->Save(out);
			fld.Close();
			
			int index = m_items.size();
			std::shared_ptr<Resource2<T, Policy>> res(new Resource2<T, Policy>);
			res->Init(index, location);
			m_items.push_back(res);
			m_dictionary[location] = index;
		}

		virtual int GetResourceType() const
		{
			return Policy<T>::GetResourceType();
		}

		virtual HResource Load(const System::string& filename)
		{			
			auto it = m_dictionary.find(filename);
			if (it == m_dictionary.end())
			{
				out_error() << filename + L" was not cached. Can't load." << std::endl;
				return HResource();
			}
			return HResource(GetResourceType(), it->second);
		}

		virtual PermanentData* Get(int index)
		{
			return m_items[index]->Get();
		}

		const Collection& GetAll() const { return m_items; }

		static ResourceManager2<T, Policy>* Instance()
		{
			if (!m_instance.get())
			{
				m_instance.reset(new ResourceManager2<T, Policy>);
				GlobalManager::Instance()->RegisterManager(m_instance.get());				
			}
			return m_instance.get();
		}

		static void Destroy()
		{
			out_message() << "Destroying static object manager" << std::endl;
			GlobalManager::Instance()->UnregisterManager(m_instance.get());
			m_instance.reset(0);
		}

	private:
		
		typedef std::map<const System::string, int> Dictionary;

		static std::auto_ptr<ResourceManager2> m_instance;

		Collection m_items;
		Dictionary m_dictionary;
	};

	template<class T, template <class U> class Policy> 
	std::auto_ptr<ResourceManager2<T, Policy>> ResourceManager2<T, Policy>::m_instance;
}

#endif _H_RESOURCE_MANAGER2