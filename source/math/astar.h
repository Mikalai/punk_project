#ifndef _H_PUNK_MATH_ASTAR_3
#define _H_PUNK_MATH_ASTAR_3

#include "../system/types/priority_list.h"

#include <string>
#include <iostream>
#include <list>

namespace Math
{
	class Node;

	class Location
	{
	public:
		typedef std::list<Location*> LocationList;
		typedef LocationList::iterator LocationIterator;
		typedef LocationList::const_iterator LocationConstIterator;

	public:
		Location() : m_node(0) {}
		LocationList& GetNeighbours() { return m_neighbours; }
		const LocationList& GetNeighbours() const { return m_neighbours; }

		virtual const std::string ToString() const = 0;
	private:
		LocationList m_neighbours;
		mutable Node* m_node;

		friend class Node;
		friend class Algorithm;
	};

	class Agent
	{
	public:
		virtual double EstimateCost(const Location* a, const Location* b) = 0;
		virtual double TraverseCost(const Location* a, const Location* b) = 0;
	};

	class Node
	{
	public:
		typedef std::list<Node*> NodeList;
		NodeList m_successor;

	public:
		Node(const Location* location);
		~Node() { if (m_location) m_location->m_node = 0; }
		void SetCostFromStart(double cost) { m_cost_from_start = cost; }
		double GetCostFromStart() const { return m_cost_from_start; }

		void SetCostToGoal(double cost) { m_cost_to_goal = cost; }
		double GetCostToGoal() const { return m_cost_to_goal; }

		double GetTotalCost() const { return m_cost_from_start + m_cost_to_goal; }

		void SetParent(Node* node);// { m_parent = node; }
		Node* GetParent() { return m_parent; }
		const Node* GetParent() const { return m_parent; }

		const Location* GetLocation() const { return m_location; }

		NodeList& GetSuccessors() { return m_successor; }
		const NodeList& GetSuccessors() const { return m_successor; }

		void SetLocation(const Location* location) { m_location = location; }
		void Init();
		void Update();
		void Clear();
	private:

		double m_cost_from_start;
		double m_cost_to_goal;

		Node* m_parent;	
		const Location* m_location;
		bool  m_delete_flag;
	};

	class Algorithm
	{
		struct Cmp
		{
			Node* m_current;
			bool operator () (Node* a, Node* b)
			{
				return a->GetTotalCost() < b->GetTotalCost();
			}
		};

		typedef System::priority_list<Node*, Cmp> OpenList;
		typedef std::list<Node*> CloseList;

		OpenList m_open;
		CloseList m_close;

		std::list<Node*> m_allocated_nodes;
		std::list<Node*> m_free_nodes;
	public:

		Node* CreateNode(Location* location)
		{
			Node* new_node = new Node(location);
			m_allocated_nodes.push_back(new_node);
			return new_node;
		}

		void DeleteNode(Node* node)
		{
		}

		Algorithm() {}

		bool Run(Location* start_loc, Location* end_loc, Agent* agent)
		{
			std::cout << "Go from " << start_loc->ToString() << " to " << end_loc->ToString() << std::endl;
			m_open.clear();
			m_close.clear();

			Node* start_node;
			m_open.push(start_node = CreateStartNode(start_loc, end_loc, agent));

			while (!m_open.empty())
			{
				Node* node = m_open.top(); m_open.pop();
				std::cout << "Try " << node->GetLocation()->ToString() << std::endl;
				if (IsGoal(node->GetLocation(), end_loc))
				{
					std::cout << "Final path: " << std::endl;
					ConstructPath(node);
					Clear();
					return true;
				}
				else
				{
					for (Location::LocationList::const_iterator it = node->GetLocation()->GetNeighbours().begin(); it != node->GetLocation()->GetNeighbours().end(); ++it)
					{
						Location* location = *it;
						Node* new_node = location->m_node;
						if (!new_node)
							new_node = CreateNode(location);					

						double new_cost = node->GetCostFromStart() + agent->TraverseCost(node->GetLocation(), new_node->GetLocation());

						if ((IsNodeInOpen(new_node) || IsNodeInClose(new_node))
							&& new_node->GetCostFromStart() <= new_cost)
						{						
							continue;
						}
						else
						{	
							new_node->SetParent(node);
							new_node->SetCostFromStart(new_cost);
							new_node->SetCostToGoal(agent->EstimateCost(new_node->GetLocation(), end_loc));
							//	new_node->m_total_cost = new_node->m_cost_from_start + new_node->m_cost_to_goal;							

							if (IsNodeInClose(new_node))
							{
								RemoveFromClose(new_node);		
								//delete new_node;
							}

							if (IsNodeInOpen(new_node))
							{
								AdjustLocationInOpen(new_node);
							}
							else
							{
								m_open.push(new_node);
							}
						}
					}
				}
				m_close.push_back(node);
			}
			std::cout << "No path" << std::endl;
			Clear();
			return false;
		}

		void AdjustLocationInOpen(Node* node)
		{
			m_open.adjust_position(node);
		}

		void RemoveFromClose(Node* node)
		{
			CloseList::iterator it = std::find(m_close.begin(), m_close.end(), node);
			if (it == m_close.end())
			{
				std::cout << "Error: Can't remove node from close list" << std::endl;
				return;
			}
			m_close.erase(it);
		}

		bool IsNodeInOpen(Node* node)
		{
			return std::find(m_open.begin(), m_open.end(), node) != m_open.end();
		}

		bool IsNodeInClose(Node* node)
		{
			return std::find(m_close.begin(), m_close.end(), node) != m_close.end();
		}

		Node* CreateStartNode(Location* start_loc, Location* end_loc, Agent* agent)
		{	
			Node* start = CreateNode(start_loc);
			start->Init();
			start->SetCostToGoal(agent->EstimateCost(start_loc, end_loc));
			return start;
		}

		void ConstructPath(Node* node)
		{
			if (node)
			{
				ConstructPath(node->GetParent());
				std::cout << node->GetLocation()->ToString() << std::endl;
			}
		}

		bool IsGoal(const Location* current, const Location* goal)
		{
			return current == goal;
		}

		void AddToOpen(Node* node)
		{
			m_open.push(node);
		}


		bool SelectTheBest(Node node, Node* result)
		{
			return false;
		}

		void Clear()
		{
			for (std::list<Node*>::iterator it = m_allocated_nodes.begin(); it != m_allocated_nodes.end(); ++it)
			{
				(*it)->SetLocation(0);
				delete *it;
			}
			m_allocated_nodes.clear();
			m_open.clear();
			m_close.clear();
		}
	};
}

#endif	//	_H_PUNK_MATH_ASTAR_3