//#ifndef _H_PUNK_PHYSICS_SIMPLE_MOTION_STATE
//#define _H_PUNK_PHYSICS_SIMPLE_MOTION_STATE
//
//#ifdef USE_SIMPLE_PHYSICS
//
//namespace Scene { class TransformNode; }
//
//namespace Physics
//{
//	class SimpleMotionState
//	{
//	public:
//		SimpleMotionState(const btTransform &initialpos, Scene::TransformNode* node);
//		void SetNode(Scene::TransformNode *node);
//		virtual ~SimpleMotionState();
//		virtual void getWorldTransform(btTransform &worldTrans) const;
//		virtual void setWorldTransform(const btTransform &worldTrans);
//
//	protected:
//		//	should not be deleted here
//		Scene::TransformNode* m_visible_node;
//		btTransform m_position;
//	};
//}
//
//#endif  //  USE_BULLET_PHYSICS
//
//#endif	//	_H_PUNK_PHYSICS_BULLET_MOTION_STATE
