#ifndef _H_PUNK_SYSTEM_H_RESOURCE
#define _H_PUNK_SYSTEM_H_RESOURCE

#include "../config.h"

namespace System
{
	enum ObjectType : unsigned
	{
		RESOURCE_NONE = -1,
		PERMANENT_RESOURCE_STATIC_MESH,
		PERMANENT_RESOURCE_SKINNED_MESH,
		PERMANENT_RESOURCE_POINT_LIGHT,
		PERMANENT_RESOURCE_AUDIO_BUFFER,
		PERMANENT_RESOURCE_COLLISION_SHAPE,		
		PERMANENT_RESOURCE_TEXTURE2D,
		PERMANENT_RESOURCE_SCENE,
		PERMANENT_RESOURCE_ARMATURE,		
		PERMANENT_RESOURCE_WEAPON_TYPE,

		DYNAMIC_RESOURCE_START = 0x2000,
		DYNAMIC_RESOURCE_OBJECT = 0x2000,
		DYNAMIC_RESOURCE_CAMERA_FPS,
		DYNAMIC_RESOURCE_CAMERA_1,
		DYNAMIC_RESOURCE_CAMERA_2,
		DYNAMIC_RESOURCE_PROXY,
		DYNAMIC_RESOURCE_TRANSFORM,
		DYNAMIC_RESOURCE_POINT_LIGHT,
		DYNAMIC_RESOURCE_SPOT_LIGHT,
		DYNAMIC_RESOURCE_MATERIAL,
		DYNAMIC_RESOURCE_ARMATURE_ANIMATION_MIXER,
		DYNAMIC_RESOURCE_OBJECT_ANIMATION_MIXER
	};

	/*class StorableData;
	class AbstractManager;

	class PUNK_ENGINE HResource
	{
		int m_type;
		int m_index;
		AbstractManager* m_manager;
	public:

		HResource(int type = -1, int index = -1);
		StorableData* operator -> ();
		StorableData* operator * ();
		const StorableData* operator -> () const;
		bool IsValid() const { return m_index != -1 && m_type != -1; }
		int GetType() { return m_type; }
		int GetIndex() { return m_index; }

		bool IsPermanent() { return m_type < DYNAMIC_RESOURCE_START; }
		bool IsDynamic() { return m_type >= DYNAMIC_RESOURCE_START; }

		bool Save(std::ostream& stream);
		bool Load(std::istream& stream);

		template<class T> 
		const T* As() const
		{
			if (T::GetType() == m_type && m_index >= 0)
				return static_cast<T*>(operator * ());
			return 0;
		}		

		template<class T>
		T* As() 
		{
			return const_cast<T*>(static_cast<const T*>(this)->As<T>());
		}
	};*/
}

#endif	//	_H_PUNK_SYSTEM_H_RESOURCE