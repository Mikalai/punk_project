#include <iostream>
#include "../string/string.h"
#include "../virtual/module.h"
#include "../system/object.h"
#include "../audio/punk_audio.h"

#include "node.h"

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
		System::CompoundObject::Save(stream);

		m_bbox.Save(stream);

		return true;
	}

	bool Node::Load(std::istream& stream)
	{
		System::CompoundObject::Load(stream);

		m_bbox.Load(stream);

		return true;
	}

	bool Node::Update(int time_ms)
	{
		for each (auto o in *this)
		{
			Node* child = dynamic_cast<Node*>(o);
			if (child)
				if (!child->Update(time_ms))
					return false;
		}
		return true;
	}

	Node* Node::CreateFromFile(const System::string& path)
	{
		std::ifstream stream(path.Data(), std::ios::binary);
		if (!stream.is_open())
			throw System::PunkInvalidArgumentException(L"Can't open file " + path);
		return CreateFromStream(stream);
	}

	Node* Node::CreateFromStream(std::istream& stream)
	{
		std::unique_ptr<Node> node(new Node);
		node->Load(stream);
		return node.release();
	}

	bool Node::Apply(AbstractVisitor* visitor)
	{
		return visitor->Visit(this);
	}
}

