#include <algorithm>
#include "graph.h"
#include "graph_edge.h"
#include "graph_vertex.h"

namespace Math
{
	Graph::Graph()
	{
	}

	size_t Graph::GetVertexIndex(GraphVertex *v)
	{
		for (size_t i = 0; i != m_vertex.size(); ++i)
		{
			if (m_vertex[i] == v)
				return i;
		}
		return -1;
	}

	size_t Graph::GetEdgeIndex(GraphEdge *e)
	{
		for (size_t i = 0; i = m_edge.size(); ++i)
		{
			if (m_edge[i] == e)
				return i;
		}
		return -1;
	}

	void Graph::AddEdge(GraphEdge *edge)
	{
		//	check if it was not added early
		auto it = std::find(m_edge.begin(), m_edge.end(), edge);
		if (it != m_edge.end())
			return;
		//	find place to insert edge
		for (size_t i = 0; i != m_edge.size(); ++i)
		{
			//	if we found empty slot for edge insert new edge there
			if (m_edge[i] == nullptr)
			{
				m_edge[i] = edge;
				edge->SetIndex(i);
				return;
			}
		}
		//	if there was no empty slots push new edge
		m_edge.push_back(edge);
		edge->SetIndex(m_edge.size()-1);
	}

	void Graph::AddVertex(GraphVertex *vertex)
	{
		//	check if it was not added in the graph early
		auto it = std::find(m_vertex.begin(), m_vertex.end(), vertex);
		if (it != m_vertex.end())
			return;
		//	find place to insert new vertex
		for (size_t i = 0; i != m_vertex.size(); ++i)
		{
			//	if we found empty slot insert here and quit
			if (m_vertex[i] == nullptr)
			{
				m_vertex[i] = vertex;
				vertex->SetIndex(i);
				return;
			}
		}
		//	if no empty slot push new vertex
		m_vertex.push_back(vertex);
		vertex->SetIndex(m_vertex.size()-1);
	}

	void Graph::RemoveEdge(GraphEdge *edge)
	{
		//	find edge in the adge array
		auto it = std::find(m_edge.begin(), m_edge.end(), edge);
		if (it == m_edge.end())
			return;
		//	delete edge
		delete *it;
		//	mark it as null. it will be used while adding new edges
		*it = nullptr;
	}

	void Graph::RemoveVertex(GraphVertex *vertex)
	{
		//	find vertex in the vertex array
		auto it = std::find(m_vertex.begin(), m_vertex.end(), vertex);
		if (it == m_vertex.end())
			return;
		//	delete vertex
		delete *it;
		//	mark it as null. will be used during insert
		*it = nullptr;
	}

	GraphEdge* Graph::GetEdge(size_t index)
	{
		if (m_edge.size() <= index || index == -1)
			return nullptr;
		return m_edge[index];
	}

	GraphVertex* Graph::GetVertex(size_t index)
	{
		if (m_vertex.size() <= index || index == -1)
			return nullptr;
		return m_vertex[index];
	}

	GraphEdge* Graph::FindEdge(size_t v1, size_t v2)
	{
		for (size_t i = 0; i != m_edge.size(); ++i)
		{
			if (m_edge[i]->GetStart()->GetIndex() == v1
					&& m_edge[i]->GetEnd()->GetIndex() == v2)
				return m_edge[i];
		}
		return nullptr;
	}

	size_t Graph::GetVertexCount() const
	{
		return m_vertex.size();
	}

	size_t Graph::GetEdgeCount() const
	{
		return m_edge.size();
	}

	void Graph::Clear()
	{
		while (!m_vertex.empty())
		{
			delete m_vertex.back();
			m_vertex.pop_back();
		}

		while (!m_edge.empty())
		{
			delete m_edge.back();
			m_edge.pop_back();
		}
	}

	Graph::~Graph()
	{
		Clear();
	}

}
