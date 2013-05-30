#ifndef GRAPH_VERTEX_H
#define GRAPH_VERTEX_H

#include "../../config.h"

namespace Math
{
	class Graph;

	class PUNK_ENGINE GraphVertex
	{
	public:
		GraphVertex(Graph* graph, void* data = nullptr);
		void AddVertex(GraphVertex* v);

		/**
		 * @brief RemoveVertex. If flag == true than if v has got no edges it will be deleted.
		 * @param v
		 * @param flag
		 */
		void RemoveVertex(GraphVertex* v, bool flag = true);
		bool IsConnected(GraphVertex* v);

		void SetData(void* data);
		void* GetData();
		const void* GetData() const;
		size_t GetIndex() const;
		size_t GetAdjacentVertexCount() const;
		size_t GetIncidentEdgeCount() const;

	private:
		void AddIncidentEdge(size_t e);
		void RemoveIncidentEdge(size_t e);
		bool IsIncidentEdge(size_t e) const;
		void AddAdjacentVertex(size_t v);
		void RemoveAdjecentVertex(size_t v);
		bool IsAdjacentVertex(size_t v) const;
		void SetIndex(size_t index);
	private:
		Graph* m_graph;
		size_t m_index;
		void* m_data;

		std::vector<size_t> m_incident_edge;
		std::vector<size_t> m_adjacent_vertex;
		friend class Graph;
	};

	template<typename T>
	inline void SetVertexData(GraphVertex* v, T* data)
	{
		v->SetData(reinterpret_cast<void*>(data));
	}

	template<typename T>
	inline T* GetVertexData(GraphVertex* v)
	{
		return reinterpret_cast<T*>(v->GetData());
	}
}

#endif // GRAPH_VERTEX_H
