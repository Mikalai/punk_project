#ifndef _H_RESOURCE_FACTORY
#define _H_RESOURCE_FACTORY

#include "handle_win32.h"
#include <memory>

namespace System
{
	class Resource;
	class string;

	class MODULE_SYSTEM ResourceFactory
	{
		struct ResourceFactoryImpl;
		std::auto_ptr<ResourceFactoryImpl> impl_rf;
		static std::auto_ptr<ResourceFactory> m_instance;

		ResourceFactory(const ResourceFactory&);
		ResourceFactory& operator = (const ResourceFactory&);

	public:

		ResourceFactory();

		void RegisterResource(const Descriptor::TypeCode& code, Resource* etalon);
		std::auto_ptr<Resource> Query(const Descriptor::TypeCode& code);
		
		static ResourceFactory* Instance();
		static void Destroy();
		static unsigned short GetBaseTypeCode(const string& module);
	};
}

#endif