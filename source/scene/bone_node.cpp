#include "bone_node.h"
#include "../system/factory.h"
#include "../virtual/skinning/armature.h"

IMPLEMENT_MANAGER(L"resource.bone_nodes", L"*.bone_node", System::Environment::Instance()->GetModelFolder(), System::ObjectType::ARMATURE_NODE, Scene, BoneNode);


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
		if (!Node::Save(stream))
			return (out_error() << "Can't save geometry " << std::endl, false);				
		return true;
	}

	bool BoneNode::Load(std::istream& stream)
	{
		if (!Node::Load(stream))
			return (out_error() << "Can't save geometry " << std::endl, false);
		return true;
	}

	System::Proxy<BoneNode> BoneNode::CreateFromFile(const System::string& path)
	{
		std::ifstream stream(path.Data(), std::ios::binary);
		if (!stream.is_open())
			return (out_error() << "Can't open file " << path << std::endl, System::Proxy<BoneNode>(nullptr));
		return CreateFromStream(stream);
	}

	System::Proxy<BoneNode> BoneNode::CreateFromStream(std::istream& stream)
	{
		System::Proxy<BoneNode> node(new BoneNode);
		if (!node->Load(stream))
			return (out_error() << "Can't load node from file" << std::endl, System::Proxy<BoneNode>(nullptr));
		return node;
	}

	bool BoneNode::Apply(AbstractVisitor* visitor)
	{
		return visitor->Visit(this);
	}
}