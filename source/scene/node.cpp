#include <iostream>
#include "../system/logger.h"
#include "../string/string.h"
#include "../virtual/data/data.h"
#include "../virtual/skinning/skinning.h"
#include "../system/object.h"
#include "../audio/punk_audio.h"
#include "../opengl/driver.h"

#include "node.h"

IMPLEMENT_MANAGER(L"resource.nodes", L"*.node", System::Environment::Instance()->GetModelFolder(), System::ObjectType::NODE, Scene, Node);

namespace Scene
{
	Node::Node()
	{
		SetType(System::ObjectType::NODE);
	}

	Node::~Node()
	{
	}

	bool Node::Save(std::ostream& stream) const
	{		
		if (!System::Object::Save(stream))
			return (out_error() << "Can't save node " << GetName() << std::endl, false);
		return true;
	}

	bool Node::Load(std::istream& stream)
	{
		if (!System::Object::Load(stream))
			return (out_error() << "Can't load node " << std::endl, false);
		return true;
	}

	bool Node::Update(int time_ms)
	{
		for each (System::Proxy<Node> child in (*this))
		{
			if (child.IsValid())
				if (!child->Update(time_ms))
					return false;
		}
		return true;
	}

	System::Proxy<Node> Node::CreateFromFile(const System::string& path)
	{
		std::ifstream stream(path.Data(), std::ios::binary);
		if (!stream.is_open())
			return (out_error() << "Can't open file " << path << std::endl, System::Proxy<Node>(nullptr));
		return CreateFromStream(stream);
	}

	System::Proxy<Node> Node::CreateFromStream(std::istream& stream)
	{
		System::Proxy<Node> node(new Node);
		if (!node->Load(stream))
			return (out_error() << "Can't load node from file" << std::endl, System::Proxy<Node>(nullptr));
		return node;
	}

	bool Node::Apply(AbstractVisitor* visitor)
	{
		return visitor->Visit(this);
	}
}

