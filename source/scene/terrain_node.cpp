#include "../virtual/terrain/module.h"
#include "terrain_node.h"

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
		Node::Save(stream);
		return true;
	}

	bool TerrainNode::Load(std::istream& stream)
	{
		Node::Load(stream);
		return true;
	}

	TerrainNode* TerrainNode::CreateFromFile(const System::string& path)
	{
		std::ifstream stream(path.ToStdString().c_str(), std::ios::binary);
		if (!stream.is_open())
			throw System::PunkInvalidArgumentException(L"Can't open file " + path);
		return CreateFromStream(stream);
	}

	TerrainNode* TerrainNode::CreateFromStream(std::istream& stream)
	{
		std::unique_ptr<TerrainNode> node(new TerrainNode);
		node->Load(stream);
		return node.release();
	}

	bool TerrainNode::Apply(AbstractVisitor* visitor)
	{
		return visitor->Visit(this);
	}
}
