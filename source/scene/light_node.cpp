#include "../system/logger.h"
#include "light_node.h"

namespace Scene
{
	LightNode::LightNode()
	{
		SetType(System::ObjectType::LIGHT_NODE);
	}

	bool LightNode::Save(std::ostream& stream) const
	{
		if (!Node::Save(stream))
			return (out_error() << "Can't save light node" << std::endl, false);
		
		//if (!System::Factory::Instance()->SaveToStream(stream, m_light_set))
		//	return (out_error() << "Can't save light node" << std::endl, false);

		return true;
	}

	bool LightNode::Load(std::istream& stream) 
	{
		if (!Node::Load(stream))
			return (out_error() << "Can't load light node" << std::endl, false);

		//m_light_set = System::Factory::Instance()->LoadFromStream(stream);
		//if (!m_light_set.IsValid())
		//	return (out_error() << "Can't load light node" << std::endl, false);

		return true;
	}

	//System::Proxy<LightNode> LightNode::CreateFromFile(const System::string& path)
	//{
	//	std::ifstream stream(path.Data(), std::ios::binary);
	//	if (!stream.is_open())
	//		return (out_error() << "Can't open file " << path << std::endl, System::Proxy<LightNode>(nullptr));
	//	return CreateFromStream(stream);
	//}

	//System::Proxy<LightNode> LightNode::CreateFromStream(std::istream& stream)
	//{
	//	System::Proxy<LightNode> node(new LightNode);
	//	if (!node->Load(stream))
	//		return (out_error() << "Can't load node from file" << std::endl, System::Proxy<LightNode>(nullptr));
	//	return node;
	//}

	bool LightNode::Apply(AbstractVisitor* visitor)
	{
		return visitor->Visit(this);
	}
}