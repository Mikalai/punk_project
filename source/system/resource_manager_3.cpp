//#include "resource_manager_3.h"
//
//namespace System
//{
//
//	ResourceManager3::ResourceManager3(Policy* policy) : m_policy(policy)
//	{						
//	}
//
//	ResourceManager3::~ResourceManager3()
//	{
//		m_policy->OnDestroy();
//		m_items.clear();
//		ClearIndexCache();
//	}
//
//	bool ResourceManager3::Init()
//	{	
//		m_policy->OnInit();
//		out_message() << L"Start caching resources of the manager" << std::endl;
//		std::list<System::string> indexed = ReadResourcFile();
//		System::Folder fld;
//		fld.Open(m_policy->GetFolder());
//		out_message() << L"Look for files: " + m_policy->GetExtension() << std::endl;
//		std::list<System::string> all_files = fld.Find(m_policy->GetExtension().Data());		
//
//		///	remove not existed files
//		std::list<System::string> really_indexed;
//		for each (System::string file in indexed)
//		{
//			auto it = std::find(all_files.begin(), all_files.end(), file);
//			if (it != all_files.end())
//			{
//				really_indexed.push_back(file);
//			}
//		}
//
//		std::list<System::string> unindexed;
//		for each (System::string file in all_files)
//		{
//			auto it = std::find(really_indexed.begin(), really_indexed.end(), file);
//			if (it == really_indexed.end())
//			{
//				unindexed.push_back(file);
//			}
//		}	
//
//		fld.Close();
//		std::copy(unindexed.begin(), unindexed.end(), std::back_inserter(really_indexed));			
//		UpdateResourceFile(really_indexed);
//		out_message() << L"Resource caching complete" << std::endl;
//
//		return true;
//	}
//
//	int ResourceManager3::GetResourceType() const
//	{
//		return m_policy->GetResourceType();
//	}
//
//	Proxy<Object> ResourceManager3::Load(const System::string& filename)
//	{			
//		auto it = m_dictionary.find(filename);
//		if (it == m_dictionary.end())
//		{
//			out_warning() << filename + L" was not cached. Try to load." << std::endl;
//			Proxy<Object> object = m_policy->Create();
//			if (!object.IsValid())
//				return (out_error() << "Can't create " << AsString(m_policy->GetResourceType()) << std::endl, Proxy<Object>(nullptr));
//			std::ifstream stream((m_policy->GetFolder() + filename).Data(), std::ios_base::binary);
//			if (!stream.is_open())
//				return (out_error() << "Can't load " << filename << std::endl, Proxy<Object>(nullptr));
//			object->Load(stream);
//			stream.close();				
//			UpdateIndexCache(m_items.size(), filename);
//			m_items.push_back(object);
//			return object;
//		}
//		return m_items[it->second];
//	}
//
//	bool ResourceManager3::Save(int index) const
//	{
//		if (index < 0 || index >= (int)m_items.size())
//		{
//			out_error() << "Can't save resource with index " << index << std::endl;
//			return false;
//		}
//
//		System::Folder fld;
//		fld.Open(m_policy->GetFolder());
//		std::ofstream out(m_reverse_dictionary.at(index).Data(), std::ios_base::binary);
//		if (!out.is_open())
//			return (out_error() << "Can't save resource: " << m_reverse_dictionary.at(index) << std::endl, false);
//		m_items[index]->Save(out);
//		fld.Close();
//		return true;
//	}
//
//	Proxy<Object> ResourceManager3::Create()
//	{
//		Proxy<Object> object = m_policy->Create();
//		string name = string::Format(L"%d", m_items.size());
//		Manage(name, object);
//		return object;
//	}
//
//	Proxy<Object> ResourceManager3::Create(const string& name)
//	{
//		auto it = m_dictionary.find(name);
//		if (it == m_dictionary.end())
//		{
//			Proxy<Object> object = m_policy->Create();
//			Manage(name, object);
//			object->SetStorageName(name);
//			return object;
//		}
//		return m_items[it->second];
//	}
//
//	Proxy<Object> ResourceManager3::Get(int index)
//	{
//		return m_items[index];
//	}
//
//	const System::string ResourceManager3::GetResourceName(int index)
//	{
//		if (index < 0 || index >= (int)m_items.size())
//		{
//			out_error() << "Can't get resource name for index " << index << std::endl;
//			return L"";
//		}
//		return m_reverse_dictionary[index];
//	}
//
//	bool ResourceManager3::Manage(const System::string& storage_name, Proxy<Object> data)
//	{						
//		auto value = data;
//		if (!storage_name.Length())
//			return (out_error() << "Can't store data with empty storage name" << std::endl, false);
//		if (m_dictionary.find(storage_name) != m_dictionary.end())
//			return (out_error() << "Can't store data with the same name" << storage_name << std::endl, false);
//
//		if (!value.IsValid())
//			return (out_error() << "Can't manager resourse" << std::endl, false);
//
//		int index = m_items.size();	
//		m_items.push_back(value);
//		UpdateIndexCache(index, storage_name);
//		return true;
//	}
//
//	void ResourceManager3::UpdateIndexCache(int index, const System::string name)
//	{
//		m_dictionary[name] = index;
//		m_reverse_dictionary[index] = name;
//	}
//
//	void ResourceManager3::ClearIndexCache()
//	{
//		m_dictionary.clear();
//		m_reverse_dictionary.clear();
//	}
//
//
//	std::list<System::string> ResourceManager3::ReadResourcFile()
//	{
//		out_message() << L"Reading all resources in " + m_policy->GetFolder() << std::endl;
//		std::list<System::string> already_index;
//
//		System::Folder fld;
//		if (!fld.Open(m_policy->GetFolder()))
//			out_error() << L"Can't open folder: " << m_policy->GetFolder() << std::endl;
//		std::wifstream inp(m_policy->GetResourceFile().Data());
//		if (inp.is_open())
//		{
//			while (!inp.eof())
//			{
//				int index;
//				wchar_t buf[2048];
//				inp >> index;
//				inp >> buf;	
//				if (wcslen(buf) == 0)
//					break;
//				already_index.push_back(System::string(buf));
//				out_message() << L"Found resource " + System::string::Convert(index) + L" -> " + buf << std::endl;
//			}
//		}
//		else
//		{
//			fld.Close();
//			return std::list<System::string>();
//		}
//		fld.Close();
//		out_message() << L"Reading resources complete" << std::endl;
//		return already_index;
//	}
//
//	void ResourceManager3::UpdateResourceFile(const std::list<System::string>& files)
//	{
//		int k = 0;
//		System::Folder fld;
//		fld.Open(m_policy->GetFolder());
//		std::wofstream out(m_policy->GetResourceFile().Data());
//		for each(System::string file in files)
//		{
//			out << k << L' ' << file.Data() << std::endl;
//			k++;
//		}
//		out.close();
//		fld.Close();
//	}
//
//	bool ResourceManager3::LoadResources()
//	{			
//		m_items.clear();
//		out_message() << L"Loading resources from " + m_policy->GetFolder() << std::endl;
//		System::Folder fld;
//		fld.Open(m_policy->GetFolder());
//		std::wifstream inp(m_policy->GetResourceFile().Data());
//		if (inp.is_open())
//		{
//			while (!inp.eof())
//			{
//				int index;
//				wchar_t buf[2048];				
//				inp >> index;
//				if (inp.eof())
//					break;
//				inp.getline(buf, 2048);
//				if (wcslen(buf) == 0)
//					break;
//
//				System::string file(buf);
//				file = file.Trim(L" ");
//				Proxy<Object> res = Load(file);
//				// res->Init(index, file);
//				//	we should place a resource in specifed by index position
//				m_items.resize(Math::Max((int)m_items.size(), index + 1));
//				m_items[index] = res;
//				UpdateIndexCache(index, file);
//				out_message() << L"Resource " + System::string::Convert(index) + L" " + file + L" has been cached" << std::endl;
//			}							
//		}
//		else
//		{
//			out_error() << L"Resource file '" + m_policy->GetResourceFile() + L"' was not found in " + m_policy->GetFolder() << std::endl;
//		}
//		out_message() << L"Loading resources complete" << std::endl;
//		fld.Close();
//
//		return true;
//	}
//}