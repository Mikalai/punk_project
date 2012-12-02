#include <ostream>
#include <istream>

#include "../system/storable_data.h"
#include "hresource.h"
#include "global_resource_manager.h"
//#include "abstract_manager.h"
#include "logger.h"

namespace System
{
	const System::string AsString(ObjectType type)
	{
		switch (type)
		{
		case System::RESOURCE_NONE:
			return L"BAD_RESOURCE";
		case System::STATIC_MESH:
			return L"STATIC_MESH";
		case System::SKINNED_MESH:
			return L"SKINNED_MESH";
		case System::QUAD:
			return L"QUAD";
		case System::SOUND_2D:
			return L"SOUND_2D";
		case System::SOUND_3D:
			return L"SOUND_3D";
		case System::FPS_CAMERA:
			return L"FPS_CAMERA";
		case System::PORTAL_NODE:
			return L"PORTAL_NODE";
		case System::AUDIO_BUFFER:
			return L"AUDIO_BUFFER";
		case System::TEXTURE_2D:
			return L"TEXTURE_2D";
		case System::TEXTURE_3D:
			return L"TEXTURE_3D";
		case System::MATERIAL:
			return L"MATERIAL";
		case ARMATURE:			
			return L"ARMATURE";
		case ARMATURE_ANIMATION_MIXER:
			return L"ARMATURE_ANIMATION_MIXER";
		case POINT_LIGHT:
			return L"POINT_LIGHT";
		case SCENE_GRAPH:
			return L"SCENE_GRAPH";
		case NODE:
			return L"NODE";
		case LIGHT_NODE:
			return L"LIGHT_NODE";
		case POINT_LIGHT_NODE:
			return L"POINT_LIGHT_NODE";
		case CAMERA_NODE:
			return L"CAMERA_NODE";
		case MATERIAL_NODE:
			return L"MATERIAL_NODE";
		case GEOMETRY_NODE:
			return L"GEOMETRY_NODE";
		case TRANSFORM_NODE:
			return L"TRANSFORM_NODE";
		case LOCATION_INDOOR:
			return L"LOCATION_INDOOR";
		case STATIC_GEOMETRY:
			return L"STATIC_GEOMETRY";
		default:
			return L"BAD_RESOURCE";
		}
	}

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
