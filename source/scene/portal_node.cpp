#include "portal_node.h"

namespace Scene
{
	PortalNode::PortalNode()
	{
		SetType(System::ObjectType::PORTAL_NODE);
	}

	bool PortalNode::Save(std::ostream& stream) const
	{
		if (!TransformNode::Save(stream))
			return (out_error() << "Can't save portal node" << std::endl, false);
		
		if (!m_portal.Save(stream))
			return (out_error() << "Can't save portal node" << std::endl, false);
		
		return true;
	}

	bool PortalNode::Load(std::istream& stream)
	{
		if (!TransformNode::Load(stream))
			return (out_error() << "Can't load portal node" << std::endl, false);
		
		if (!m_portal.Load(stream))
			return (out_error() << "Can't load portal node" << std::endl, false);
		
		return true;
	}

	System::Proxy<PortalNode> PortalNode::CreateFromFile(const System::string& path)
	{
		std::ifstream stream(path.Data(), std::ios::binary);
		if (!stream.is_open())
			return (out_error() << "Can't open file " << path << std::endl, System::Proxy<PortalNode>(nullptr));
		return CreateFromStream(stream);
	}

	System::Proxy<PortalNode> PortalNode::CreateFromStream(std::istream& stream)
	{
		System::Proxy<PortalNode> node(new PortalNode);
		if (!node->Load(stream))
			return (out_error() << "Can't load node from file" << std::endl, System::Proxy<PortalNode>(nullptr));
		return node;
	}

	bool PortalNode::Apply(AbstractVisitor* visitor)
	{
		return visitor->Visit(this);
	}

}