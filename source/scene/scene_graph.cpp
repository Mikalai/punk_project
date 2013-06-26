#include "scene_graph.h"
#include "../gpu/opengl/renderable/module.h"
#include "../virtual/module.h"

namespace Scene
{
	SceneGraph::SceneGraph()
	{
	}

	SceneGraph::~SceneGraph()
	{
	}


	bool SceneGraph::Save(std::ostream& stream) const
	{
        System::CompoundObject::Save(stream);
		//System::GetFactory()->SaveToStream(stream, m_root);
		//System::GetFactory()->SaveToStream(stream, m_camera_node);
		return true;
	}

	bool SceneGraph::Load(std::istream& stream)
	{
        System::CompoundObject::Load(stream);
		//m_root = Cast<Node*>(System::GetFactory()->LoadFromStream(stream));
		//m_camera_node = Cast<CameraNode*>(System::GetFactory()->LoadFromStream(stream));
		return true;
	}
}
