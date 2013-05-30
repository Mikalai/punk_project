#include <algorithm>
#include "graph_vertex.h"
#include "graph.h"
#include "graph_edge.h"

namespace Math
{

	GraphVertex::GraphVertex(Graph *graph, void *data)
		: m_graph(graph)
		, m_data(data)
		, m_index(-1)
	{}

	void GraphVertex::AddVertex(GraphVertex *v)
	{
		//	if we have been already connected skipp all
		if (IsConnected(v))
			return;

		//	if vertex is not in graph add it
		if (v->GetIndex() == -1)
			m_graph->AddVertex(v);

		//	create edge
		GraphEdge* edge = new GraphEdge(this, v);

		//	add edge in the graph
		m_graph->AddEdge(edge);

		//	connect start vertex with edge
		AddIncidentEdge(edge->GetIndex());
		//	connect end vertex with edge
		v->AddIncidentEdge(edge->GetIndex());

		//	add adjecent vertex
		AddAdjacentVertex(v->GetIndex());
		v->AddAdjacentVertex(GetIndex());
	}

	void GraphVertex::RemoveVertex(GraphVertex *v, bool flag)
	{
		//	find incident edge for both vertex
		GraphEdge* e = m_graph->FindEdge(GetIndex(), v->GetIndex());
		if (!e)
			return;

		//	remove incident edges
		RemoveIncidentEdge(e->GetIndex());
		v->RemoveIncidentEdge(e->GetIndex());

		//	remove adjacent vertex
		RemoveAdjecentVertex(v->GetIndex());
		v->RemoveIncidentEdge(GetIndex());

		m_graph->RemoveEdge(e);

		if (flag)
		{
			if (v->GetAdjacentVertexCount() == 0)
				m_graph->RemoveVertex(v);
			//	TODO: I'm afraid of the next code
			if (GetAdjacentVertexCount() == 0)
				m_graph->RemoveVertex(this);
		}
	}

	bool GraphVertex::IsConnected(GraphVertex *v)
	{
		auto it = std::find(m_adjacent_vertex.begin(), m_adjacent_vertex.end(), v->GetIndex());
		return it != m_adjacent_vertex.end();
	}

	void GraphVertex::SetData(void *data)
	{
		m_data = data;
	}

	void* GraphVertex::GetData()
	{
		return m_data;
	}

	const void* GraphVertex::GetData() const
	{
		return m_data;
	}

	size_t GraphVertex::GetIndex() const
	{
		return m_index;
	}

	size_t GraphVertex::GetAdjacentVertexCount() const
	{
		return m_adjacent_vertex.size();
	}

	size_t GraphVertex::GetIncidentEdgeCount() const
	{
		return m_incident_edge.size();
	}

	void GraphVertex::AddIncidentEdge(size_t e)
	{
		auto it = std::find(m_incident_edge.begin(), m_incident_edge.end(), e);
		if (it != m_incident_edge.end())
			return;
		m_incident_edge.push_back(e);
	}

	void GraphVertex::RemoveIncidentEdge(size_t e)
	{
		auto it = std::find(m_incident_edge.begin(), m_incident_edge.end(), e);
		if (it == m_incident_edge.end())
			return;
		m_incident_edge.erase(it);
	}

	bool GraphVertex::IsIncidentEdge(size_t e) const
	{
		auto it = std::find(m_incident_edge.begin(), m_incident_edge.end(), e);
		return it != m_incident_edge.end();
	}

	void GraphVertex::AddAdjacentVertex(size_t v)
	{
		auto it = std::find(m_adjacent_vertex.begin(), m_adjacent_vertex.end(), v);
		if (it != m_adjacent_vertex.end())
			return;
		m_adjacent_vertex.push_back(v);
	}

	void GraphVertex::RemoveAdjecentVertex(size_t v)
	{
		auto it = std::find(m_adjacent_vertex.begin(), m_adjacent_vertex.end(), v);
		if (it == m_adjacent_vertex.end())
			return;
		m_adjacent_vertex.erase(it);
	}

	bool GraphVertex::IsAdjacentVertex(size_t v) const
	{
		auto it = std::find(m_adjacent_vertex.begin(), m_adjacent_vertex.end(), v);
		return it != m_adjacent_vertex.end();
	}

	void GraphVertex::SetIndex(size_t index)
	{
		m_index = index;
	}
}
