#include "skin_mesh_node.h"

IMPLEMENT_MANAGER(L"resource.skin_mesh_nodes", L"*.skin_mesh_node", System::Environment::Instance()->GetModelFolder(), System::ObjectType::SKINE_MESH_NODE, Scene, SkinMeshNode);

namespace Scene
{
	SkinMeshNode::SkinMeshNode()
	{
		SetType(System::ObjectType::SKIN_MESH_NODE);
	}

	bool SkinMeshNode::Save(std::ostream& stream) const
	{
		if (!GeometryNode::Save(stream))
			return (out_error() << "Can't save portal node" << std::endl, false);		
		return true;
	}

	bool SkinMeshNode::Load(std::istream& stream)
	{
		if (!GeometryNode::Load(stream))
			return (out_error() << "Can't load portal node" << std::endl, false);
		
		return true;
	}

	System::Proxy<SkinMeshNode> SkinMeshNode::CreateFromFile(const System::string& path)
	{
		std::ifstream stream(path.Data(), std::ios::binary);
		if (!stream.is_open())
			return (out_error() << "Can't open file " << path << std::endl, System::Proxy<SkinMeshNode>(nullptr));
		return CreateFromStream(stream);
	}

	System::Proxy<SkinMeshNode> SkinMeshNode::CreateFromStream(std::istream& stream)
	{
		System::Proxy<SkinMeshNode> node(new SkinMeshNode);
		if (!node->Load(stream))
			return (out_error() << "Can't load node from file" << std::endl, System::Proxy<SkinMeshNode>(nullptr));
		return node;
	}

	System::Proxy<Virtual::SkinGeometry> SkinMeshNode::GetSkinGeometry()
	{
		return GetGeometry();
	}

	bool SkinMeshNode::Apply(AbstractVisitor* visitor)
	{
		return visitor->Visit(this);
	}
}