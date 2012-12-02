#include "location_indoor.h"

namespace Scene
{
	LocationIndoorNode::LocationIndoorNode()
	{
		SetType(System::ObjectType::LOCATION_INDOOR);
	}

	bool LocationIndoorNode::Save(std::ostream& stream) const
	{
		if (!TransformNode::Save(stream))
			return (out_error() << "Can't save TransformNode" << std::endl, false);
		return true;
	}

	bool LocationIndoorNode::Load(std::istream& stream)
	{
		if (!TransformNode::Load(stream))
			return (out_error() << "Can't save TransformNode" << std::endl, false);
		return true;
	}

	System::Proxy<LocationIndoorNode> LocationIndoorNode::CreateFromFile(const System::string& path)
	{
		std::ifstream stream(path.Data(), std::ios::binary);
		if (!stream.is_open())
			return (out_error() << "Can't open file " << path << std::endl, System::Proxy<TransformNode>(nullptr));
		return CreateFromStream(stream);
	}

	System::Proxy<LocationIndoorNode> LocationIndoorNode::CreateFromStream(std::istream& stream)
	{
		System::Proxy<LocationIndoorNode> node(new LocationIndoorNode);
		if (!node->Load(stream))
			return (out_error() << "Can't load node from file" << std::endl, System::Proxy<LocationIndoorNode>(nullptr));
		return node;
	}

	bool LocationIndoorNode::Apply(AbstractVisitor* visitor)
	{
		return visitor->Visit(this);
	}
}