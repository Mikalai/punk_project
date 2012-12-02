#include "transform_node.h"

namespace Scene
{
	TransformNode::TransformNode()
	{
		SetType(System::ObjectType::TRANSFORM_NODE);
	}

	bool TransformNode::Save(std::ostream& stream) const
	{
		if (!Node::Save(stream))
			return (out_error() << "Can't save TransformNode" << std::endl, false);
		
		if (!m_local.Save(stream))
			return (out_error() << "Can't save TransformNode" << std::endl, false);

		if (!m_global.Save(stream))
			return (out_error() << "Can't save TransformNode" << std::endl, false);

		return true;
	}

	bool TransformNode::Load(std::istream& stream)
	{
		if (!Node::Load(stream))
			return (out_error() << "Can't save TransformNode" << std::endl, false);
		
		if (!m_local.Load(stream))
			return (out_error() << "Can't save TransformNode" << std::endl, false);

		if (!m_global.Load(stream))
			return (out_error() << "Can't save TransformNode" << std::endl, false);

		return true;
	}

	System::Proxy<TransformNode> TransformNode::CreateFromFile(const System::string& path)
	{
		std::ifstream stream(path.Data(), std::ios::binary);
		if (!stream.is_open())
			return (out_error() << "Can't open file " << path << std::endl, System::Proxy<TransformNode>(nullptr));
		return CreateFromStream(stream);
	}

	System::Proxy<TransformNode> TransformNode::CreateFromStream(std::istream& stream)
	{
		System::Proxy<TransformNode> node(new TransformNode);
		if (!node->Load(stream))
			return (out_error() << "Can't load node from file" << std::endl, System::Proxy<TransformNode>(nullptr));
		return node;
	}

	bool TransformNode::Apply(AbstractVisitor* visitor)
	{
		return visitor->Visit(this);
	}
}