#include "path_node.h"

namespace Scene
{
    PathNode::PathNode()
        : m_path(nullptr)
    {}

    PathNode::~PathNode()
    {}

    void PathNode::SetCurvePath(AI::CurvePath* value)
    {
        m_path = value;
    }

    AI::CurvePath* PathNode::GetCurvePath() const
    {
        return m_path;
    }

    bool PathNode::Apply(AbstractVisitor* visitor)
    {
        return visitor->Visit(this);
    }

    Node* PathNode::Clone() const
    {
        PathNode* node = new PathNode;
        node->SetCurvePath(m_path);
        CloneInternals(node);
        return node;
    }
}
