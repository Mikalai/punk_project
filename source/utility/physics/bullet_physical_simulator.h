#ifndef _H_BULLET_PHYSICAL_SIMULATOR
#define _H_BULLET_PHYSICAL_SIMULATOR

#include <vector>
#include <LinearMath\btAlignedObjectArray.h>

#include "physical_simulator.h"

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

namespace Utility
{
	class BulletRigidBody;

	class BulletPhysicalSimulator : public PhysicalSimulator
	{
		std::auto_ptr<btCollisionConfiguration> m_collision_configuration;
		std::auto_ptr<btCollisionDispatcher> m_dispatcher;
		std::auto_ptr<btBroadphaseInterface> m_broad_phase_interface;
		std::auto_ptr<btSequentialImpulseConstraintSolver> m_solver;
		std::auto_ptr<btDiscreteDynamicsWorld> m_dynamics_world;

		btAlignedObjectArray<btCollisionShape*> m_collision_shapes;

	public:
		virtual void Update(float delta);
		virtual void Init();
		virtual void Clear();
		virtual RigidBody* CreateRigidBody(RigidBodyDesc& desc);
		virtual void CreateDynamicShapeBody(Object& object);
		virtual void SetGravity(const Math::Vector3<float>& g);
		virtual void SetTerrain(Terrain& terrain);
		virtual void SetRender(void* drawer);
		virtual void Draw();
		virtual ~BulletPhysicalSimulator();		
		void DestroyRigidBody(btRigidBody* body_ptr);
		void DestroyGhostBody(btGhostObject* ghost);
	private:
		void CreateConvexHulls(Object& object);
		void CombineConvexHulls(btCompoundShape* result, Object& object, const Math::Matrix4x4<float>& parent);
	};
}

#endif