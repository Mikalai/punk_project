#include "transform.h"
#include "../../utility/descriptors/object_desc.h"
#include "../../system/logger.h"

namespace Virtual
{
	TransformNode::TransformNode(const Math::mat4& m)
	{
		SetType(System::ObjectType::TRANSFORM_NODE);
		m_transform = m;
	}

	TransformNode::TransformNode() {}

	bool TransformNode::Save(std::ostream& stream) const
	{
		System::Object::Save(stream);
		m_transform.Save(stream);
		return true;
	}

	bool TransformNode::Load(std::istream& stream)
	{
		System::Object::Load(stream);
		m_transform.Load(stream);
		return true;
	}

	TransformNode::~TransformNode()
	{}

}
