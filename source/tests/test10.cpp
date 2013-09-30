#include "test10.h"

namespace Test10
{
	class TestApp
	{
		Math::Graph m_graph;
	public:

		TestApp()
		{
		}

		void Run()
		{
			Math::GraphVertex* vertex = new Math::GraphVertex(&m_graph, (void*)10);
			vertex->AddVertex(new Math::GraphVertex(&m_graph, (void*)20));
			vertex->AddVertex(new Math::GraphVertex(&m_graph, (void*)30));

			std::cout << "Vertex count: " << m_graph.GetVertexCount() << std::endl;
			std::cout << "Edge count: " << m_graph.GetEdgeCount() << std::endl;

			m_graph.Clear();

			std::cout << "Vertex count: " << m_graph.GetVertexCount() << std::endl;
			std::cout << "Edge count: " << m_graph.GetEdgeCount() << std::endl;
		}
	};

	void Test::Run()
	{
        m_result = true;
		TestApp app;
		try
		{            
			app.Run();
		}
		catch(System::PunkException& e)
		{
			out_error() << e.ToString() << std::endl;
			m_result = false;
		}
		catch(...)
		{
			m_result = false;
		}
	}

	bool Test::Succeed()
	{
		return m_result;
	}

}
