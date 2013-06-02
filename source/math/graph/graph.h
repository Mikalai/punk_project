#ifndef GRAPH_H
#define GRAPH_H

#include "../../config.h"
#include <vector>
#include <utility>

namespace Math
{
	class GraphVertex;
	class GraphEdge;

	class PUNK_ENGINE_API Graph
	{
	public:


	public:
		Graph();
		~Graph();

		size_t GetVertexIndex(GraphVertex* v);
		size_t GetEdgeIndex(GraphEdge* e);

		void AddEdge(GraphEdge* edge);
		void RemoveEdge(GraphEdge* edge);
		void AddVertex(GraphVertex* vertex);
		void RemoveVertex(GraphVertex* vertex);
		GraphEdge* GetEdge(size_t index);
		GraphVertex* GetVertex(size_t index);

		GraphEdge* FindEdge(size_t v1, size_t v2);

		size_t GetVertexCount() const;
		size_t GetEdgeCount() const;

		void Clear();
	private:

		std::vector<GraphVertex*> m_vertex;
		std::vector<GraphEdge*> m_edge;
	};
}

#endif // GRAPH_H
