#include "material_node.h"

namespace Scene
{
	MaterialNode::MaterialNode()
	{
		SetType(System::ObjectType::MATERIAL_NODE);
	}

	bool MaterialNode::Save(std::ostream& stream) const
	{
		if (!Node::Save(stream))
			return (out_error() << "Can't save light node" << std::endl, false);
		
		if (!System::Factory::Instance()->SaveToStream(stream, m_material))
			return (out_error() << "Can't save material in the material node" << std::endl, false);

		return true;
	}

	bool MaterialNode::Load(std::istream& stream) 
	{
		if (!Node::Load(stream))
			return (out_error() << "Can't load light node" << std::endl, false);

		m_material = System::Factory::Instance()->LoadFromStream(stream);
		if (!m_material.IsValid())
			return (out_error() << "Can't load material in the material node" << std::endl, false);

		return true;
	}

	System::Proxy<MaterialNode> MaterialNode::CreateFromFile(const System::string& path)
	{
		std::ifstream stream(path.Data(), std::ios::binary);
		if (!stream.is_open())
			return (out_error() << "Can't open file " << path << std::endl, System::Proxy<MaterialNode>(nullptr));
		return CreateFromStream(stream);
	}

	System::Proxy<MaterialNode> MaterialNode::CreateFromStream(std::istream& stream)
	{
		System::Proxy<MaterialNode> node(new MaterialNode);
		if (!node->Load(stream))
			return (out_error() << "Can't load node from file" << std::endl, System::Proxy<MaterialNode>(nullptr));
		return node;
	}

	bool MaterialNode::Apply(AbstractVisitor* visitor)
	{
		return visitor->Visit(this);
	}
}