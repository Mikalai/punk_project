#include <memory>
#include <btBulletDynamicsCommon.h>
#include <BulletCollision/CollisionShapes/btHeightfieldTerrainShape.h>
#include "BulletCollision/CollisionDispatch/btGhostObject.h"
#include "BulletDynamics/Character/btKinematicCharacterController.h"

#include "../../system/logger.h"
#include "object.h"
#include "../elements/terrain.h"

#include "bullet_physical_simulator.h"
#include "bullet_rigid_body.h"
#include "bullet_shape_body.h"

namespace Utility
{
	void BulletPhysicalSimulator::DestroyRigidBody(btRigidBody* body)
	{
		if (body && body->getMotionState())
		{
			delete body->getMotionState();
		}
		m_dynamics_world->removeCollisionObject(body);
		delete body;
	}

	void BulletPhysicalSimulator::DestroyGhostBody(btGhostObject* body)
	{
		m_dynamics_world->removeCollisionObject(body);		
	}

	void BulletPhysicalSimulator::SetTerrain(Terrain& terrain)
	{		
#define USE_HEIGHT_FIELD
#ifdef USE_TRIMESH
		{
//	TRIMESH AS GROUND
	int i;

const float TRIANGLE_SIZE=20.f;

	//create a triangle-mesh ground
	int vertStride = sizeof(btVector3);
	int indexStride = 3*sizeof(int);

	const int NUM_VERTS_X = 20;
	const int NUM_VERTS_Y = 20;
	const int totalVerts = NUM_VERTS_X*NUM_VERTS_Y;
	
	const int totalTriangles = 2*(NUM_VERTS_X-1)*(NUM_VERTS_Y-1);

	m_vertices = new btVector3[totalVerts];
	int*	gIndices = new int[totalTriangles*3];

	

	for ( i=0;i<NUM_VERTS_X;i++)
	{
		for (int j=0;j<NUM_VERTS_Y;j++)
		{
			float wl = .2f;
			//height set to zero, but can also use curved landscape, just uncomment out the code
			float height = 0.f;//20.f*sinf(float(i)*wl)*cosf(float(j)*wl);

			m_vertices[i+j*NUM_VERTS_X].setValue(
				(i-NUM_VERTS_X*0.5f)*TRIANGLE_SIZE,
				height,
				(j-NUM_VERTS_Y*0.5f)*TRIANGLE_SIZE);

		}
	}

	int index=0;
	for ( i=0;i<NUM_VERTS_X-1;i++)
	{
		for (int j=0;j<NUM_VERTS_Y-1;j++)
		{
			gIndices[index++] = j*NUM_VERTS_X+i;
			gIndices[index++] = j*NUM_VERTS_X+i+1;
			gIndices[index++] = (j+1)*NUM_VERTS_X+i+1;

			gIndices[index++] = j*NUM_VERTS_X+i;
			gIndices[index++] = (j+1)*NUM_VERTS_X+i+1;
			gIndices[index++] = (j+1)*NUM_VERTS_X+i;
		}
	}
	
	m_indexVertexArrays = new btTriangleIndexVertexArray(totalTriangles,
		gIndices,
		indexStride,
		totalVerts,(btScalar*) &m_vertices[0].x(),vertStride);

	bool useQuantizedAabbCompression = true;
	groundShape = new btBvhTriangleMeshShape(m_indexVertexArrays,useQuantizedAabbCompression);
	
	tr.setOrigin(btVector3(0,-4.5f,0));
		}
		///////////////////////////////////////////////////////
#endif
#ifdef USE_HEIGHT_FIELD
		unsigned char* data = terrain.GetLandscape()->GetData();
		btHeightfieldTerrainShape* bullet_shape = new btHeightfieldTerrainShape	
			(2048, 2048,
			data, terrain.GetScale(),
			btScalar(0.0), (btScalar)(255.0*terrain.GetScale()),
			1, PHY_UCHAR, false);
		
		btTransform t;
		btVector3 mmin, mmax;
		bullet_shape->getAabb(t, mmin, mmax);
		
		int k = 0;

		BulletShapeBody* shape_body = new BulletShapeBody;
		m_collision_shapes.push_back(bullet_shape);
		shape_body->SetCollisionShape(bullet_shape);
		terrain.SetShapeBody(shape_body);

		btTransform start_transform;
		start_transform.setIdentity();		
		start_transform.setOrigin(btVector3(1023.5, 127.5, 1023.5));
			
		btDefaultMotionState* myMotionState = new btDefaultMotionState(start_transform);

		btRigidBody::btRigidBodyConstructionInfo cInfo(0.0, myMotionState, bullet_shape, btVector3(0,0,0));
		 
		btRigidBody* body = new btRigidBody(cInfo);
		body->setContactProcessingThreshold(BT_LARGE_FLOAT);
		m_dynamics_world->addRigidBody(body);
#endif
#undef USE_HEIGHT_FIELD
	}

	void BulletPhysicalSimulator::Update(float dt)
	{
		m_dynamics_world->stepSimulation(dt);
	}

	void BulletPhysicalSimulator::CreateConvexHulls(Object& object)
	{
		//	if this collision mesh than we use it
		if (object.IsCollisionVolume())
		{
			//	get mesh
			const Mesh* mesh = object.GetMesh();
			//	if no mesh -> panic
			if (!mesh)
			{
				out_error() << L"Can't build concave shape. No mesh in " + object.GetName() << std::endl;
				return;
			}
			//	build collision shape
			btConvexHullShape* bullet_shape = new btConvexHullShape((btScalar*)&mesh->m_vertices[0], mesh->m_vertices.size(), sizeof(mesh->m_vertices[0]));
			m_collision_shapes.push_back(bullet_shape);

			//	create BulletShapeBody
			BulletShapeBody* shape_body = new BulletShapeBody;
			shape_body->SetCollisionShape(bullet_shape);
			
			//	save shape body in the object
			object.SetShapeBody(shape_body);
		}

		for each (auto child in object.GetChildren())
		{
			CreateConvexHulls(*child.get());
		}
	}

	void BulletPhysicalSimulator::CombineConvexHulls(btCompoundShape* result, Object& object, const Math::mat4& parent)
	{
		ShapeBody* body = object.GetShapeBody();
		if (body)
		{
			BulletShapeBody* shape_body = static_cast<BulletShapeBody*>(body);
			btTransform transform;
			transform.setFromOpenGLMatrix(&(parent*object.GetLocalMatrix())[0]);
			result->addChildShape(transform, shape_body->GetCollisionShape());
		}

		for each (auto child in object.GetChildren())
		{
			CombineConvexHulls(result, *child.get(), parent*object.GetLocalMatrix());
		}
	}

	void BulletPhysicalSimulator::CreateDynamicShapeBody(Object& object)
	{		
		//	create for each collision volume collision shape
		CreateConvexHulls(object);

		//	create compound shape
		btCompoundShape* bullet_shape = new btCompoundShape;
		m_collision_shapes.push_back(bullet_shape);
		//	make compound shape
		CombineConvexHulls(bullet_shape, object, Math::mat4::CreateIdentity());	

		BulletShapeBody* final_shape_body = new BulletShapeBody;
		final_shape_body->SetCollisionShape(bullet_shape);
		object.SetShapeBody(final_shape_body);
	}

	RigidBody* BulletPhysicalSimulator::CreateRigidBody(RigidBodyDesc& desc)
	{
		if (desc.m_is_character)
		{
			btTransform startTransform;
			startTransform.setIdentity ();
			startTransform.setFromOpenGLMatrix(&desc.m_initial_position[0]);

			btPairCachingGhostObject* m_ghostObject = new btPairCachingGhostObject();
			m_ghostObject->setWorldTransform(startTransform);
			m_broad_phase_interface->getOverlappingPairCache()->setInternalGhostPairCallback(new btGhostPairCallback());
						
			btScalar characterHeight = 1.0;
			btScalar characterWidth = 0.5;
			btConvexShape* capsule = new btCapsuleShape(characterWidth,characterHeight);			
			
			m_ghostObject->setCollisionShape(capsule);			
			m_ghostObject->getWorldTransform().setOrigin(btVector3(0, 1, 0));
			m_ghostObject->setCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT);
			
			btScalar stepHeight = btScalar(0.35);
			btKinematicCharacterController* m_character = new btKinematicCharacterController(m_ghostObject, capsule, stepHeight);

			///only collide with static for now (no interaction with dynamic objects)
			m_dynamics_world->addCollisionObject(m_ghostObject,btBroadphaseProxy::CharacterFilter, btBroadphaseProxy::StaticFilter|btBroadphaseProxy::DefaultFilter);

			m_dynamics_world->addAction(m_character);

			BulletRigidBody* body = new BulletRigidBody;
			body->SetCollisionObject(m_ghostObject);
			return body;
		}
		else
		{
			btTransform transform;
			transform.setFromOpenGLMatrix(&desc.m_initial_position[0]);
			btDefaultMotionState* motion_state = new btDefaultMotionState(transform);

			btVector3 inertia(0,0,0);
			btCollisionShape* bullet_shape = 0;
			if (desc.m_shape)
			{
				BulletShapeBody* shape = static_cast<BulletShapeBody*>(desc.m_shape);
				bullet_shape = shape->GetCollisionShape();
				bullet_shape->calculateLocalInertia(desc.m_mass, inertia);
			}

			btRigidBody::btRigidBodyConstructionInfo info(desc.m_mass, motion_state, bullet_shape, inertia);
			btRigidBody* bullet_body = new btRigidBody(info);

			m_dynamics_world->addRigidBody(bullet_body);//, desc.m_group, desc.m_mask);

			BulletRigidBody* body = new BulletRigidBody;
			body->SetCollisionObject(bullet_body);

			return body;
		}
	}

	void BulletPhysicalSimulator::Init()
	{
		m_collision_configuration.reset(new btDefaultCollisionConfiguration);
		m_dispatcher.reset(new btCollisionDispatcher(m_collision_configuration.get()));
		m_broad_phase_interface.reset(new btDbvtBroadphase());
		m_solver.reset(new btSequentialImpulseConstraintSolver());
		m_dynamics_world.reset(new btDiscreteDynamicsWorld(m_dispatcher.get(),
			m_broad_phase_interface.get(),
			m_solver.get(),
			m_collision_configuration.get()));

		m_dynamics_world->setGravity(btVector3(0, -9.8f, 0));
	}

	void BulletPhysicalSimulator::SetGravity(const Math::Vector3<float>& g)
	{
		btVector3 v(g.X(), g.Y(), g.Z());
		m_dynamics_world->setGravity(v);
	}

	void BulletPhysicalSimulator::Clear()
	{

		//	remove the rigidbodies from the dynamics world and delete them
		for (int i = m_dynamics_world->getNumCollisionObjects()-1; i >= 0; ++i)
		{
			btCollisionObject* object = m_dynamics_world->getCollisionObjectArray()[i];
			btRigidBody* body = btRigidBody::upcast(object);
			if (body && body->getMotionState())
			{
				delete body->getMotionState();
			}
			m_dynamics_world->removeCollisionObject(object);
			delete object;
		}

		//	delete collision shapes
		for (int i = 0; i < m_collision_shapes.size(); ++i)
		{
			btCollisionShape* shape = m_collision_shapes[i];
			m_collision_shapes[i] = 0;
			delete shape;
		}

		m_dynamics_world.reset(0);
		m_solver.reset(0);
		m_broad_phase_interface.reset(0);
		m_dispatcher.reset(0);
		m_collision_configuration.reset(0);

		m_collision_shapes.clear();
	}

	BulletPhysicalSimulator::~BulletPhysicalSimulator()
	{
		Clear();
	}

	void BulletPhysicalSimulator::SetRender(void* drawer)
	{
		m_dynamics_world->setDebugDrawer((btIDebugDraw*)(drawer));		
	}

	void BulletPhysicalSimulator::Draw()
	{
		m_dynamics_world->debugDrawWorld();
	}
};
