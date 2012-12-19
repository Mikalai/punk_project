#include "armature_node.h"
#include "../system/factory.h"
#include "../virtual/skinning/armature.h"

IMPLEMENT_MANAGER(L"resource.armature_nodes", L"*.armature_node", System::Environment::Instance()->GetModelFolder(), System::ObjectType::ARMATURE_NODE, Scene, ArmatureNode);


namespace Scene
{
	ArmatureNode::ArmatureNode()
	{
		SetType(System::ObjectType::ARMATURE_NODE);
	}

	ArmatureNode::~ArmatureNode()
	{
	}

	bool ArmatureNode::Save(std::ostream& stream) const
	{
		if (!Node::Save(stream))
			return (out_error() << "Can't save geometry " << std::endl, false);
				
		if (!System::GetFactory()->SaveToStream(stream, m_armature))
			return (out_error() << "Can't save geometry " << std::endl, false);

		return true;
	}

	bool ArmatureNode::Load(std::istream& stream)
	{
		if (!Node::Load(stream))
			return (out_error() << "Can't save geometry " << std::endl, false);

		m_armature = System::GetFactory()->LoadFromStream(stream);
		if (!m_armature.IsValid())
			return false;

		return true;
	}

	System::Proxy<ArmatureNode> ArmatureNode::CreateFromFile(const System::string& path)
	{
		std::ifstream stream(path.Data(), std::ios::binary);
		if (!stream.is_open())
			return (out_error() << "Can't open file " << path << std::endl, System::Proxy<ArmatureNode>(nullptr));
		return CreateFromStream(stream);
	}

	System::Proxy<ArmatureNode> ArmatureNode::CreateFromStream(std::istream& stream)
	{
		System::Proxy<ArmatureNode> node(new ArmatureNode);
		if (!node->Load(stream))
			return (out_error() << "Can't load node from file" << std::endl, System::Proxy<ArmatureNode>(nullptr));
		return node;
	}

	void ArmatureNode::SetArmature(System::Proxy<Virtual::Armature> value)
	{
		m_armature = value;
	}

	System::Proxy<Virtual::Armature> ArmatureNode::GetArmature() 
	{
		return m_armature;
	}

	bool ArmatureNode::Apply(AbstractVisitor* visitor)
	{
		return visitor->Visit(this);
	}
}