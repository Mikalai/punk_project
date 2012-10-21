#ifndef _H_PUNK_VIRTUAL_OBJECT_DESCRIPTORS
#define _H_PUNK_VIRTUAL_OBJECT_DESCRIPTORS

#include <iosfwd>
#include "../../math/vec3.h"
#include "../../math/mat4.h"
#include "../../math/bounding_box.h"

#include <memory>

namespace Utility
{
	class MeshDesc;
	class ArmatureDesc;
	class CameraDesc;
	class LightDesc;

	class PUNK_ENGINE ObjectDesc
	{
	public:
		System::string m_type;
		System::string m_name;
		System::string m_parent;
		System::string m_material;
		System::string m_reference;
		Math::vec3 m_location;
		Math::BoundingBox m_bbox;
		Math::mat4 m_world;
		Math::mat4 m_inv_parent;
		Math::mat4 m_local;
		std::auto_ptr<MeshDesc> m_mesh_desc;
		std::auto_ptr<MeshDesc> m_mesh_collision_desc;
		std::auto_ptr<ArmatureDesc> m_armature_desc;
		std::auto_ptr<CameraDesc> m_camera_desc;
		std::auto_ptr<LightDesc> m_light_desc;
		std::vector<System::string> m_supported_animations;
		std::vector<ObjectDesc*> m_children;

		~ObjectDesc();

		std::wostream& out_formatted(std::wostream& stream);
	};
}

#endif	//	_H_PUNK_VIRTUAL_OBJECT_DESCRIPTORS