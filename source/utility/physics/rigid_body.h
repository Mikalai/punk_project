#ifndef _H_PUNK_UTILITY_RIGID_BODY
#define _H_PUNK_UTILITY_RIGID_BODY

#include "../../math/mat4.h"

namespace Utility
{
	class ShapeBody;
	class Object;

	struct RigidBodyDesc
	{
		Math::mat4 m_initial_position;
		float m_mass;
		ShapeBody* m_shape;
		short m_group;
		short m_mask;
		bool m_is_character;

		RigidBodyDesc() : m_is_character(false) {}
			
	};

	class RigidBody
	{		
	public:
		virtual void SetObject(Object* object) = 0;
		virtual Object* GetObject(Object* object) = 0;
		virtual const Object* GetObject(Object* object) const = 0;
		virtual const Math::mat4 GetLocation() const = 0;
		virtual void SetLocation(const Math::Matrix4x4<float>& m) = 0;
	};
}

#endif	//	_H_PUNK_UTILITY_RIGID_BODY