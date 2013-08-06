#include "scene_graph.h"
#include "../gpu/opengl/renderable/module.h"
#include "../virtual/module.h"
#include "../engine_objects.h"

namespace Scene
{
    PUNK_OBJECT_REG(SceneGraph, "Scene.SceneGraph", PUNK_SCENE_GRAPH, &Node::Info.Type);

    SceneGraph::SceneGraph()
	{
        Info.Add(this);
	}

	SceneGraph::~SceneGraph()
	{
        Info.Remove(this);
	}

    const System::string SceneGraph::ToString() const
    {
        std::wstringstream stream;
        stream << L'[' << GetLocalIndex() << L' ' << Info.Type.GetName() << L']';
        return System::string(stream.str());
    }
}
