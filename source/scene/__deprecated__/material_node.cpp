#include "material_node.h"

namespace Scene
{
	MaterialNode::MaterialNode()
        : m_material(nullptr)
	{
	}

    MaterialNode::~MaterialNode()
    {}

	bool MaterialNode::Save(std::ostream& stream) const
	{
		Node::Save(stream);

		bool flag = m_material != 0;
		stream.write((char*)&flag, sizeof(flag));
		if (flag)
			m_material->GetName().Save(stream);

		return true;
	}

	bool MaterialNode::Load(std::istream& stream)
	{
		Node::Load(stream);

		bool flag;
		stream.read((char*)&flag, sizeof(flag));
		if (flag)
		{
			System::string name;
			name.Load(stream);
			m_material = Virtual::Material::find(name);
		}

		return true;
	}

	MaterialNode* MaterialNode::CreateFromFile(const System::string& path)
	{
		std::ifstream stream(path.ToStdString().c_str(), std::ios::binary);
		if (!stream.is_open())
			throw System::PunkInvalidArgumentException(L"Can't open file " + path);
		return CreateFromStream(stream);
	}

	MaterialNode* MaterialNode::CreateFromStream(std::istream& stream)
	{
		std::unique_ptr<MaterialNode> node(new MaterialNode);
		node->Load(stream);
		return node.release();
	}

	bool MaterialNode::Apply(AbstractVisitor* visitor)
	{
		return visitor->Visit(this);
	}

    Node* MaterialNode::Clone() const
    {
        MaterialNode* node = new MaterialNode;
        node->SetMaterial(m_material);
        CloneInternals(node);
        return node;
    }
}
