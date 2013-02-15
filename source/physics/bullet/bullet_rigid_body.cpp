#include <bullet/btBulletDynamicsCommon.h>
#include <bullet/BulletCollision/CollisionDispatch/btGhostObject.h>
#include "../error/module.h"
#include "bullet_shape_body.h"
#include "bullet_physical_simulator.h"
#include "bullet_rigid_body.h"
#include "bullet_motion_state.h"

namespace Physics
{
	BulletRigidBody::BulletRigidBody()
		: m_rigid_body(nullptr)
		, m_world(nullptr)
	{}

	void BulletRigidBody::Init(RigidBodyDesc& desc)
	{
		btTransform trans;
		trans.setFromOpenGLMatrix(&desc.m_initial_position[0]);

		bool dynamic = desc.m_mass != 0.0f;
		btVector3 inertia(0,0,0);
		if (dynamic)
			desc.m_shape->calculateLocalInertia(desc.m_mass, inertia);

		BulletMotionState* state = new BulletMotionState(trans, nullptr);
		btRigidBody::btRigidBodyConstructionInfo info(desc.m_mass, state, desc.m_shape, inertia);
		m_rigid_body = new btRigidBody(info);
	}

	BulletRigidBody::~BulletRigidBody()
	{
		try
		{
			LeaveWorld();
			if (m_rigid_body && m_rigid_body->getMotionState())
			{
				delete m_rigid_body->getMotionState();
			}
			delete m_rigid_body;
			m_rigid_body = nullptr;
		}
		catch(...)
		{
		}
	}

	void BulletRigidBody::EnterWorld(btDiscreteDynamicsWorld* world)
	{
		if (!m_rigid_body)
			throw PunkPhysicsException(L"No rigid body to enter the world");

		if (m_world)
			m_world->removeRigidBody(m_rigid_body);

		m_world = world;
		m_world->addRigidBody(m_rigid_body);
	}

	void BulletRigidBody::LeaveWorld()
	{
		if (!m_world)
			throw PunkPhysicsException(L"Can't leave any world, because no world entered");

		m_world->removeRigidBody(m_rigid_body);
		m_world = nullptr;
	}

	BulletMotionState* BulletRigidBody::GetMotionState() 
	{
		return (BulletMotionState*)m_rigid_body->getMotionState();
	}

	const BulletMotionState* BulletRigidBody::GetMotionState() const
	{
		return (const BulletMotionState*)m_rigid_body->getMotionState();
	}

	//void BulletRigidBody::Clear()
	//{
	//	BulletSimulator* sim = (BulletSimulator*)BulletSimulator::Instance();
	//	{
	//		btRigidBody* body = btRigidBody::upcast(m_rigid_body);
	//		if (body)
	//			sim->DestroyRigidBody(body);		
	//	}

	//	{
	//		btGhostObject* body = btPairCachingGhostObject::upcast(m_rigid_body);
	//		if (body)
	//			sim->DestroyGhostBody(body);
	//	}

	//	m_rigid_body = 0;
	//}

	//void BulletRigidBody::Init()
	//{
	//	if (m_rigid_body)
	//		Clear();

	//	BulletSimulator* sim = (BulletSimulator*)BulletSimulator::Instance();
	//	BulletShapeBody* shape_body;// = static_cast<BulletShapeBody*>(m_object->GetShapeBody());
	//	m_rigid_body = new btRigidBody(0, 0, shape_body->GetCollisionShape());		
	//}

	//void BulletRigidBody::SetObject(Object* object)
	//{
	//	Clear();
	//	m_object = object;
	//	Init();
	//}

	//const Math::mat4 BulletRigidBody::GetLocation() const
	//{
	//	Math::mat4 m;
	//	btRigidBody* body = btRigidBody::upcast(m_rigid_body);
	//	if (body)
	//	{
	//		btTransform t;
	//		body->getMotionState()->getWorldTransform(t);
	//		t.getOpenGLMatrix(&m[0]);
	//	}
	//	else
	//	{
	//		m_rigid_body->getWorldTransform().getOpenGLMatrix(&m[0]);;
	//	}
	//	return m;
	//}

	//void BulletRigidBody::SetLocation(const Math::Matrix4x4<float>& m)
	//{
	//	btRigidBody* body = btRigidBody::upcast(m_rigid_body);
	//	if (body)
	//	{
	//		btTransform transform;
	//		transform.setFromOpenGLMatrix(&m[0]);
	//		body->setWorldTransform(transform);
	//	}
	//	else 
	//	{
	//		btTransform transform;
	//		transform.setFromOpenGLMatrix(&m[0]);
	//		m_rigid_body->setWorldTransform(transform);		
	//	}
	//}


}