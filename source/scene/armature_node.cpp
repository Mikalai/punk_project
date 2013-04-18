#include "armature_node.h"
#include "../virtual/skinning/armature.h"

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
		Node::Save(stream);

		bool flag = m_armature != 0;
		stream.write((char*)&flag, sizeof(flag));
		if (flag)
		{
			m_armature->GetName().Save(stream);
		}

		return true;
	}

	bool ArmatureNode::Load(std::istream& stream)
	{
		Node::Load(stream);

		bool flag = false;
		stream.read((char*)&flag, sizeof(flag));
		if (flag)
		{
			System::string name;
			name.Load(stream);
			m_armature = Virtual::Armature::find(name);
		}

		return true;
	}

	ArmatureNode* ArmatureNode::CreateFromFile(const System::string& path)
	{
		std::ifstream stream(path.ToStdString().c_str(), std::ios::binary);
		if (!stream.is_open())
			throw System::PunkInvalidArgumentException(L"Can't open file " + path);
		return CreateFromStream(stream);
	}

	ArmatureNode* ArmatureNode::CreateFromStream(std::istream& stream)
	{
		std::unique_ptr<ArmatureNode> node(new ArmatureNode);
		node->Load(stream);
		return node.release();
	}

	void ArmatureNode::SetArmature(Virtual::Armature* value)
	{
		m_armature = value;
	}

	Virtual::Armature* ArmatureNode::GetArmature()
	{
		return m_armature;
	}

	bool ArmatureNode::Apply(AbstractVisitor* visitor)
	{
		return visitor->Visit(this);
	}
}
