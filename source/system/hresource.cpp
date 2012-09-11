#include "hresource.h"
#include "global_resource_manager.h"
#include "abstract_manager.h"
#include "logger.h"

namespace System
{
	HResource::HResource(int type, int index) 
		: m_type(type)
		, m_index(index) 
		, m_manager(GlobalManager::Instance()->FindManager(type))
	{}

	PermanentData* HResource::operator -> ()
	{
		if (m_manager)
			return m_manager->Get(m_index);
		out_warning() << "No resource with index " << m_index << " in resource manager for " << m_type << std::endl;
		return 0;
	}

	PermanentData* HResource::operator * ()
	{
		if (m_manager)
			return m_manager->Get(m_index);
		out_warning() << "No resource with index " << m_index << " in resource manager for " << m_type << std::endl;
		return 0;
	}

	const PermanentData* HResource::operator -> () const
	{
		if (m_manager)
			return m_manager->Get(m_index);
		out_warning() << "No resource with index " << m_index << " in resource manager for " << m_type << std::endl;
		return 0;
	}
}
