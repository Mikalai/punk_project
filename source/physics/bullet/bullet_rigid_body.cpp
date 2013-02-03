#define _STATIC_CPPLIB
#include "bullet_rigid_body.h"
#include "bullet_physical_simulator.h"
#include "bullet_shape_body.h"
#include <bullet/btBulletDynamicsCommon.h>
#include <bullet/BulletCollision/CollisionDispatch/btGhostObject.h>

namespace Phyiscs
{
	void BulletRigidBody::Clear()
	{
		BulletPhysicalSimulator* sim = (BulletPhysicalSimulator*)BulletPhysicalSimulator::Instance();
		{
			btRigidBody* body = btRigidBody::upcast(m_rigid_body);
			if (body)
				sim->DestroyRigidBody(body);		
		}

		{
			btGhostObject* body = btPairCachingGhostObject::upcast(m_rigid_body);
			if (body)
				sim->DestroyGhostBody(body);
		}

		m_rigid_body = 0;
	}

	void BulletRigidBody::Init()
	{
		if (m_rigid_body)
			Clear();

		BulletPhysicalSimulator* sim = (BulletPhysicalSimulator*)BulletPhysicalSimulator::Instance();
		BulletShapeBody* shape_body;// = static_cast<BulletShapeBody*>(m_object->GetShapeBody());
		m_rigid_body = new btRigidBody(0, 0, shape_body->GetCollisionShape());		
	}

	void BulletRigidBody::SetObject(Object* object)
	{
		Clear();
		m_object = object;
		Init();
	}

	const Math::mat4 BulletRigidBody::GetLocation() const
	{
		Math::mat4 m;
		btRigidBody* body = btRigidBody::upcast(m_rigid_body);
		if (body)
		{
			btTransform t;
			body->getMotionState()->getWorldTransform(t);
			t.getOpenGLMatrix(&m[0]);
		}
		else
		{
			m_rigid_body->getWorldTransform().getOpenGLMatrix(&m[0]);;
		}
		return m;
	}

	void BulletRigidBody::SetLocation(const Math::Matrix4x4<float>& m)
	{
		btRigidBody* body = btRigidBody::upcast(m_rigid_body);
		if (body)
		{
			btTransform transform;
			transform.setFromOpenGLMatrix(&m[0]);
			body->setWorldTransform(transform);
		}
		else 
		{
			btTransform transform;
			transform.setFromOpenGLMatrix(&m[0]);
			m_rigid_body->setWorldTransform(transform);		
		}
	}


}