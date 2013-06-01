#ifndef GRAPH_EDGE_H
#define GRAPH_EDGE_H

#include "../../config.h"
#include <cstddef>

namespace Math
{
	class Graph;
	class GraphVertex;

	class PUNK_ENGINE_PUBLIC GraphEdge
	{
	public:
		GraphEdge(GraphVertex* v1, GraphVertex* v2);

		const GraphVertex* GetStart() const;
		GraphVertex* GetStart();
		const GraphVertex* GetEnd() const;
		GraphVertex* GetEnd();
		size_t GetIndex() const;

	private:
		void SetIndex(size_t value);

	private:
		GraphVertex* m_start;
		GraphVertex* m_end;
		size_t m_index;

		friend class Graph;
	};
}

#endif // GRAPH_EDGE_H
