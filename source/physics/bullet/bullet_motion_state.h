#ifndef _H_PUNK_PHYSICS_BULLET_MOTION_STATE
#define _H_PUNK_PHYSICS_BULLET_MOTION_STATE

#ifdef USE_BULLET_PHYSICS

#include <bullet/LinearMath/btMotionState.h>

namespace Scene { class TransformNode; }

namespace Physics
{
	class BulletMotionState : public btMotionState {
	public:
		BulletMotionState(const btTransform &initialpos, Scene::TransformNode* node);
		void SetNode(Scene::TransformNode *node);
		virtual ~BulletMotionState() override;
		virtual void getWorldTransform(btTransform &worldTrans) const= 0;
		virtual void setWorldTransform(const btTransform &worldTrans) override;

	protected:
		//	should not be deleted here
		Scene::TransformNode* m_visible_node;
		btTransform m_position;
	};
}

#endif  //  USE_BULLET_PHYSICS

#endif	//	_H_PUNK_PHYSICS_BULLET_MOTION_STATE
