#ifndef _H_PUNK_PHYSICAL_SIMULATOR
#define _H_PUNK_PHYSICAL_SIMULATOR

#include "../config.h"
#include "../system/smart_pointers/module.h"

namespace Math
{
	class vec3;
}

namespace Physics
{
	struct RigidBodyDesc;
	class RigidBody;
	class ShapeBody;
	class Object;
	class Terrain;

	class PUNK_ENGINE_PUBLIC Simulator
	{
	public:
		void Init();
		void Clear();
		void Update(float delta);
		RigidBody* CreateRigidBody();
		void RemoveRigidBody(RigidBody* value);
		void SetGravity(const Math::vec3& g);
		~Simulator() {}

		struct SimulatorImpl;
		SimulatorImpl* impl;
	};
}

#endif
