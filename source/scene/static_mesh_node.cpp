#include "static_mesh_node.h"

namespace Scene
{
	StaticMeshNode::StaticMeshNode()
	{
		SetType(System::ObjectType::STATIC_MESH_NODE);
	}

	bool StaticMeshNode::Save(std::ostream& stream) const
	{
		GeometryNode::Save(stream);
		return true;
	}

	bool StaticMeshNode::Load(std::istream& stream)
	{
		GeometryNode::Load(stream);		
		return true;
	}

	StaticMeshNode* StaticMeshNode::CreateFromFile(const System::string& path)
	{
		std::ifstream stream(path.Data(), std::ios::binary);
		if (!stream.is_open())
			throw System::PunkInvalidArgumentException(L"Can't open file " + path);
		return CreateFromStream(stream);
	}

	StaticMeshNode* StaticMeshNode::CreateFromStream(std::istream& stream)
	{
		std::unique_ptr<StaticMeshNode> node(new StaticMeshNode);
		node->Load(stream);
		return node.release();
	}

	Virtual::StaticGeometry* StaticMeshNode::GetStaticGeometry()
	{
		return Cast<Virtual::StaticGeometry*>(GetGeometry());
	}

	bool StaticMeshNode::Apply(AbstractVisitor* visitor)
	{
		return visitor->Visit(this);
	}
}