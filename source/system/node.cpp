#include "node.h"

namespace System
{
	Node::Node() : m_parent(0)
	{}

	Node::Node(const Node& node)
		: m_parent(node.m_parent)
		, m_children(node.m_children)
	{}

	Node& Node::operator= (const Node& node)
	{
		if (this != &node)
		{
			m_parent = node.m_parent;
			m_children = node.m_children;
		}
		return *this;
	}

	bool Node::Apply(NodeVisitor& visitor, bool deep)
	{
		if (!visitor(this))
			return false;

		if (deep)
		{
			for (auto node : m_children)
			{
				if (!node->Apply(visitor, deep))
					return false;
			}
		}		
		return true;
	}

	Node::~Node()
	{
		for (auto node : m_children)
			delete node;
	}
}