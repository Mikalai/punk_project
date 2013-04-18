#include <memory>
#include "point_light_node.h"

namespace Scene
{
	PointLightNode::PointLightNode()
	{
		SetType(System::ObjectType::POINT_LIGHT_NODE);
	}

	bool PointLightNode::Save(std::ostream& stream) const
	{
		LightNode::Save(stream);

//		System::GetFactory()->SaveToStream(stream, m_point_light);
		return true;
	}

	bool PointLightNode::Load(std::istream& stream)
	{
		LightNode::Load(stream);

//		m_point_light = Cast<Virtual::PointLight*>(System::GetFactory()->LoadFromStream(stream));

		return true;
	}

	PointLightNode* PointLightNode::CreateFromFile(const System::string& path)
	{
		std::ifstream stream(path.ToStdString().c_str(), std::ios::binary);
		if (!stream.is_open())
			throw System::PunkInvalidCastException(L"Can't open file " + path);
		return CreateFromStream(stream);
	}

	PointLightNode* PointLightNode::CreateFromStream(std::istream& stream)
	{
		std::unique_ptr<PointLightNode> node(new PointLightNode);
		node->Load(stream);
		return node.release();
	}

	bool PointLightNode::Apply(AbstractVisitor* visitor)
	{
		return visitor->Visit(this);
	}
}
