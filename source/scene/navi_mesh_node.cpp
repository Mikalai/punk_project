#include "navi_mesh_node.h"

namespace Scene
{
    NaviMeshNode::NaviMeshNode()
        : m_navi_mesh(nullptr)
        , m_renderable(nullptr)
    {}

    NaviMeshNode::~NaviMeshNode()
    {
        safe_delete(m_renderable);
    }

    void NaviMeshNode::SetNaviMesh(AI::NaviMesh* value)
    {
        m_navi_mesh = value;
    }

    AI::NaviMesh* NaviMeshNode::GetNaviMesh() const
    {
        return m_navi_mesh;
    }

    bool NaviMeshNode::Apply(AbstractVisitor* visitor)
    {
        return visitor->Visit(this);
    }

    void NaviMeshNode::SetRenderable(GPU::Renderable* value)
    {
        if (m_renderable)
            delete m_renderable;
        m_renderable = value;
    }

    GPU::Renderable* NaviMeshNode::GetRenderable() const
    {
        return m_renderable;
    }

    Node* NaviMeshNode::Clone() const
    {
        NaviMeshNode* node = new NaviMeshNode;
        node->SetNaviMesh(m_navi_mesh);
        node->SetRenderable(m_renderable);
        CloneInternals(node);
        return node;
    }

}
