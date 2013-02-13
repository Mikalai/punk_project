#ifndef _H_PUNK_PHYSICAL_SIMULATOR
#define _H_PUNK_PHYSICAL_SIMULATOR

#include "../config.h"
#include "../system/smart_pointers/module.h"

namespace Math
{
	class vec3;
}

namespace Phyiscs
{
	struct RigidBodyDesc;
	class RigidBody;
	class ShapeBody;
	class Object;
	class Terrain;

	class PUNK_ENGINE Simulator	
	{
	public:
		virtual void Init() = 0;
		virtual void Clear() = 0;
		virtual void Update(float delta) = 0;
		virtual RigidBody* CreateRigidBody() = 0;
		virtual void RemoveRigidBody(RigidBody* value) = 0;
		virtual void SetGravity(const Math::vec3& g) = 0;
		virtual ~Simulator() {}
	};
}

#endif