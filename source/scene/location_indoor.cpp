#include <memory>
#include <fstream>
#include "location_indoor.h"

namespace Scene
{
	LocationIndoorNode::LocationIndoorNode()
	{
		SetType(System::ObjectType::LOCATION_INDOOR);
	}

	bool LocationIndoorNode::Save(std::ostream& stream) const
	{
		TransformNode::Save(stream);
		m_convex_mesh.Save(stream);
		return true;
	}

	bool LocationIndoorNode::Load(std::istream& stream)
	{
		TransformNode::Load(stream);
		m_convex_mesh.Load(stream);
		return true;
	}

	LocationIndoorNode* LocationIndoorNode::CreateFromFile(const System::string& path)
	{
		std::ifstream stream(path.ToStdString().c_str(), std::ios::binary);
		if (!stream.is_open())
			throw System::PunkInvalidArgumentException(L"Can't open file " + path);
		return CreateFromStream(stream);
	}

	LocationIndoorNode* LocationIndoorNode::CreateFromStream(std::istream& stream)
	{
		std::unique_ptr<LocationIndoorNode> node(new LocationIndoorNode);
		node->Load(stream);
		return node.release();
	}

	bool LocationIndoorNode::Apply(AbstractVisitor* visitor)
	{
		return visitor->Visit(this);
	}
}
