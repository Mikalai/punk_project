#include "solid_cube.h"
#include "../../../scene/module.h"
#include "../../data/module.h"
#include "../../../physics/module.h"
#include <bullet/btBulletCollisionCommon.h>
#include <bullet/btBulletDynamicsCommon.h>

namespace Virtual
{
	struct Cube::CubeImpl
	{		
		Math::vec3 m_dim;
		Physics::BulletShapeBody* m_shape;
		Physics::BulletRigidBody* m_body;
		Physics::BulletSimulator* m_simulator;
		Virtual::Geometry* m_geometry;
		Scene::TransformNode* m_node;

		CubeImpl()
		{			
			m_shape = new Physics::BulletShapeBody();
			m_shape->InitBox(1,1,1);
			m_body = new Physics::BulletRigidBody();
			Physics::RigidBodyDesc desc;
			desc.m_group = 0;
			desc.m_is_character = false;
			desc.m_mask = 0;
			desc.m_mass = 1;
			desc.m_shape = m_shape->GetCollisionShape();
			m_body->Init(desc);
			m_dim.Set(1,1,1);
		}

		~CubeImpl()
		{
			safe_delete(m_shape);
			safe_delete(m_body);
		}
	};


	Cube::Cube()
		: impl(new CubeImpl)
	{}

	Cube::~Cube()
	{
		safe_delete(impl);
	}

	void Cube::SetGeometry(Geometry* geom)
	{
		impl->m_geometry = geom;
	}

	Geometry* Cube::GetGeometry()
	{
		return impl->m_geometry;
	}

	void Cube::SetMass(float mass)
	{
		btVector3 inertia(0,0,0);
		if (mass != 0)
			impl->m_shape->GetCollisionShape()->calculateLocalInertia(mass, inertia);		
		impl->m_body->GetRigidBody()->setMassProps(mass, inertia);		
	}

	float Cube::GetMass() const
	{
		float inv_mass = impl->m_body->GetRigidBody()->getInvMass();
		if (inv_mass == 0)
			return 0;
		return 1.0f / inv_mass;
	}

	void Cube::SetDimensions(const Math::vec3& value)
	{
		impl->m_dim = value;
		float mass = GetMass();
		impl->m_shape->InitBox(value[0], value[1], value[2]);
		btVector3 inertia(0,0,0);
		if (mass != 0)
			impl->m_shape->GetCollisionShape()->calculateLocalInertia(mass, inertia);		
		impl->m_body->GetRigidBody()->setCollisionShape(impl->m_shape->GetCollisionShape());
		impl->m_body->GetRigidBody()->setMassProps(mass, inertia);
	}

	const Math::vec3 Cube::GetDimensions() const
	{
		return impl->m_dim;
	}

	void Cube::OnEnterSceneGraph(Scene::SceneGraph* graph, Scene::Node* node)
	{
		impl->m_node = Cast<Scene::TransformNode*>(node);
		impl->m_body->GetMotionState()->SetNode(impl->m_node);
	}

	void Cube::OnLeaveSceneGraph(Scene::SceneGraph* graph) 
	{
		impl->m_node = nullptr;
		impl->m_body->GetMotionState()->SetNode(nullptr);
	}

	void Cube::OnEnterVisibility() 
	{
	}
	
	void Cube::OnLostVisibility()
	{
	}

	void Cube::EnterPhysicalSimulator(Physics::BulletSimulator* value) 
	{
		impl->m_simulator = value;
		impl->m_body->EnterWorld(value->GetWorld());
	}

	void Cube::LeavePhysicalSimulator() 
	{
		impl->m_body->LeaveWorld();
	}

	void Cube::SetTransform(const Math::mat4& value)
	{
		btTransform t;
		t.setFromOpenGLMatrix(&value[0]);
		impl->m_body->GetRigidBody()->setWorldTransform(t);
		impl->m_body->GetRigidBody()->activate(true);
	}

	void Cube::GetTransform(Math::mat4& value)
	{
		impl->m_body->GetRigidBody()->getWorldTransform().getOpenGLMatrix(&value[0]);
	}
}