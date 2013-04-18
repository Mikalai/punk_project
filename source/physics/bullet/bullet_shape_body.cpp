#ifdef USE_BULLET_PHYSICS

#include "../../virtual/module.h"
#include "btBulletCollisionCommon.h"
#include "btBulletDynamicsCommon.h"
#include "bullet_shape_body.h"

namespace Physics
{
	BulletShapeBody::BulletShapeBody()
		: m_shape(nullptr)
	{}

	void BulletShapeBody::InitConvexHull(Virtual::Geometry* value, bool auto_cache)
	{
		if (m_shape)
			delete m_shape;
		const Virtual::Geometry::Vertices& v = value->GetVertexArray();
		m_shape = new btConvexHullShape((btScalar*)&v[0], v.size(), sizeof(v[0]));

		if (auto_cache)
			value->SetPhysicsCache(this);
	}

	void BulletShapeBody::InitBox(float dim_x, float dim_y, float dim_z)
	{
		if (m_shape)
			delete m_shape;
		m_shape = new btBoxShape(btVector3(dim_x, dim_y, dim_z));
	}

	void BulletShapeBody::InitSphere(float radius)
	{
		if (m_shape)
			delete m_shape;
		m_shape = new btSphereShape(radius);
	}

	void BulletShapeBody::InitPlain(float height)
	{
		if (m_shape)
			delete m_shape;
		m_shape = new btStaticPlaneShape(btVector3(0,1,0), height);
	}

	BulletShapeBody::~BulletShapeBody()
	{
		if (m_shape)
		{
			delete m_shape;
			m_shape = 0;
		}
	}
}

#endif // USE_BULLET_PHYSICS
