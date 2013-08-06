#ifndef NAVI_MESH_NODE_H
#define NAVI_MESH_NODE_H

#include "node.h"

namespace AI
{
    class NaviMesh;
}

namespace Gpu
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

        void SetRenderable(Gpu::Renderable* value);
        Gpu::Renderable* GetRenderable() const;

        Node* Clone() const override;
    private:
        AI::NaviMesh* m_navi_mesh;
        Gpu::Renderable* m_renderable;
    };
}

#endif // NAVI_MESH_NODE_H
