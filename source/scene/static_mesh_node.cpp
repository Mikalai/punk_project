#include "static_mesh_node.h"

IMPLEMENT_MANAGER(L"resource.static_mesh_nodes", L"*.static_mesh_node", System::Environment::Instance()->GetModelFolder(), System::ObjectType::STATIC_MESH_NODE, Scene, StaticMeshNode);

namespace Scene
{
	StaticMeshNode::StaticMeshNode()
	{
		SetType(System::ObjectType::STATIC_MESH_NODE);
	}

	bool StaticMeshNode::Save(std::ostream& stream) const
	{
		if (!GeometryNode::Save(stream))
			return (out_error() << "Can't save portal node" << std::endl, false);		
		return true;
	}

	bool StaticMeshNode::Load(std::istream& stream)
	{
		if (!GeometryNode::Load(stream))
			return (out_error() << "Can't load portal node" << std::endl, false);
		
		return true;
	}

	System::Proxy<StaticMeshNode> StaticMeshNode::CreateFromFile(const System::string& path)
	{
		std::ifstream stream(path.Data(), std::ios::binary);
		if (!stream.is_open())
			return (out_error() << "Can't open file " << path << std::endl, System::Proxy<StaticMeshNode>(nullptr));
		return CreateFromStream(stream);
	}

	System::Proxy<StaticMeshNode> StaticMeshNode::CreateFromStream(std::istream& stream)
	{
		System::Proxy<StaticMeshNode> node(new StaticMeshNode);
		if (!node->Load(stream))
			return (out_error() << "Can't load node from file" << std::endl, System::Proxy<StaticMeshNode>(nullptr));
		return node;
	}

	System::Proxy<Virtual::StaticGeometry> StaticMeshNode::GetStaticGeometry()
	{
		return GetGeometry();
	}

	bool StaticMeshNode::Apply(AbstractVisitor* visitor)
	{
		return visitor->Visit(this);
	}
}