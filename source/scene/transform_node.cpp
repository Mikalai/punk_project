#include <memory>
#include <fstream>
#include "transform_node.h"

namespace Scene
{
	TransformNode::TransformNode()
	{
		SetType(System::ObjectType::TRANSFORM_NODE);
	}

	bool TransformNode::Save(std::ostream& stream) const
	{
		Node::Save(stream);
		m_local.Save(stream);
		return true;
	}

	bool TransformNode::Load(std::istream& stream)
	{
		Node::Load(stream);
		m_local.Load(stream);
		return true;
	}

	TransformNode* TransformNode::CreateFromFile(const System::string& path)
	{
		std::ifstream stream(path.ToStdString().c_str(), std::ios::binary);
		if (!stream.is_open())
			throw System::PunkInvalidArgumentException(L"Can't open file " + path);
		return CreateFromStream(stream);
	}

	TransformNode* TransformNode::CreateFromStream(std::istream& stream)
	{
		std::unique_ptr<TransformNode> node(new TransformNode);
		node->Load(stream);
		return node.release();
	}

	bool TransformNode::Apply(AbstractVisitor* visitor)
	{
		return visitor->Visit(this);
	}

    const Math::mat4 TransformNode::GetGlobalMatrix() const
    {
        if (GetOwner() == nullptr)
            return m_local;
        std::vector<const Scene::TransformNode*> nodes;
        nodes.push_back(this);
        const Scene::Node* owner = As<const Scene::Node*>(GetOwner());
        while (owner != nullptr)
        {
            const Scene::TransformNode* cur_transform = As<const Scene::TransformNode*>(owner);
            if (cur_transform)
            {
                nodes.push_back(cur_transform);
            }
            owner = As<const Scene::Node*>(owner->GetOwner());
        }
        Math::mat4 res;
        for (auto it = nodes.rbegin(); it != nodes.rend(); ++it)
        {
            res *= (*it)->GetLocalMatrix();
        }
        return res;
    }

    Node* TransformNode::Clone() const
    {
        TransformNode* node = new TransformNode;
        node->SetLocalMatrix(m_local);
        CloneInternals(node);
        return node;
    }
}
