#include "sun_node.h"

namespace Scene
{
    SunNode::SunNode()
        : m_sun(nullptr)
    {
    }

    SunNode::~SunNode()
    {}

    void SunNode::SetSun(Virtual::Sun* value)
    {
        m_sun = value;
    }

    Virtual::Sun* SunNode::GetSun() const
    {
        return m_sun;
    }

    bool SunNode::Apply(AbstractVisitor *visitor)
    {
        return visitor->Visit(this);
    }

    Node* SunNode::Clone() const
    {
        SunNode* node = new SunNode;
        node->SetSun(m_sun);
        CloneInternals(node);
        return node;
    }
}
