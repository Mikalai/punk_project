#ifdef USE_BULLET_PHYSICS

#ifndef _H_BULLET_PHYSICAL_SIMULATOR
#define _H_BULLET_PHYSICAL_SIMULATOR

#include <vector>
#include <memory>
#include <bullet/LinearMath/btAlignedObjectArray.h>
#include "../physical_simulator.h"
#include "../../system/smart_pointers/module.h"

namespace Math
{
	template<class T> class Matrix4x4;
}

class btCollisionConfiguration;
class btCollisionDispatcher;
class btBroadphaseInterface;
class btCollisionShape;
class btSequentialImpulseConstraintSolver;
class btDiscreteDynamicsWorld;
class btCompoundShape;
class btRigidBody;
class btGhostObject;

namespace Physics
{
	class BulletRigidBody;

	class PUNK_ENGINE_PUBLIC BulletSimulator
	{
	public:
		virtual void Init();
		virtual void Clear();
		virtual void Update(float delta);
		virtual void SetGravity(const Math::vec3& g);
		virtual ~BulletSimulator();

		btDiscreteDynamicsWorld* GetWorld() { return m_dynamics_world; }

	private:
		btCollisionConfiguration* m_collision_configuration;
		btCollisionDispatcher* m_dispatcher;
		btBroadphaseInterface* m_broad_phase_interface;
		btSequentialImpulseConstraintSolver* m_solver;
		btDiscreteDynamicsWorld* m_dynamics_world;

		btAlignedObjectArray<btCollisionShape*> m_collision_shapes;
	};
}

#endif

#endif // USE_BULLET_PHYSICS
