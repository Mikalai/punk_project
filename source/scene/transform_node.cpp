#include <memory>
#include <fstream>
#include "transform_node.h"

namespace Scene
{
	TransformNode::TransformNode()
	{
		SetType(System::ObjectType::TRANSFORM_NODE);
	}

	bool TransformNode::Save(std::ostream& stream) const
	{
		Node::Save(stream);
		m_local.Save(stream);
		m_global.Save(stream);
		return true;
	}

	bool TransformNode::Load(std::istream& stream)
	{
		Node::Load(stream);
		m_local.Load(stream);
		m_global.Load(stream);
		return true;
	}

	TransformNode* TransformNode::CreateFromFile(const System::string& path)
	{
		std::ifstream stream(path.Data(), std::ios::binary);
		if (!stream.is_open())
			throw System::PunkInvalidArgumentException(L"Can't open file " + path);
		return CreateFromStream(stream);
	}

	TransformNode* TransformNode::CreateFromStream(std::istream& stream)
	{
		std::unique_ptr<TransformNode> node(new TransformNode);
		node->Load(stream);
		return node.release();
	}

	bool TransformNode::Apply(AbstractVisitor* visitor)
	{
		return visitor->Visit(this);
	}
}