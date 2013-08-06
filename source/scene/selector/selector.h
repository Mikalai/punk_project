#ifndef PUNK_SCENE_SELECTOR_H
#define PUNK_SCENE_SELECTOR_H

#include <stack>
#include <vector>
#include "../../virtual/interface.h"
#include "../../ai/interface.h"
#include "../../system/object.h"
#include "../../config.h"
#include "../../math/mat4.h"
#include "../../math/line3d.h"
#include "selection.h"

namespace Scene
{
    class Node;
    class SceneGraph;

    class PUNK_ENGINE_API Selector
    {
    public:
        Selector(const Math::mat4& projection_matrix, const Math::mat4& view_matrix, const Math::vec2& cursor, const Math::vec2& screen_size, float m_selection_depth);
        virtual ~Selector();

        void Select(SceneGraph* scene);
        void Process(Node* node);
        bool ProcessChildren(Node *node);


    private:
        void UpdateViewRay();
        bool ProcessStaticGeometry(Node* node, Virtual::StaticGeometry* value);
        bool ProcessSkinGeometry(Node* node, Virtual::SkinGeometry* value);
        bool ProcessTransform(Node* node, Virtual::Transform* value);
        bool ProcessNaviMesh(Node* node, AI::NaviMesh* value);
        bool ProcessTerrainMesh(Node* node, Virtual::TerrainMesh* value);

    public:
        std::vector<Selection> m_bbox_selected;
        std::vector<Selection> m_bsphere_selected;
        std::vector<Selection> m_selections;

        Math::mat4 m_projection_matrix;
        Math::mat4 m_view_matrix;
        Math::vec2 m_cursor;
        Math::vec2 m_screen_size;
        Math::Line3D m_view_ray;
        float m_selection_depth;        
        std::stack<Math::mat4> m_local_transform;
        Math::vec3 m_world_screen_point;

        bool m_enable_frusum_culling;
        bool m_check_bounding_sphere;
        bool m_check_bounding_box;
        bool m_check_geometry;
    };
}

#endif // SELECTOR_H
