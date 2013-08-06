#include "../virtual/terrain/module.h"
#include "terrain_node.h"

namespace Scene
{
	TerrainNode::TerrainNode()
        : m_mesh(nullptr)
	{
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

    void TerrainNode::SetTerrainMesh(Virtual::TerrainMesh* value)
    {
        m_mesh = value;
    }

    Virtual::TerrainMesh* TerrainNode::GetTerrainMesh()
    {
        return m_mesh;
    }

    Node* TerrainNode::Clone() const
    {
        TerrainNode* node = new TerrainNode;
        node->SetTerrainMesh(m_mesh);
        CloneInternals(node);
        return node;
    }
}
