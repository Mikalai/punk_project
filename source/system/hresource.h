#ifndef _H_PUNK_SYSTEM_H_RESOURCE
#define _H_PUNK_SYSTEM_H_RESOURCE

#include "../config.h"
#include "../string/string.h"

namespace System
{
	enum ObjectType : int
	{
		RESOURCE_NONE = -1,
		STATIC_MESH = 10,
		SKINNED_MESH,
		QUAD,
		SOUND_2D,
		SOUND_3D,
		FPS_CAMERA,
		PORTAL_NODE,
		AUDIO_BUFFER,
		TEXTURE_2D,
		TEXTURE_3D,
		MATERIAL,
		ARMATURE,
		ARMATURE_ANIMATION_MIXER,
		POINT_LIGHT,		
		SCENE_GRAPH,
		NODE,		
		LIGHT_NODE,
		POINT_LIGHT_NODE,
		CAMERA_NODE,
		MATERIAL_NODE,
		GEOMETRY_NODE,
		TRANSFORM_NODE,
		LOCATION_INDOOR,
		STATIC_GEOMETRY
	};

	PUNK_ENGINE const System::string AsString(ObjectType type);

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