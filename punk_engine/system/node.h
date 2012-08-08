#ifndef _H_PUNK_SYSTEM_NODE
#define _H_PUNK_SYSTEM_NODE

#include "config.h"
#include <list>

namespace System
{
	/**
		Node supposed to be used to create different hierarchical
		structures
	*/
	class Node;

	struct NodeVisitor
	{
		virtual bool operator () (Node* node) = 0;
	};

	class MODULE_SYSTEM Node
	{
		Node* m_parent;
		std::list<std::shared_ptr<Node>> m_children;
	public:		
		Node();
		Node(const Node& node);
		Node& operator = (const Node& node);

		void AddChild(Node* node) { m_children.push_back(std::shared_ptr<Node>(node)); }
		void RemoveChild(Node* node) { m_children.remove(std::shared_ptr<Node>(node)); }

		bool Apply(NodeVisitor& visitor, bool deep = true);
	};
}

#endif	//	_H_PUNK_SYSTEM_NODE