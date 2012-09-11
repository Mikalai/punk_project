#ifndef _H_PUNK_SYSTEM_H_RESOURCE
#define _H_PUNK_SYSTEM_H_RESOURCE

#include "../config.h"

namespace System
{
	enum PermanentResourceType
	{
		PERMANENT_RESOURCE_NONE = -1,
		PERMANENT_RESOURCE_STATIC_MESH,
		PERMANENT_RESOURCE_SKINNED_MESH,
		PERMANENT_RESOURCE_POINT_LIGHT,
		PERMANENT_RESOURCE_SOUND,
		PERMANENT_RESOURCE_COLLISION_SHAPE,
		PERMANENT_RESOURCE_OBJECT,
		PERMANENT_RESOURCE_TEXTURE2D,
		PERMANENT_RESOURCE_SCENE,
		PERMANENT_RESOURCE_ARMATURE,		
		PERMANENT_RESOURCE_WEAPON_TYPE,
	};

	class PermanentData;
	class AbstractManager;

	class PUNK_ENGINE HResource
	{
		int m_type;
		int m_index;
		AbstractManager* m_manager;
	public:

		HResource(int type = -1, int index = -1);
		PermanentData* operator -> ();
		PermanentData* operator * ();
		const PermanentData* operator -> () const;
		bool IsValid() const { return m_index != -1 && m_type != -1; }
		int GetType() { return m_type; }
		int GetIndex() { return m_index; }
	};
}

#endif	//	_H_PUNK_SYSTEM_H_RESOURCE