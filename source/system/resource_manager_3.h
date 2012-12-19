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

namespace System
{
	struct PUNK_ENGINE Policy
	{
		virtual System::Proxy<Object> Create() { return System::Proxy<Object>(new Object); }
		virtual const System::string GetResourceFile() { return L"BAD_FILE"; }
		virtual const System::string GetExtension() { return L"BAD_EXTENSION"; }
		virtual const System::string GetFolder() { return L"BAD_FILDER"; }
		virtual const System::ObjectType GetResourceType() { return System::ObjectType::RESOURCE_NONE; }
		virtual void OnInit() {}
		virtual void OnDestroy() {}
	};

	class PUNK_ENGINE ResourceManager3 : public ResourceCreator
	{
	public:
		typedef std::vector<Proxy<Object>> Collection;
		typedef Collection::iterator iterator;
		typedef Collection::const_iterator const_iterator;
	public:		
		ResourceManager3(Policy* policy);
		~ResourceManager3();			
		int GetResourceType() const;
		Proxy<Object> Load(const System::string& filename);
		virtual bool Save(int index) const;
		virtual Proxy<Object> Create();
		virtual Proxy<Object> Create(const string& name);
		virtual bool Init();	
		Proxy<Object> Get(int index);
		const System::string GetResourceName(int index);
		bool Manage(const System::string& storage_name, Proxy<Object> data);
		const Collection& GetAll() const;
	private:

		void UpdateIndexCache(int index, const System::string name);
		void ClearIndexCache();
		std::list<System::string> ReadResourcFile();
		void UpdateResourceFile(const std::list<System::string>& files);
		bool LoadResources();
		ResourceManager3(const ResourceManager3&);
		ResourceManager3& operator = (const ResourceManager3&);

	protected:

		typedef std::map<const System::string, int> Dictionary;
		typedef std::map<int, System::string> ReverseDictionary;		

		Collection m_items;
		Dictionary m_dictionary;
		ReverseDictionary m_reverse_dictionary;
		std::auto_ptr<Policy> m_policy;
	};	
}

#define REGISTER_MANAGER(THE_FILE, THE_EXT, THE_FOLDER, THE_TYPE_CODE, THE_NAMESPACE, THE_TYPE, ON_INIT, ON_DESTROY) \
namespace THE_NAMESPACE { class PUNK_ENGINE THE_TYPE##Manager; } \
namespace System { \
	struct PUNK_ENGINE Policy##THE_NAMESPACE##THE_TYPE : public Policy{ \
	public: \
		virtual System::Proxy<Object> Create() { return System::Proxy<THE_NAMESPACE::THE_TYPE>(new THE_NAMESPACE::THE_TYPE); }\
		virtual const System::string GetResourceFile() { return THE_FILE; } \
		virtual const System::string GetExtension() { return THE_EXT; } \
		virtual const System::string GetFolder() { return THE_FOLDER; }	\
		virtual const System::ObjectType GetResourceType() { return THE_TYPE_CODE; } \
		virtual void OnInit() { ON_INIT; } \
		virtual void OnDestroy() { ON_DESTROY; }\
	};\
} \
namespace THE_NAMESPACE { \
	class PUNK_ENGINE THE_TYPE##Manager : public System::ResourceManager3 { \
		THE_TYPE##Manager(const THE_TYPE##Manager&); \
		THE_TYPE##Manager& operator = (const THE_TYPE##Manager&);		\
	public:\
		THE_TYPE##Manager(System::Policy* policy) : System::ResourceManager3(policy) { \
			System::GetFactory()->RegisterCreator(m_policy->GetResourceType(), this); }\
		static THE_TYPE##Manager* Instance()  { \
			if (!m_instance##THE_TYPE) { \
				System::Policy##THE_NAMESPACE##THE_TYPE* policy = new System::Policy##THE_NAMESPACE##THE_TYPE();\
				m_instance##THE_TYPE = new THE_TYPE##Manager(policy); \
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

#endif _H_RESOURCE_MANAGER2
