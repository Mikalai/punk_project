#include <memory>
#include <fstream>
#include "portal_node.h"

namespace Scene
{
	PortalNode::PortalNode()
	{
		SetType(System::ObjectType::PORTAL_NODE);
	}

	bool PortalNode::Save(std::ostream& stream) const
	{
		TransformNode::Save(stream);
		m_portal.Save(stream);
		return true;
	}

	bool PortalNode::Load(std::istream& stream)
	{
		TransformNode::Load(stream);
		m_portal.Load(stream);
		return true;
	}

	PortalNode* PortalNode::CreateFromFile(const System::string& path)
	{
		std::ifstream stream(path.ToStdString().c_str(), std::ios::binary);
		if (!stream.is_open())
			throw System::PunkInvalidArgumentException(L"Can't open file " + path);
		return CreateFromStream(stream);
	}

	PortalNode* PortalNode::CreateFromStream(std::istream& stream)
	{
		std::unique_ptr<PortalNode> node(new PortalNode);
		node->Load(stream);
		return node.release();
	}

	bool PortalNode::Apply(AbstractVisitor* visitor)
	{
		return visitor->Visit(this);
	}

}
