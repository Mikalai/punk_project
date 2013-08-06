#include "selector.h"
#include "../scene_graph.h"
#include "../../ai/module.h"
#include "../../math/perspective_decoder.h"
#include "../../virtual/module.h"

namespace Scene
{
    Selector::Selector(const Math::mat4 &projection_matrix, const Math::mat4 &view_matrix, const Math::vec2 &cursor, const Math::vec2 &screen_size, float selection_depth)
        : m_projection_matrix(projection_matrix)
        , m_view_matrix(view_matrix)
        , m_cursor(cursor)
        , m_screen_size(screen_size)
        , m_selection_depth(selection_depth)
        , m_check_bounding_box(true)
        , m_check_bounding_sphere(true)
        , m_check_geometry(true)
    {
        UpdateViewRay();
    }

    Selector::~Selector()
    {}

    void Selector::Select(SceneGraph *scene)
    {
        for (auto object : *scene)
        {
            Scene::Node* node = As<Scene::Node*>(object);
            if (!node)
                continue;
            Process(node);
        }
    }

    void Selector::Process(Node *node)
    {
        System::Object* o = node->GetData();
        if (o)
        {
            auto type = o->GetType();
            if (type->IsEqual(&Virtual::StaticGeometry::Info.Type))
                ProcessStaticGeometry(node, (Virtual::StaticGeometry*)o);
            else if (type->IsEqual(&Virtual::SkinGeometry::Info.Type))
                ProcessSkinGeometry(node, (Virtual::SkinGeometry*)o);
            else if (type->IsEqual(&Virtual::Transform::Info.Type))
                ProcessTransform(node, (Virtual::Transform*)o);
            else if (type->IsEqual(&AI::NaviMesh::Info.Type))
                ProcessNaviMesh(node, (AI::NaviMesh*)0);
            else if (type->IsEqual(&Virtual::TerrainMesh::Info.Type))
                ProcessTerrainMesh(node, (Virtual::TerrainMesh*)o);
            else
                ProcessChildren(node);
        }
        else
        {
            ProcessChildren(node);
        }
    }

    void Selector::UpdateViewRay()
    {
        //  TODO: Maybe should be placed in frustum, or somehere else, because it depends greatly
        //  on the projection matrix

        Math::PerspectiveDecoder decoder(m_projection_matrix);
        float x = decoder.GetWidthToHeightAspectRatio()*( -1 + 2.0f * m_cursor.X() / m_screen_size.X());
        float y = (-1 + 2.0f * m_cursor.Y() / m_screen_size.Y());

        auto m = m_view_matrix.Inversed();
        Math::vec3 origin = m * Math::vec3(0,0,0);
        auto vv = m * Math::vec4(x, y, -1.0f / tan(decoder.GetFovY() / 2.0f), 1);
        Math::vec3 destination(vv[0] / vv[3], vv[1] / vv[3], vv[2] / vv[3]);
        m_world_screen_point = destination;
        m_view_ray.SetOriginDestination(origin, origin + (destination - origin).Normalized() * m_selection_depth);
    }

    bool Selector::ProcessStaticGeometry(Node *node, Virtual::StaticGeometry *geom)
    {        
        if (geom)
        {
            if (geom->GetCpuCache().IsOnCpu())
            {
                bool has_bsphere = false;
                bool has_bbox = false;
                Math::Line3D line = m_local_transform.top().Inversed() * m_view_ray;
                if (m_check_bounding_sphere)
                {
                    const Math::BoundingSphere& sphere = geom->GetBoundingSphere();
                    Math::vec3 p1, p2;
                    Math::Relation r = Math::CrossLineSphere(line, sphere, p1, p2);
                    if (r == Math::Relation::INTERSECT_2)
                    {
                        std::vector<Math::vec3> p(2);
                        p[0]= m_local_transform.top() * p1;
                        p[1] = m_local_transform.top() * p2;
                        Selection s;
                        s.SetPoints(p);
                        s.SetType(SelectionType::BoundingSphere);
                        s.SetObject(node);
                        m_selections.push_back(s);
                        has_bsphere = true;
                    }
                    if (r == Math::Relation::INTERSECT_1)
                    {
                        std::vector<Math::vec3> p(1);
                        p[0]= m_local_transform.top() * p1;
                        Selection s;
                        s.SetPoints(p);
                        s.SetType(SelectionType::BoundingSphere);
                        s.SetObject(node);
                        m_selections.push_back(s);
                        has_bsphere = true;
                    }
                }
                if (m_check_bounding_box)
                {
                    if (has_bsphere || !m_check_bounding_sphere)
                    {
                        const Math::BoundingBox& bbox = geom->GetBoundingBox();
                        Math::vec3 p;
                        Math::Relation r = Math::CrossLineBoundingBox(line, bbox, p);
                        if (r == Math::Relation::INTERSECT)
                        {
                            std::vector<Math::vec3> points(1);
                            points[0] = m_local_transform.top() * p;
                            Selection s;
                            s.SetPoints(points);
                            s.SetType(SelectionType::BoundingBox);
                            s.SetObject(node);
                            m_selections.push_back(s);
                            has_bbox = true;
                        }
                    }
                }
                if (m_check_geometry)
                {
                    if (has_bbox || !m_check_bounding_box)
                    {
                        std::vector<Math::vec3> points;
                        std::vector<size_t> faces;
                        Math::Relation r = Math::CrossLineTriangles(line, geom->GetCpuCache().GetVertices(), geom->GetCpuCache().GetFaces(), points, faces);
                        if (r == Math::Relation::INTERSECT)
                        {
                            //  return points to the worlds coordinate system
                            for (auto& p : points)
                            {
                                p = m_local_transform.top() * p;
                            }
                            Selection selection;
                            selection.SetPoints(points);
                            selection.SetFaces(faces);
                            selection.SetType(SelectionType::Geometry);
                            selection.SetObject(node);
                            m_selections.push_back(selection);
                        }
                    }
                }
            }
        }
        return ProcessChildren(node);
    }

    bool Selector::ProcessSkinGeometry(Node *node, Virtual::SkinGeometry *value)
    {
        return ProcessChildren(node);
    }

    bool Selector::ProcessTransform(Node *node, Virtual::Transform *value)
    {
        if (m_local_transform.empty())
            m_local_transform.push(value->Get());
        else
            m_local_transform.push(m_local_transform.top() * value->Get());
        bool result = ProcessChildren(node);
        m_local_transform.pop();
        return result;
    }

    bool Selector::ProcessTerrainMesh(Node *node, Virtual::TerrainMesh *terrain)
    {        
        if (terrain)
        {
            Virtual::StaticGeometry* geom = terrain->GetGeometry();
            if (geom)
            {
                Math::Line3D line = m_local_transform.top().Inversed() * m_view_ray;
                std::vector<Math::vec3> points;
                std::vector<size_t> faces;
                Math::Relation r = Math::CrossLineTriangles(line, geom->GetCpuCache().GetVertices(), geom->GetCpuCache().GetFaces(), points, faces);
                if (r == Math::Relation::INTERSECT)
                {
                    Selection selection;
                    //  return points to the worlds coordinate system
                    for (auto& p : points)
                    {
                        p = m_local_transform.top() * p;
                    }
                    selection.SetPoints(points);
                    selection.SetFaces(faces);
                    selection.SetObject(node);
                    m_selections.push_back(selection);
                }
            }
        }
        ProcessChildren(node);
        return true;
    }

    bool Selector::ProcessNaviMesh(Node *node, AI::NaviMesh *mesh)
    {     
        if (mesh)
        {
            auto line = m_local_transform.top().Inversed() * m_view_ray;
            std::vector<Math::vec3> points;
            std::vector<size_t> faces;
            Math::Relation res = Math::CrossLineTriangles(line, mesh->GetPoints(), mesh->GetFaces(), points, faces);
            if (res == Math::Relation::INTERSECT)
            {
                //  return points to the worlds coordinate system
                for (auto& p : points)
                {
                    p = m_local_transform.top() * p;
                }
                Selection selection;
                selection.SetPoints(points);
                selection.SetFaces(faces);
                selection.SetObject(node);
                m_selections.push_back(selection);
            }
        }
        ProcessChildren(node);
        return true;
    } 

    bool Selector::ProcessChildren(Scene::Node *node)
    {
        for (auto object : *node)
        {
            Scene::Node* node = As<Scene::Node*>(object);
            if (!node)
                continue;
            Process(node);
        }
        return true;
    }

}
