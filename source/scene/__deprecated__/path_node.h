#ifndef PATH_NODE_H
#define PATH_NODE_H

#include "node.h"

namespace AI
{
    class CurvePath;
}

namespace Scene
{
    class PUNK_ENGINE_API PathNode : public Node
    {
    public:
        PathNode();
        virtual ~PathNode();
        virtual bool Apply(AbstractVisitor* visitor) override;
        void SetCurvePath(AI::CurvePath* value);
        AI::CurvePath* GetCurvePath() const;

        virtual Node* Clone() const override;

    private:
        AI::CurvePath* m_path;

    };
}

#endif // PATH_NODE_H
