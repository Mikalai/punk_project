#include "scene_graph.h"
#include "../gpu/opengl/renderable/module.h"
#include "../virtual/module.h"

namespace Scene
{
	SceneGraph::SceneGraph()
	{
		SetType(System::ObjectType::SCENE_GRAPH);
		m_camera_node = new CameraNode;
		m_root = new Node;
	}

	SceneGraph::~SceneGraph()
	{
		safe_delete(m_camera_node);
		safe_delete(m_root);
	}

	void SceneGraph::SetActiveCamera(Virtual::Camera* value)
	{
		m_camera_node->SetCamera(value);
	}


	bool SceneGraph::Save(std::ostream& stream) const
	{
		Object::Save(stream);
		//System::GetFactory()->SaveToStream(stream, m_root);
		//System::GetFactory()->SaveToStream(stream, m_camera_node);
		return true;
	}

	bool SceneGraph::Load(std::istream& stream)
	{
		Object::Load(stream);
		//m_root = Cast<Node*>(System::GetFactory()->LoadFromStream(stream));
		//m_camera_node = Cast<CameraNode*>(System::GetFactory()->LoadFromStream(stream));
		return true;
	}

	SceneGraph* SceneGraph::CreateFromFile(const System::string& path)
	{
		std::ifstream stream(path.ToStdString().c_str(), std::ios::binary);
		if (!stream.is_open())
			throw System::PunkInvalidArgumentException(L"Can't open file " + path);
		return CreateFromStream(stream);
	}

	SceneGraph* SceneGraph::CreateFromStream(std::istream& stream)
	{
		std::unique_ptr<SceneGraph> node(new SceneGraph);
		node->Load(stream);
		return node.release();
	}
}
