#ifndef _H_PUNK_PHYSICS_BULLET_ADAPTER
#define _H_PUNK_PHYSICS_BULLET_ADAPTER

#include "../../math/mat4.h"

namespace Physics
{
	class BulletSimulator;

	class BulletAdapter 
	{
	public:
		virtual void EnterPhysicalSimulator(BulletSimulator* value) = 0;
		virtual void LeavePhysicalSimulator() = 0;
		virtual void SetTransform(const Math::mat4& value) = 0;
		virtual void GetTransform(Math::mat4& value) = 0;
	};
}

#endif	//	_H_PUNK_PHYSICS_BULLET_ADAPTER