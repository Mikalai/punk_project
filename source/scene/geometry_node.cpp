#include "geometry_node.h"
#include "../system/errors/module.h"

namespace Scene
{
	GeometryNode::GeometryNode()
	{
		m_geometry = nullptr;
		SetType(System::ObjectType::GEOMETRY_NODE);
	}

	bool GeometryNode::Save(std::ostream& stream) const
	{
		Node::Save(stream);

//		if (!System::GetFactory()->SaveToStream(stream, m_geometry))

		return true;
	}

	bool GeometryNode::Load(std::istream& stream)
	{
		Node::Load(stream);
		//m_geometry = Cast<Virtual::Geometry*>(System::GetFactory()->LoadFromStream(stream));
		return true;
	}

	GeometryNode* GeometryNode::CreateFromFile(const System::string& path)
	{
		std::ifstream stream(path.ToStdString().c_str(), std::ios::binary);
		if (!stream.is_open())
			throw  System::PunkException(L"Can't open file");
		return CreateFromStream(stream);
	}

	GeometryNode* GeometryNode::CreateFromStream(std::istream& stream)
	{
		std::unique_ptr<GeometryNode> node(new GeometryNode);
		node->Load(stream);
		return node.release();
	}

	bool GeometryNode::Apply(AbstractVisitor* visitor)
	{
		return visitor->Visit(this);
	}
}
