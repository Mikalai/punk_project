#ifdef USE_BULLET_PHYSICS

#include "bullet_physical_simulator.h"
#include "bullet_rigid_body.h"

#include <memory>
#include <bullet/btBulletDynamicsCommon.h>
#include <bullet/BulletCollision/CollisionShapes/btHeightfieldTerrainShape.h>
#include <bullet/BulletCollision/CollisionDispatch/btGhostObject.h>
#include <bullet/BulletDynamics/Character/btCharacterControllerInterface.h>
#include <bullet/BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.h>
#include <bullet/BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h>
#include "bullet_terrain.h"
#include "bullet_physical_simulator.h"
#include "bullet_rigid_body.h"
#include "bullet_shape_body.h"

namespace Physics
{
	BulletSimulator::~BulletSimulator()
	{
		try
		{
			Clear();
		}
		catch(...)
		{}
	}

	void BulletSimulator::Update(float dt)
	{
		m_dynamics_world->stepSimulation(dt);
	}

	void BulletSimulator::SetGravity(const Math::vec3& g)
	{
		btVector3 v(g.X(), g.Y(), g.Z());
		m_dynamics_world->setGravity(v);
	}

	void BulletSimulator::Clear()
	{

		////	remove the rigidbodies from the dynamics world and delete them
		//for (int i = m_dynamics_world->getNumCollisionObjects()-1; i >= 0; ++i)
		//{
		//	btCollisionObject* object = m_dynamics_world->getCollisionObjectArray()[i];
		//	btRigidBody* body = btRigidBody::upcast(object);
		//	if (body && body->getMotionState())
		//	{
		//		delete body->getMotionState();
		//	}
		//	m_dynamics_world->removeCollisionObject(object);
		//	delete object;
		//}

		////	delete collision shapes
		//for (int i = 0; i < m_collision_shapes.size(); ++i)
		//{
		//	btCollisionShape* shape = m_collision_shapes[i];
		//	m_collision_shapes[i] = 0;
		//	delete shape;
		//}

		delete m_dynamics_world;
		delete m_solver;
		delete m_broad_phase_interface;
		delete m_dispatcher;
		delete m_collision_configuration;

		//	delete collision shapes
		for (int i = 0; i < m_collision_shapes.size(); ++i)
		{
			btCollisionShape* shape = m_collision_shapes[i];
			m_collision_shapes[i] = 0;
			delete shape;
		}
	}

	void BulletSimulator::Init()
	{
		m_collision_configuration = new btDefaultCollisionConfiguration;
		m_dispatcher = new btCollisionDispatcher(m_collision_configuration);
		m_broad_phase_interface = new btDbvtBroadphase();
		m_solver = new btSequentialImpulseConstraintSolver();
		m_dynamics_world = new btDiscreteDynamicsWorld(m_dispatcher, m_broad_phase_interface, m_solver, m_collision_configuration);
		m_dynamics_world->setGravity(btVector3(0, -9.8f, 0));
	}

	//void BulletSimulator::DestroyRigidBody(btRigidBody* body)
	//{
	//	if (body && body->getMotionState())
	//	{
	//		delete body->getMotionState();
	//	}
	//	m_dynamics_world->removeCollisionObject(body);
	//	delete body;
	//}

	//void BulletSimulator::DestroyGhostBody(btGhostObject* body)
	//{
	//	m_dynamics_world->removeCollisionObject(body);
	//}

	//void BulletSimulator::SetTerrain(Terrain& terrain)
	//{
	//}

	//void BulletSimulator::CreateConvexHulls(Object& object)
	//{
	//	//	if this collision mesh than we use it
	//	//if (object.IsCollisionVolume())
	//	//{
	//	//	//	get mesh
	//	//	const Mesh* mesh = object.GetMesh();
	//	//	//	if no mesh -> panic
	//	//	if (!mesh)
	//	//	{
	//	//		out_error() << L"Can't build concave shape. No mesh in " + object.GetName() << std::endl;
	//	//		return;
	//	//	}
	//	//	//	build collision shape
	//	//	btConvexHullShape* bullet_shape = new btConvexHullShape((btScalar*)&mesh->m_vertices[0], mesh->m_vertices.size(), sizeof(mesh->m_vertices[0]));
	//	//	m_collision_shapes.push_back(bullet_shape);

	//	//	//	create BulletShapeBody
	//	//	BulletShapeBody* shape_body = new BulletShapeBody;
	//	//	shape_body->SetCollisionShape(bullet_shape);
	//	//
	//	//	//	save shape body in the object
	//	//	object.SetShapeBody(shape_body);
	//	//}

	//	//for each (auto child in object.GetChildren())
	//	//{
	//	//	CreateConvexHulls(*child.get());
	//	//}
	//}

	////void BulletSimulator::CombineConvexHulls(btCompoundShape* result, Object& object, const Math::mat4& parent)
	////{
	////	//ShapeBody* body = object.GetShapeBody();
	////	//if (body)
	////	//{
	////	//	BulletShapeBody* shape_body = static_cast<BulletShapeBody*>(body);
	////	//	btTransform transform;
	////	//	transform.setFromOpenGLMatrix(&(parent*object.GetLocalMatrix())[0]);
	////	//	result->addChildShape(transform, shape_body->GetCollisionShape());
	////	//}

	////	//for each (auto child in object.GetChildren())
	////	//{
	////	//	CombineConvexHulls(result, *child.get(), parent*object.GetLocalMatrix());
	////	//}
	////}

	//void BulletSimulator::CreateDynamicShapeBody(Object& object)
	//{
	//	////	create for each collision volume collision shape
	//	//CreateConvexHulls(object);

	//	////	create compound shape
	//	//btCompoundShape* bullet_shape = new btCompoundShape;
	//	//m_collision_shapes.push_back(bullet_shape);
	//	////	make compound shape
	//	//CombineConvexHulls(bullet_shape, object, Math::mat4::CreateIdentity());

	//	//BulletShapeBody* final_shape_body = new BulletShapeBody;
	//	//final_shape_body->SetCollisionShape(bullet_shape);
	//	//object.SetShapeBody(final_shape_body);
	//}

	//RigidBody* BulletSimulator::CreateRigidBody(RigidBodyDesc& desc)
	//{
	//	if (desc.m_is_character)
	//	{
	//		/*		btTransform startTransform;
	//		startTransform.setIdentity ();
	//		startTransform.setFromOpenGLMatrix(&desc.m_initial_position[0]);

	//		btPairCachingGhostObject* m_ghostObject = new btPairCachingGhostObject();
	//		m_ghostObject->setWorldTransform(startTransform);
	//		m_broad_phase_interface->getOverlappingPairCache()->setInternalGhostPairCallback(new btGhostPairCallback());

	//		btScalar characterHeight = 1.0;
	//		btScalar characterWidth override.5;
	//		btConvexShape* capsule = new btCapsuleShape(characterWidth,characterHeight);

	//		m_ghostObject->setCollisionShape(capsule);
	//		m_ghostObject->getWorldTransform().setOrigin(btVector3(0, 1, 0));
	//		m_ghostObject->setCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT);

	//		btScalar stepHeight = btScalar(0.35);
	//		btKinematicCharacterController* m_character = new btKinematicCharacterController(m_ghostObject, capsule, stepHeight);

	//		///only collide with static for now (no interaction with dynamic objects)
	//		m_dynamics_world->addCollisionObject(m_ghostObject,btBroadphaseProxy::CharacterFilter, btBroadphaseProxy::StaticFilter|btBroadphaseProxy::DefaultFilter);

	//		m_dynamics_world->addAction(m_character);

	//		BulletRigidBody* body = new BulletRigidBody;
	//		body->SetCollisionObject(m_ghostObject);
	//		return body;*/
	//	}
	//	else
	//	{
	//		//btTransform transform;
	//		//transform.setFromOpenGLMatrix(&desc.m_initial_position[0]);
	//		//btDefaultMotionState* motion_state = new btDefaultMotionState(transform);

	//		//btVector3 inertia(0,0,0);
	//		//btCollisionShape* bullet_shape override;
	//		//if (desc.m_shape)
	//		//{
	//		//	BulletShapeBody* shape = static_cast<BulletShapeBody*>(desc.m_shape);
	//		//	bullet_shape = shape->GetCollisionShape();
	//		//	bullet_shape->calculateLocalInertia(desc.m_mass, inertia);
	//		//}

	//		//btRigidBody::btRigidBodyConstructionInfo info(desc.m_mass, motion_state, bullet_shape, inertia);
	//		//btRigidBody* bullet_body = new btRigidBody(info);

	//		//m_dynamics_world->addRigidBody(bullet_body);//, desc.m_group, desc.m_mask);

	//		//BulletRigidBody* body = new BulletRigidBody;
	//		//body->SetCollisionObject(bullet_body);

	//		//return body;
	//	}
	//	return 0;
	//}

	//void BulletSimulator::SetGravity(const Math::Vector3<float>& g)
	//{
	//	btVector3 v(g.X(), g.Y(), g.Z());
	//	m_dynamics_world->setGravity(v);
	//}

	//void BulletSimulator::Clear()
	//{

	//	//	remove the rigidbodies from the dynamics world and delete them
	//	for (int i = m_dynamics_world->getNumCollisionObjects()-1; i >= 0; ++i)
	//	{
	//		btCollisionObject* object = m_dynamics_world->getCollisionObjectArray()[i];
	//		btRigidBody* body = btRigidBody::upcast(object);
	//		if (body && body->getMotionState())
	//		{
	//			delete body->getMotionState();
	//		}
	//		m_dynamics_world->removeCollisionObject(object);
	//		delete object;
	//	}

	//	//	delete collision shapes
	//	for (int i = 0; i < m_collision_shapes.size(); ++i)
	//	{
	//		btCollisionShape* shape = m_collision_shapes[i];
	//		m_collision_shapes[i] = 0;
	//		delete shape;
	//	}

	//	m_dynamics_world.reset(0);
	//	m_solver.reset(0);
	//	m_broad_phase_interface.reset(0);
	//	m_dispatcher.reset(0);
	//	m_collision_configuration.reset(0);

	//	m_collision_shapes.clear();
	//}

	//BulletSimulator::~BulletSimulator()
	//{
	//	Clear();
	//}

	//void BulletSimulator::SetRender(void* drawer)
	//{
	//	m_dynamics_world->setDebugDrawer((btIDebugDraw*)(drawer));
	//}

	//void BulletSimulator::Draw()
	//{
	//	m_dynamics_world->debugDrawWorld();
	//}
};

#endif // USE_BULLET_PHYSICS
