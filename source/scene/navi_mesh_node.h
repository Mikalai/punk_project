#ifndef NAVI_MESH_NODE_H
#define NAVI_MESH_NODE_H

#include "node.h"

namespace AI
{
    class NaviMesh;
}

namespace GPU
{
    class Renderable;
}

namespace Scene
{
    class NaviMeshNode : public Node
    {
    public:
        NaviMeshNode();
        virtual ~NaviMeshNode();
        virtual bool Apply(AbstractVisitor *visitor) override;
        void SetNaviMesh(AI::NaviMesh* value);
        AI::NaviMesh* GetNaviMesh() const;

        void SetRenderable(GPU::Renderable* value);
        GPU::Renderable* GetRenderable() const;

        Node* Clone() const override;
    private:
        AI::NaviMesh* m_navi_mesh;
        GPU::Renderable* m_renderable;
    };
}

#endif // NAVI_MESH_NODE_H
