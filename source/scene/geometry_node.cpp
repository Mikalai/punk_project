#include "geometry_node.h"

IMPLEMENT_MANAGER(L"resource.geom_nodes", L"*.geometry_node", System::Environment::Instance()->GetModelFolder(), System::ObjectType::GEOMETRY_NODE, Scene, GeometryNode);

namespace Scene
{
	GeometryNode::GeometryNode()
	{
		SetType(System::ObjectType::GEOMETRY_NODE);
	}

	bool GeometryNode::Save(std::ostream& stream) const
	{
		if (!Node::Save(stream))
			return (out_error() << "Can't save geometry " << std::endl, false);
				
		if (!System::GetFactory()->SaveToStream(stream, m_geometry))
			return (out_error() << "Can't save geometry " << std::endl, false);

		return true;
	}

	bool GeometryNode::Load(std::istream& stream)
	{
		if (!Node::Load(stream))
			return (out_error() << "Can't save geometry " << std::endl, false);

		m_geometry = System::GetFactory()->LoadFromStream(stream);
		if (!m_geometry.IsValid())
			return false;

		return true;
	}

	System::Proxy<GeometryNode> GeometryNode::CreateFromFile(const System::string& path)
	{
		std::ifstream stream(path.Data(), std::ios::binary);
		if (!stream.is_open())
			return (out_error() << "Can't open file " << path << std::endl, System::Proxy<GeometryNode>(nullptr));
		return CreateFromStream(stream);
	}

	System::Proxy<GeometryNode> GeometryNode::CreateFromStream(std::istream& stream)
	{
		System::Proxy<GeometryNode> node(new GeometryNode);
		if (!node->Load(stream))
			return (out_error() << "Can't load node from file" << std::endl, System::Proxy<GeometryNode>(nullptr));
		return node;
	}

	bool GeometryNode::Apply(AbstractVisitor* visitor)
	{
		return visitor->Visit(this);
	}
}