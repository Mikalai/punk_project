#include <iostream>
#include "../string/string.h"
#include "../virtual/module.h"
#include "../utility/module.h"
#include "../system/object.h"
#include "../audio/punk_audio.h"
#include "../engine_objects.h"
#include "node.h"

namespace Scene
{
    PUNK_OBJECT_REG(Node, "Scene.Node", PUNK_NODE, &System::CompoundObject::Info.Type);

    Node::Node()
        : m_data(nullptr)
        , m_task(nullptr)
    {
        Info.Add(this);
    }

    Node::~Node()
    {
        delete m_task;
        Info.Remove(this);
    }

    Node* Node::Clone()
    {
        std::unique_ptr<Node> node{new Node};
        node->SetName(GetName());
        node->SetBoundingBox(GetBoundingBox());
        node->SetBoundingSphere(GetBoundingSphere());
        node->SetData(GetData());
        node->SetOwner(GetOwner());
        CloneInternals(node.get());
        return node.release();
    }

    void Node::CloneInternals(Node *dst)
    {
        for (auto o : m_children)
        {
            Node* n = As<Node*>(o);
            if (n)
                dst->Add(n->Clone());
        }
    }

    void Node::SetData(System::Object* value)
    {
        m_data = value;
    }

    SceneGraph* Node::GetSceneGraph() const
    {
        return m_graph;
    }

    System::Object* Node::GetData()
    {
        return m_data;
    }

    const System::Object* Node::GetData() const
    {
        return m_data;
    }

    const System::string Node::ToString() const
    {
        std::wstringstream stream;
        stream << L'[' << GetLocalIndex() << L' ' << Info.Type.GetName() << L']';
        return System::string(stream.str());
    }

    void Node::SetName(const System::string& value)
    {
        m_name = value;
    }

    const System::string& Node::GetName() const
    {
        return m_name;
    }

    bool Node::Remove(const System::string& name, bool depth)
    {
        return System::CompoundObject::Remove(Find(name, depth), depth);
    }

    const Node* Node::Find(const System::string& name, bool in_depth) const
    {
        for (Object* o : m_children)
        {
            Node* n = As<Node*>(o);
            if (n && (n->GetName() == name))
                return n;
        }
        if (in_depth)
        {
            for (Object* o : m_children)
            {
                Node* co = As<Node*>(o);
                if (co)
                {
                    Node* res = co->Find(name, in_depth);
                    if (res)
                        return res;
                }
            }
        }
        return nullptr;
    }

    size_t Node::GetIndex(const System::string& name) const
    {
        size_t index = 0;
        for (const Object* o : m_children)
        {
            const Node* n = As<const Node*>(o);
            if (n && (n->GetName() == name))
                return index;
            index++;
        }
        return -1;
    }

    Node* Node::Find(const System::string& name, bool in_depth)
    {
        for (Object* o : m_children)
        {
            Node* node = As<Node*>(o);
            if (node)
            {
                if (node->GetName() == name)
                    return node;
                if (in_depth)
                {
                    Node* n = node->Find(name, in_depth);
                    if (n != nullptr)
                        return n;
                }
            }
        }
        return nullptr;
    }

    std::vector<Node*> Node::FindAll(const System::string& name, bool in_depth, bool strict_compare)
    {
        std::vector<Node*> res;
        for (Object* o : m_children)
        {
            Node* n = As<Node*>(o);
            if (strict_compare)
            {
                if (n && (n->GetName() == name))
                {
                    res.push_back(n);
                }
            }
            else
            {
                if (n && (n->GetName().find(name) != System::string::npos))
                {
                    res.push_back(n);
                }
            }
            if (in_depth)
            {
                if (n)
                {
                    auto child_res = n->FindAll(name, in_depth, strict_compare);
                    res.insert(res.end(), child_res.begin(), child_res.end());
                }
            }
        }
        return res;
    }

    Utility::AsyncParserTask* Node::Task() const
    {
        return m_task;
    }

    Utility::AsyncParserTask* Node::Task(Utility::AsyncParserTask* value)
    {
        if (m_task)
            delete m_task;
        return m_task = value;
    }
}
