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
#include "smart_pointers/handle.h"
#include "string.h"
#include "folder.h"

#include "logger.h"
//#include "abstract_manager.h"
#include "hresource.h"
#include "global_resource_manager.h"
#include "singletone.h"

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

	//template<class T, template<class> class Policy> 
	//class Resource2
	//{
	//	int m_index;
	//	System::string m_location;
	//	std::auto_ptr<T> m_resource;

	//	Resource2<T, Policy>(const Resource2<T, Policy>&);
	//	Resource2<T, Policy>& operator = (const Resource2<T, Policy>&);

	//	bool LoadResource()
	//	{
	//		m_resource.reset(new T());			
	//		out_message() << L"Loading " + Policy<T>::GetFolder() + m_location << std::endl;
	//		std::ifstream inp((Policy<T>::GetFolder() + m_location).Data(), std::ios_base::binary);
	//		m_resource->Load(inp);
	//		inp.close();

	//		return true;
	//	}

	//public:
	//	Resource2<T, Policy>()
	//		: m_index(-1)
	//		, m_location(L"/")
	//	{}

	//	void Init(int index, const System::string& location)
	//	{
	//		m_location = location;
	//		m_index = index;
	//	}

	//	T* Get() 
	//	{
	//		if (!m_resource.get())
	//		{
	//			LoadResource();
	//		}
	//		return m_resource.get();
	//	}

	//	void Set(T* item)
	//	{
	//		m_resource.reset(item);
	//	}

	//	void Unload()
	//	{
	//		m_resource.reset(0)
	//	}

	//	int GetTimeIntervalAccess();

	//	bool Save()
	//	{
	//		const wchar_t* name = wcsstr(m_location.Data(), L".");
	//		const System::string file(name + Policy<T>::GetExtension());
	//		char buf[2048];
	//		file.ToANSI(buf, 2048);
	//		std::wofstream out(buf);
	//		out << m_index << L' ' << m_location.Data() << std::endl;
	//		out.close();
	//		return true;
	//	}

	//	bool Load(const System::string resource_file)
	//	{
	//		std::wifstream inp(file.Data());
	//		out << m_index << L' ' << m_location.Data() << std::endl;
	//		out.close();

	//		return true;
	//	}	

	//	const System::string& GetLocation() const { return m_location; }
	//	int GetIndex() const { return m_index; }
	//};

	template<class T, template<class U> class Policy> class ResourceManager2;

	template<class T, template<class U> class Policy>
	class ResourceManager2 
	{
	public:
		typedef std::vector<Handle<T>> Collection;
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

		bool LoadResources()
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

					System::string file(buf);
					file = file.Trim(L" ");
					Proxy<T> res(T::CreateFromFile(file));
					// res->Init(index, file);
					//	we should place a resource in specifed by index position
					m_items.resize(std::max((int)m_items.size(), index + 1));
					m_items[index] = Handle<T>(res);
					UpdateIndexCache(index, file);
					out_message() << L"Resource " + System::string::Convert(index) + L" " + file + L" has been cached" << std::endl;
				}							
			}
			else
			{
				out_error() << L"Resource file '" + Policy<T>::GetResourceFile() + L"' was not found in " + Policy<T>::GetFolder() << std::endl;
			}
			out_message() << L"Loading resources complete" << std::endl;
			fld.Close();

			return true;
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
			m_items.clear();
			ClearIndexCache();
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

			//LoadResources();
		}
		
		//void Manage(const System::string& name, T* item)
		//{
		//	System::string location = name + Policy<T>::GetExtension().Replace(L"*", L"");
		//	System::Folder fld;
		//	fld.Open(Policy<T>::GetFolder());
		//	std::ofstream out(location.Data(), std::ios_base::binary);
		//	item->Save(out);
		//	fld.Close();
		//	
		//	int index = m_items.size();
		//	std::unique_ptr<T> res(new T);
		//	res->SetStorageName(location);
		//	//res->Init(index, location);
		//	m_items.push_back(res.release());
		//	m_dictionary[location] = index;
		//}

		int GetResourceType() const
		{
			return Policy<T>::GetResourceType();
		}

		Handle<T> Load(const System::string& filename)
		{			
			auto it = m_dictionary.find(filename);
			if (it == m_dictionary.end())
			{
				out_warning() << filename + L" was not cached. Try to load." << std::endl;
				Proxy<T> object(T::CreateFromFile(Policy<T>::GetFolder() + filename));
				if (!object.IsValid())
					return (out_error() << "Can't load " << filename << std::endl, nullptr);
				UpdateIndexCache(m_items.size(), filename);
				m_items.push_back(Handle<T>(object));
				return object;
			}
			return m_items[it->second];
		}

		virtual bool Save(int index)
		{
			if (index < 0 || index >= (int)m_items.size())
			{
				out_error() << "Can't save resource with index " << index << std::endl;
				return false;
			}
									
			System::Folder fld;
			fld.Open(Policy<T>::GetFolder());
			std::ofstream out(m_reverse_dictionary[index].Data(), std::ios_base::binary);
			if (!out.is_open())
				return (out_error() << "Can't save resource: " << m_reverse_dictionary[index] << std::endl, false);
			m_items[index]->Save(out);
			fld.Close();
			return true;
		}

		Handle<T> Get(int index)
		{
			return m_items[index];
		}

		const System::string GetResourceName(int index)
		{
			if (index < 0 || index >= (int)m_items.size())
			{
				out_error() << "Can't get resource name for index " << index << std::endl;
				return L"";
			}
			return m_reverse_dictionary[index];
		}

		T* Create()
		{
			std::auto_ptr<T> p(new T);

			return p.release();
		}

		bool Manage(const System::string& storage_name, T* data)
		{
			auto value = Proxy<T>(data);
			if (!storage_name.Length())
				return (out_error() << "Can't store data with empty storage name" << std::endl, false);
			if (m_dictionary.find(storage_name) != m_dictionary.end())
				return (out_error() << "Can't store data with the same name" << storage_name << std::endl, false);

			if (!value.IsValid())
				return (out_error() << "Can't manager resourse" << std::endl, false);

			int index = m_items.size();	
			m_items.push_back(value);
			UpdateIndexCache(index, storage_name);
			return true;
		}

		const Collection& GetAll() const { return m_items; }

		static ResourceManager2<T, Policy>* Instance()
		{
			if (!m_instance.get())
			{
				m_instance.reset(new ResourceManager2<T, Policy>);
//				GlobalManager::Instance()->RegisterManager(m_instance.get());
				System::MegaDestroyer::Instance()->PushDestroyer(Destroy);
			}
			return m_instance.get();
		}

		static void Destroy()
		{
			out_message() << "Destroying static object manager" << std::endl;
	//		GlobalManager::Instance()->UnregisterManager(m_instance.get());
			m_instance.reset(0);
		}

	private:

		void UpdateIndexCache(int index, const System::string name)
		{
			m_dictionary[name] = index;
			m_reverse_dictionary[index] = name;
		}

		void ClearIndexCache()
		{
			m_dictionary.clear();
			m_reverse_dictionary.clear();
		}

	private:
		
		typedef std::map<const System::string, int> Dictionary;
		typedef std::map<int, System::string> ReverseDictionary;

		static std::auto_ptr<ResourceManager2> m_instance;

		Collection m_items;
		Dictionary m_dictionary;
		ReverseDictionary m_reverse_dictionary;
	};

	template<class T, template <class U> class Policy> 
	std::auto_ptr<ResourceManager2<T, Policy>> ResourceManager2<T, Policy>::m_instance;
}

#endif _H_RESOURCE_MANAGER2