//#ifdef USE_SIMPLE_PHYSICS
//
//#include "simple_motion_state.h"
//#include "../../scene/module.h"
//
//namespace Physics
//{
//BulletMotionState::BulletMotionState(const btTransform &initialpos, Scene::TransformNode* node)
//    : m_visible_node(node)
//    , m_position(initialpos)
//{}
//
//BulletMotionState::~BulletMotionState()
//{
//    m_visible_node = nullptr;
//}
//
//void BulletMotionState::SetNode(Scene::TransformNode *node)
//{
//    m_visible_node = node;
//}
//
//void BulletMotionState::getWorldTransform(btTransform &worldTrans) const
//{
//    worldTrans = m_position;
//}
//
//void BulletMotionState::setWorldTransform(const btTransform &worldTrans)
//{
//    if (nullptr == m_visible_node)
//        return; // silently return before we set a node
//    Math::mat4 m;
//    worldTrans.getOpenGLMatrix(&m[0]);
//    m_visible_node->SetLocalMatrix(m);
//}
//}
//
//#endif // USE_SIMPLE_PHYSICS
