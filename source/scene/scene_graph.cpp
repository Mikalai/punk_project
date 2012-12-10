#include "scene_graph.h"
#include "../opengl/renderable/renderable_data.h"
#include "../virtual/virtual.h"

IMPLEMENT_MANAGER(L"resource.scenes", L"*.scene_graph", System::Environment::Instance()->GetModelFolder(), System::ObjectType::SCENE_GRAPH, Scene, SceneGraph);

namespace Scene
{
	SceneGraph::SceneGraph()
	{
		SetType(System::ObjectType::SCENE_GRAPH);
		m_camera_node.Reset(new CameraNode);
	}

	void SceneGraph::SetActiveCamera(System::Proxy<Virtual::Cameras::Camera> value)
	{
		m_camera_node->SetCamera(value);
	}


	bool SceneGraph::Save(std::ostream& stream) const
	{
		if (!Object::Save(stream))
			return (out_error() << "Can't save scene graph" << std::endl, false);

		if (!System::GetFactory()->SaveToStream(stream, m_root))		
			return (out_error() << "Can't save root node" << std::endl, false);

		if (!System::GetFactory()->SaveToStream(stream, m_camera_node))		
			return (out_error() << "Can't save root node" << std::endl, false);

		return true;
	}

	bool SceneGraph::Load(std::istream& stream)
	{
		if (!Object::Load(stream))
			return (out_error() << "Can't load scene graph" << std::endl, false);

		m_root = System::GetFactory()->LoadFromStream(stream);
		if (!m_root.IsValid())
			return (out_error() << "Can't load root node" << std::endl, false);

		m_camera_node = System::GetFactory()->LoadFromStream(stream);
		if (!m_camera_node.IsValid())
			return (out_error() << "Can't load root node" << std::endl, false);

		return true;
	}

	System::Proxy<SceneGraph> SceneGraph::CreateFromFile(const System::string& path)
	{
		std::ifstream stream(path.Data(), std::ios::binary);
		if (!stream.is_open())
			return (out_error() << "Can't open file " << path << std::endl, System::Proxy<SceneGraph>(nullptr));
		return CreateFromStream(stream);
	}

	System::Proxy<SceneGraph> SceneGraph::CreateFromStream(std::istream& stream)
	{
		System::Proxy<SceneGraph> node(new SceneGraph);
		if (!node->Load(stream))
			return (out_error() << "Can't load node from file" << std::endl, System::Proxy<SceneGraph>(nullptr));
		return node;
	}
}
