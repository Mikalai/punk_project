#include "graph_edge.h"

namespace Math
{
	GraphEdge::GraphEdge(GraphVertex* v1, GraphVertex* v2)
		: m_start(v1)
		, m_end(v2)
		, m_index(-1)
	{
	}

	const GraphVertex* GraphEdge::GetStart() const
	{
		return m_start;
	}

	GraphVertex* GraphEdge::GetStart()
	{
		return m_start;
	}

	const GraphVertex* GraphEdge::GetEnd() const
	{
		return m_end;
	}

	GraphVertex* GraphEdge::GetEnd()
	{
		return m_end;
	}

	size_t GraphEdge::GetIndex() const
	{
		return m_index;
	}

	void GraphEdge::SetIndex(size_t value)
	{
		m_index = value;
	}
}
