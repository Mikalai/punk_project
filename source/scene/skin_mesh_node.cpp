#include "skin_mesh_node.h"
#include "../system/errors/module.h"

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

	SkinMeshNode* SkinMeshNode::CreateFromFile(const System::string& path)
	{
		std::ifstream stream(path.ToStdString().c_str(), std::ios::binary);
		if (!stream.is_open())
			throw System::PunkException(L"Can't open file " + path);
		return CreateFromStream(stream);
	}

	SkinMeshNode* SkinMeshNode::CreateFromStream(std::istream& stream)
	{
		std::unique_ptr<SkinMeshNode> node(new SkinMeshNode);
		node->Load(stream);
		return node.release();
	}

	Virtual::SkinGeometry* SkinMeshNode::GetSkinGeometry()
	{
		return dynamic_cast<Virtual::SkinGeometry*>(GetGeometry());
	}

	bool SkinMeshNode::Apply(AbstractVisitor* visitor)
	{
		return visitor->Visit(this);
	}
}
