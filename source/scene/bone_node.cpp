#include "bone_node.h"
#include "../system/factory.h"
#include "../virtual/skinning/armature.h"


namespace Scene
{
	BoneNode::BoneNode()
	{
		SetType(System::ObjectType::BONE_NODE);
	}

	BoneNode::~BoneNode()
	{
	}

	bool BoneNode::Save(std::ostream& stream) const
	{
		Node::Save(stream);
		return true;
	}

	bool BoneNode::Load(std::istream& stream)
	{
		Node::Load(stream);
		return true;
	}

	BoneNode* BoneNode::CreateFromFile(const System::string& path)
	{
		std::ifstream stream(path.Data(), std::ios::binary);
		if (!stream.is_open())
			throw System::PunkInvalidArgumentException(L"Can't open file " + path);
		return CreateFromStream(stream);
	}

	BoneNode* BoneNode::CreateFromStream(std::istream& stream)
	{
		std::unique_ptr<BoneNode> node(new BoneNode);
		node->Load(stream);
		return node.release();
	}

	bool BoneNode::Apply(AbstractVisitor* visitor)
	{
		return visitor->Visit(this);
	}
}