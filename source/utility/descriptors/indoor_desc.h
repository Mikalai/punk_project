#ifndef _H_PUNK_UTILITY_DESCRIPTOR_LOCATION_INDOOR
#define _H_PUNK_UTILITY_DESCRIPTOR_LOCATION_INDOOR

#include "object_desc.h"

namespace Utility
{
	struct LocationIndoorDesc
	{
		System::string m_name;
		System::string m_parent;
		std::unique_ptr<MeshDesc> m_mesh_desc;
		std::unique_ptr<LightDesc> m_light_desc;
		std::vector<ObjectDesc*> m_children;
	};
}

#endif	//	_H_PUNK_UTILITY_DESCRIPTOR_LOCATION_INDOOR
