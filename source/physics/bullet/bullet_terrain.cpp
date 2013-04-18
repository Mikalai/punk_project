#ifdef USE_BULLET_PHYSICS

#include <bullet/btBulletCollisionCommon.h>
#include <bullet/BulletCollision/CollisionShapes/btHeightfieldTerrainShape.h>
#include "../../math/module.h"
#include "bullet_terrain.h"
#include "bullet_rigid_body.h"
#include "../../virtual/terrain/module.h"

namespace Physics
{
	BulletTerrain::BulletTerrain()
		: m_data(nullptr)
		, m_heightfieldShape(nullptr)
		, m_body(nullptr)
	{}

	BulletTerrain::~BulletTerrain()
	{
		Clear();
	}

	void BulletTerrain::UpdateData(const Virtual::TerrainView* view)
	{
		Clear();

		const float* data = reinterpret_cast<const float*>(view->GetBackViewData());
		btAssert(data != nullptr && " no data in the terrain view");

		int width = view->GetViewSize();
		int height = view->GetViewSize();
		float min_height = std::numeric_limits<float>::max();
		float max_height = std::numeric_limits<float>::min();
		for (int i = 0; i < width*height; ++i)
		{
			if (min_height > data[i])
				min_height = data[i];
			if (max_height < data[i])
				max_height = data[i];
		}

		if (max_height < -min_height) {
			max_height = -min_height;
		}
		if (min_height > -max_height) {
			min_height = -max_height;
		}
		//	pack in auto ptr not to loose memory if exception
		std::unique_ptr<btHeightfieldTerrainShape> temp_shape(new btHeightfieldTerrainShape(width, height, data, 1, min_height, max_height, 1, PHY_FLOAT, false));

		btAssert(temp_shape.get() && "null heightfield");

		// set origin to middle of heightfield
		btTransform tr;
		tr.setIdentity();
		tr.setOrigin(btVector3(view->GetBackPosition().X(), 0, view->GetBackPosition().Y()));

		//	pack in auto ptr not to loose memory if exception
		std::unique_ptr<BulletRigidBody> temp_body(new BulletRigidBody());

		RigidBodyDesc desc;
		desc.m_group = 0;
		desc.m_initial_position = Math::mat4::CreateTranslate(view->GetBackPosition().X(), 0, view->GetBackPosition().Y());
		desc.m_is_character = false;
		desc.m_mask = 0;
		desc.m_mass = 0;
		desc.m_shape = temp_shape.get();
		temp_body->Init(desc);

		//	unpack data from auto ptrs
		m_heightfieldShape = temp_shape.release();
		m_body = temp_body.release();
	}

	void BulletTerrain::EnterWorld(btDiscreteDynamicsWorld* world)
	{
		if (!m_body)
			throw System::PunkInvalidArgumentException(L"Terrain can't enter physical world because it has no data");
		m_body->EnterWorld(world);
	}

	void BulletTerrain::Leave()
	{
		if (!m_body)
			throw System::PunkInvalidArgumentException(L"Terrain can't leave physical world because it has no data");
		m_body->LeaveWorld();
	}

	void BulletTerrain::Clear()
	{
		if (m_body)
			safe_delete(m_body);
		if (m_heightfieldShape)
			safe_delete(m_heightfieldShape);
	}
}

#endif // USE_BULLET_PHYSICS
