#include "scene_graph.h"
#include "../utility/module.h"
#include "../gpu/opengl/renderable/module.h"
#include "../virtual/module.h"
#include "../engine_objects.h"

namespace Scene
{
    PUNK_OBJECT_REG(SceneGraph, "Scene.SceneGraph", PUNK_SCENE_GRAPH, SaveSceneGraph, LoadSceneGraph, &Node::Info.Type);

    SceneGraph::SceneGraph()
        : m_parser(new Utility::AsyncParser)
	{
        Info.Add(this);
	}

	SceneGraph::~SceneGraph()
	{
        delete m_parser;
        Info.Remove(this);
	}

    const System::string SceneGraph::ToString() const
    {
        std::wstringstream stream;
        stream << L'[' << GetLocalIndex() << L' ' << Info.Type.GetName() << L']' << std::endl;
        for (auto o : m_children)
        {
            stream << o->ToString() << std::endl;
        }
        return System::string(stream.str());
    }        

    Utility::AsyncParser* SceneGraph::AsyncParser()
    {
        return m_parser;
    }

    void SaveSceneGraph(System::Buffer *buffer, const System::Object *o)
    {
        SaveNode(buffer, o);
    }

    void LoadSceneGraph(System::Buffer *buffer, System::Object *o)
    {
        LoadNode(buffer, o);
    }


    void UpdateLight(Node* node, std::vector<Node*>& nodes)
    {
        if (!node)
            return;
        auto o = node->GetData();
        if (o)
        {
            if (o->GetType()->IsDerived(&Virtual::Light::Info.Type))
            {
                nodes.push_back(node);
            }
        }

        for (auto child : *node)
        {
            Node* n = Cast<Node*>(child);
            UpdateLight(n, nodes);
        }
    }

    void SceneGraph::UpdateLights()
    {
        UpdateLight(this, m_lights);
    }

    void SceneGraph::UpdateTransform()
    {
        UpdateUpToDown(this);
    }

    void SceneGraph::Update()
    {
        UpdateTransform();
        UpdateLights();
    }

    Node* SceneGraph::GetNearestLight(const Math::vec3 &point) const
    {
        if (m_lights.empty())
            return nullptr;
        size_t best = 0;
        for (size_t i = 1, max_i = m_lights.size(); i < max_i; ++i)
        {
            const auto& p1 = m_lights[i]->GlobalPosition();
            const auto& p2 = m_lights[best]->GlobalPosition();
            float a = (p1 - point).Length();
            float b = (p2 - point).Length();
            if (a < b)
                best = i;
        }
        return m_lights[best];
    }
}
