#include "../virtual/terrain/module.h"
#include "terrain_node.h"

//IMPLEMENT_MANAGER(L"resource.geom_nodes", L"*.geometry_node", System::Environment::Instance()->GetModelFolder(), System::ObjectType::GEOMETRY_NODE, Scene, TerrainNode);

namespace Scene
{
	TerrainNode::TerrainNode()
	{
		SetType(System::ObjectType::TERRAIN_NODE);
	}

	TerrainNode::~TerrainNode()
	{
	}

	bool TerrainNode::Save(std::ostream& stream) const
	{
		if (!Node::Save(stream))
			return (out_error() << "Can't save geometry " << std::endl, false);
				
		/*if (!System::GetFactory()->SaveToStream(stream, m_geometry))
			return (out_error() << "Can't save geometry " << std::endl, false);*/

		return true;
	}

	bool TerrainNode::Load(std::istream& stream)
	{
		if (!Node::Load(stream))
			return (out_error() << "Can't save geometry " << std::endl, false);

		/*m_geometry = System::GetFactory()->LoadFromStream(stream);
		if (!m_geometry.IsValid())
			return false;*/

		return true;
	}

	System::Proxy<TerrainNode> TerrainNode::CreateFromFile(const System::string& path)
	{
		std::ifstream stream(path.Data(), std::ios::binary);
		if (!stream.is_open())
			return (out_error() << "Can't open file " << path << std::endl, System::Proxy<TerrainNode>(nullptr));
		return CreateFromStream(stream);
	}

	System::Proxy<TerrainNode> TerrainNode::CreateFromStream(std::istream& stream)
	{
		System::Proxy<TerrainNode> node(new TerrainNode);
		if (!node->Load(stream))
			return (out_error() << "Can't load node from file" << std::endl, System::Proxy<TerrainNode>(nullptr));
		return node;
	}

	bool TerrainNode::Apply(AbstractVisitor* visitor)
	{
		return visitor->Visit(this);
	}
}