#include "river_node.h"

namespace Scene
{
    RiverNode::RiverNode()
        : m_river(nullptr)
    {
    }

    RiverNode::~RiverNode()
    {

    }

    void RiverNode::SetRiver(Virtual::River* river)
    {
        m_river = river;
    }

    Virtual::River* RiverNode::GetRiver() const
    {
        return m_river;
    }

    bool RiverNode::Apply(AbstractVisitor* visitor)
    {
        return visitor->Visit(this);
    }

    Node* RiverNode::Clone() const
    {
        RiverNode* node = new RiverNode;
        node->SetRiver(m_river);
        CloneInternals(node);
        return node;
    }
}
