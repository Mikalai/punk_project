//#include <sstream>
//#include "../../system/logger.h"
//#include "object_desc.h"
//#include "camera_desc.h"
//#include "armature_desc.h"
//#include "mesh_desc.h"
//
//namespace Utility
//{
//	ObjectDesc::~ObjectDesc()
//	{
//		for (auto child : m_children)
//		{
//			delete child;
//		}
//	}
//
//	std::wostream& ObjectDesc::out_formatted(std::wostream& stream)
//	{
//		stream << Tab() << typeid(*this).name() << std::endl;
//		Tab::Inc();
//		stream << Tab() << "Name: " << m_name.Data() << std::endl;
//		stream << Tab() << "Type: " << m_type.Data() << std::endl;
//		stream << Tab() << "Parent: " << m_parent.Data() << std::endl;
//		stream << Tab() << "Material: " << m_material.Data() << std::endl;
//		if (m_reference.Size())
//			stream << Tab() << "Referenced object: " << m_reference.Data() << std::endl;
//		stream << Tab() << "Location: "; m_location.out_formatted(stream) << std::endl;
////		stream << Tab() << "Bounding box: \n"; m_bbox.out_formatted(stream) << std::endl;
//		stream << Tab() << "World matrix: \n" << m_world << std::endl;
//		stream << Tab() << "Inversed parent: \n" << m_inv_parent << std::endl;
//		stream << Tab() << "Local matrix: \n" << m_local << std::endl;
//		if (m_mesh_desc.get())
//		{
//			stream << Tab() << "Mesh: " << std::endl;
//			Tab::Inc();
//			m_mesh_desc->out_formatted(stream) << std::endl;
//			Tab::Dec();		
//		}
//
//		if (m_armature_desc.get())
//		{
//			stream << Tab() << "Armature: " << std::endl;
//			Tab::Inc();
//			m_armature_desc->out_formatted(stream) << std::endl;
//			Tab::Dec();
//		}
//
//		if (m_camera_desc.get())
//		{
//			stream << Tab() << "Camera: " << std::endl;
//			Tab::Inc();
//			m_camera_desc->out_formatted(stream) << std::endl;	
//			Tab::Dec();
//		}
//
//		if (!m_supported_animations.empty())
//		{
//			stream << Tab() << "Supported animations: " << std::endl;
//			Tab::Inc();
//			for (auto anim : m_supported_animations)
//				stream << Tab() << anim.Data() << std::endl;
//			Tab::Dec();
//		}
//
//		stream << Tab() << "Children: " << std::endl;
//		Tab::Inc();
//		for (auto child :  m_children)
//			child->out_formatted(stream) << std::endl;
//		Tab::Dec();
//
//		Tab::Dec();
//		stream << Tab() << typeid(*this).name();
//
//		return stream;
//	}
//}