#ifndef _H_PUNK_PHYSICS_BULLET_TERRAIN
#define _H_PUNK_PHYSICS_BULLET_TERRAIN
#define _STATIC_CPPLIB
#include "../../config.h"
#include "../../math/module.h"
#include <bullet/btBulletCollisionCommon.h>
#include <bullet/BulletCollision/CollisionShapes/btHeightfieldTerrainShape.h>


namespace Physics
{
	class PUNK_ENGINE BulletTerrain
	{
	public:
		BulletTerrain();
		virtual ~BulletTerrain(){}
		void UpdateData(void* data, unsigned width, unsigned height, float height_scale, const Math::vec3& up, const Math::vec3& position);
	private:
		float* m_data;
		btVector3 m_up_vector;
		btHeightfieldTerrainShape* m_heightfieldShape;
		btRigidBody* m_body;
	};
}

#endif	//	_H_PUNK_PHYSICS_BULLET_TERRAIN