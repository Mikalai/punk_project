#include <ostream>
#include <istream>

#include "../system/storable_data.h"
#include "hresource.h"
#include "global_resource_manager.h"
//#include "abstract_manager.h"
#include "logger.h"

namespace System
{
	//HResource::HResource(int type, int index) 
	//	: m_type(type)
	//	, m_index(index) 
	//	, m_manager(GlobalManager::Instance()->FindManager(type))
	//{}

	//StorableData* HResource::operator -> ()
	//{
	//	if (m_manager)
	//		return m_manager->Get(m_index);
	//	out_warning() << "No resource with index " << m_index << " in resource manager for " << m_type << std::endl;
	//	return 0;
	//}

	//StorableData* HResource::operator * ()
	//{
	//	if (m_manager)
	//		return m_manager->Get(m_index);
	//	out_warning() << "No resource with index " << m_index << " in resource manager for " << m_type << std::endl;
	//	return 0;
	//}

	//const StorableData* HResource::operator -> () const
	//{
	//	if (m_manager)
	//		return m_manager->Get(m_index);
	//	out_warning() << "No resource with index " << m_index << " in resource manager for " << m_type << std::endl;
	//	return 0;
	//}

	//bool HResource::Save(std::ostream& stream)
	//{
	//	stream.write((char*)&m_type, sizeof(m_type));
	//	if (m_type >= System::DYNAMIC_RESOURCE_START)
	//	{
	//		System::string name = m_manager->GetResourceName(m_index);
	//		name.Save(stream);
	//		System::StorableData* data = m_manager->Get(m_index);
	//		return data->Save(stream);
	//	}
	//	else
	//	{
	//		const System::string location = m_manager->GetResourceName(m_index);
	//		return location.Save(stream);
	//	}		
	//}

	//bool HResource::Load(std::istream& stream)
	//{
	//	//stream.read((char*)&m_type, sizeof(m_type));
	//	//m_manager = GlobalManager::Instance()->FindManager(m_type);
	//	//if (!m_manager)
	//	//{
	//	//	out_error() << "Can't find resource manager for type" << m_type << std::endl;
	//	//	return false;
	//	//}

	//	//if (m_type >= System::DYNAMIC_RESOURCE_START)
	//	//{			
	//	//	System::string name;
	//	//	name.Load(stream);
	//	//	System::StorableData* data = m_manager->Create();
	//	//	data->Load(stream);
	//	//	m_manager->Manage(name, data);
	//	//}
	//	//else
	//	//{
	//	//	System::string location;
	//	//	location.Load(stream);
	//	//	//m_index = m_manager->Load(location).m_index;
	//	//	out_error() << "Obsolete: This should be eliminated from code" << std::endl;
	//	//	return false;
	//	//}
	//	//return true;
	//	return false;
	//}
}
