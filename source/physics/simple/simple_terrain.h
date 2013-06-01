//#ifdef USE_BULLET_PHYSICS
//
//#ifndef _H_PUNK_PHYSICS_BULLET_TERRAIN
//#define _H_PUNK_PHYSICS_BULLET_TERRAIN
//
//#include "../../config.h"
//#include <bullet/LinearMath/btVector3.h>
//
//namespace Virtual { class TerrainView; }
//
//class btCollisionObject;
//class btRigidBody;
//class btDiscreteDynamicsWorld;
//class btHeightfieldTerrainShape;
//
//namespace Physics
//{
//	class BulletRigidBody;
//
//	class PUNK_ENGINE_PUBLIC BulletTerrain
//	{
//	public:
//		BulletTerrain();
//		virtual ~BulletTerrain();
//		void UpdateData(const Virtual::TerrainView* view);
//		void EnterWorld(btDiscreteDynamicsWorld* world);
//		void Leave();
//		void Clear();
//	private:
//
//		btVector3 m_up_vector;
//		//	should be deleted in destructor
//		btHeightfieldTerrainShape* m_heightfieldShape;
//		BulletRigidBody* m_body;
//
//		//	should not be deleted in destructor
//		float* m_data;
//	};
//}
//
//#endif	//	_H_PUNK_PHYSICS_BULLET_TERRAIN
//
//#endif // USE_BULLET_PHYSICS
