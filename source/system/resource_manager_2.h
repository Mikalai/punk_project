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
#include "../math/helper.h"
#include "logger.h"
#include "hresource.h"
#include "global_resource_manager.h"
#include "singletone.h"
#include "resource_creator.h"
#include "factory.h"
#include "environment.h"

#define REGISTER_MANAGER(THE_FILE, THE_EXT, THE_FOLDER, THE_TYPE_CODE, THE_NAMESPACE, THE_TYPE) \
namespace THE_NAMESPACE { class PUNK_ENGINE THE_TYPE##Manager; } \
namespace System { \
	template<> class PUNK_ENGINE Policy<THE_NAMESPACE::THE_TYPE>  { \
	public: \
		static const System::string GetResourceFile() { return THE_FILE; } \
		static const System::string GetExtension() { return THE_EXT; } \
		static const System::string GetFolder() { return THE_FOLDER; }	\
		static System::ObjectType GetResourceType() { return THE_TYPE_CODE; } \
		static void OnInit() {} \
		static void OnDestroy() {}\
	};\
} \
namespace THE_NAMESPACE { \
	class PUNK_ENGINE THE_TYPE##Manager : public System::ResourceManager2<THE_TYPE, System::Policy> { \
		THE_TYPE##Manager(const THE_TYPE##Manager&); \
		THE_TYPE##Manager& operator = (const THE_TYPE##Manager&);		\
	public:\
		THE_TYPE##Manager() { \
			System::GetFactory()->RegisterCreator(System::Policy<THE_TYPE>::GetResourceType(), this); }\
		static THE_TYPE##Manager* Instance()  { \
			if (!m_instance##THE_TYPE) { \
				m_instance##THE_TYPE = new THE_TYPE##Manager; \
				System::MegaDestroyer::Instance()->PushDestroyer(Destroy); \
			}\
			return m_instance##THE_TYPE;\
		}\
		static void Destroy() {\
			out_message() << "Destroying static object manager" << std::endl;\
			delete m_instance##THE_TYPE; m_instance##THE_TYPE = 0;\
		}\
	private:\
		static THE_TYPE##Manager* m_instance##THE_TYPE;\
	}; \
	\
	static THE_TYPE##Manager* THE_TYPE##temp = THE_TYPE##Manager::Instance(); \
}

#define IMPLEMENT_MANAGER(THE_FILE, THE_EXT, THE_FOLDER, THE_TYPE_CODE, THE_NAMESPACE, THE_TYPE) \
	namespace THE_NAMESPACE { \
	THE_TYPE##Manager* THE_TYPE##Manager::m_instance##THE_TYPE; }

namespace System
{
	template<class T> 
	struct Policy
	{
		static const System::string GetResourceFile() { return L"BAD_FILE"; }
		static const System::string GetExtension() { return L"BAD_EXTENSION"; }
		static const System::string GetFolder() { return L"BAD_FILDER"; }
		static const System::ObjectType GetResourceType() { return System::ObjectType::RESOURCE_NONE; }
	};

	template<class T, template<class U> class Policy> class ResourceManager2;

	template<class T, template<class U> class Policy>
	class ResourceManager2 : public ResourceCreator
	{
	public:
		typedef std::vector<Proxy<T>> Collection;
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
				fld.Close();
				return std::list<System::string>();
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
					m_items.resize(Math::Max((int)m_items.size(), index + 1));
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
		
		int GetResourceType() const
		{
			return Policy<T>::GetResourceType();
		}

		Proxy<T> Load(const System::string& filename)
		{			
			auto it = m_dictionary.find(filename);
			if (it == m_dictionary.end())
			{
				out_warning() << filename + L" was not cached. Try to load." << std::endl;
				Proxy<T> object(T::CreateFromFile(Policy<T>::GetFolder() + filename));
				if (!object.IsValid())
					return (out_error() << "Can't load " << filename << std::endl, Proxy<T>(nullptr));
				UpdateIndexCache(m_items.size(), filename);
				m_items.push_back(object);
				return object;
			}
			return m_items[it->second];
		}

		virtual bool Save(int index) const
		{
			if (index < 0 || index >= (int)m_items.size())
			{
				out_error() << "Can't save resource with index " << index << std::endl;
				return false;
			}
									
			System::Folder fld;
			fld.Open(Policy<T>::GetFolder());
			std::ofstream out(m_reverse_dictionary.at(index).Data(), std::ios_base::binary);
			if (!out.is_open())
				return (out_error() << "Can't save resource: " << m_reverse_dictionary.at(index) << std::endl, false);
			m_items[index]->Save(out);
			fld.Close();
			return true;
		}

		virtual Proxy<Object> Create()
		{
			Proxy<T> object(new T);
			string name = string::Format(L"%d", m_items.size());
			Manage(name, object);
			return object;
		}

		virtual Proxy<Object> Create(const string& name)
		{
			System::Proxy<Object> o = Load(name);
			if (o.IsValid())
				return o;

			Proxy<Object> object(new T);
			Manage(name, object);
			object->SetStorageName(name);
			return object;
		}

		Proxy<T> Get(int index)
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

		bool Manage(const System::string& storage_name, Proxy<T> data)
		{						
			auto value = data;
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

		Collection m_items;
		Dictionary m_dictionary;
		ReverseDictionary m_reverse_dictionary;
	};	
}

#endif _H_RESOURCE_MANAGER2