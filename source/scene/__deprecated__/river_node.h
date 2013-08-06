#ifndef RIVER_NODE_H
#define RIVER_NODE_H

#include "node.h"

namespace Virtual
{
    class River;
}

namespace Scene
{
    class RiverNode : public Node
    {
    public:
        RiverNode();
        virtual ~RiverNode();
        bool Apply(AbstractVisitor* visitor);
        void SetRiver(Virtual::River* river);
        Virtual::River* GetRiver() const;

        virtual Node* Clone() const override;
    private:
        Virtual::River* m_river;
    };
}

#endif // RIVER_NODE_H
