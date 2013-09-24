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
}
