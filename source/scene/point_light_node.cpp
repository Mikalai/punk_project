#include "point_light_node.h"

IMPLEMENT_MANAGER(L"resource.point_light_nodes", L"*.point_light_node", System::Environment::Instance()->GetModelFolder(), System::ObjectType::POINT_LIGHT_NODE, Scene, PointLightNode);

namespace Scene
{
	PointLightNode::PointLightNode()
	{
		SetType(System::ObjectType::POINT_LIGHT_NODE);
	}

	bool PointLightNode::Save(std::ostream& stream) const
	{		
		if (!LightNode::Save(stream))
			return (out_error() << "Can't save point light " << GetName() << std::endl, false);

		if (!System::GetFactory()->SaveToStream(stream, m_point_light))
			return (out_error() << "Can't save point light " << GetName() << std::endl, false);
		return true;
	}

	bool PointLightNode::Load(std::istream& stream)
	{
		if (!LightNode::Load(stream))
			return (out_error() << "Can't load point light " << std::endl, false);

		m_point_light = System::GetFactory()->LoadFromStream(stream);

		if (!m_point_light.IsValid())
			return (out_error() << "Can't load point light " << std::endl, false);
		return true;
	}

	System::Proxy<PointLightNode> PointLightNode::CreateFromFile(const System::string& path)
	{
		std::ifstream stream(path.Data(), std::ios::binary);
		if (!stream.is_open())
			return (out_error() << "Can't open file " << path << std::endl, System::Proxy<PointLightNode>(nullptr));
		return CreateFromStream(stream);
	}

	System::Proxy<PointLightNode> PointLightNode::CreateFromStream(std::istream& stream)
	{
		System::Proxy<PointLightNode> node(new PointLightNode);
		if (!node->Load(stream))
			return (out_error() << "Can't load node from file" << std::endl, System::Proxy<PointLightNode>(nullptr));
		return node;
	}

	bool PointLightNode::Apply(AbstractVisitor* visitor)
	{
		return visitor->Visit(this);
	}
}