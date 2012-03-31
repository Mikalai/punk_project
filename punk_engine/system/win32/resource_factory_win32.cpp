#include "resource_factory_win32.h"
#include "string_win32.h"
#include "resource_win32.h"
#include "handle_win32.h"
#include "error_win32.h"
#include <map>

namespace System
{
	std::auto_ptr<ResourceFactory> ResourceFactory::m_instance;

	ResourceFactory::ResourceFactory()
	{
	}

	struct ResourceFactory::ResourceFactoryImpl
	{
		typedef std::map<Descriptor::TypeCode, std::tr1::shared_ptr<Resource>> value_type;
		typedef value_type::iterator iterator;
		typedef value_type::const_iterator const_iterator;

		value_type m_data;
	};

	void ResourceFactory::RegisterResource(const Descriptor::TypeCode& code, Resource* etalon)
	{
		etalon->SetDescriptor(Descriptor(code, 0));
		impl_rf->m_data[etalon->GetDescriptor().Type()].reset(etalon);
	}

	std::auto_ptr<Resource> ResourceFactory::Query(const Descriptor::TypeCode& type)
	{
		if (impl_rf->m_data.find(type) == impl_rf->m_data.end())
			throw SystemError(string::Format(L"Resource %d was not registered in ResourceFactory", type));
		return std::auto_ptr<Resource>(impl_rf->m_data[type]->Clone());

	}

	ResourceFactory* ResourceFactory::Instance()
	{
		if (!m_instance.get())
			m_instance.reset(new ResourceFactory());
		return m_instance.get();
	}

	void ResourceFactory::Destroy()
	{
		m_instance.reset(0);
	}

	unsigned short int ResourceFactory::GetBaseTypeCode(const string& module)
	{
		if (module == L"system_module")
			return 0;
		else if (module == L"image_module")
			return 100;
		else if (module == L"gui_module")
			return 200;
		else if (module == L"application_module")
			return 300;
		else if (module == L"logic_module")
			return 400;
		else if (module == L"math_module")
			return 500;
		else if (module == L"render_module")
			return 600;
		else if (module == L"scene_module")
			return 700;
		else if (module == L"string_module")
			return 800;
		else if (module == L"utility_module")
			return 900;
		else
			throw SystemError(module + L" is unknown module name");
	}

}