#include "stdafx.h"
#include "CppUnitTest.h"
#include "../../../source/punk_engine.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

class MyApp : public Punk::Application
{
	Scene::SceneGraph* graph;
	Render::SimpleRender* render;
	GPU::Texture2D* t;
public:
	virtual void Init(const Punk::Config& value) override
	{
		Application::Init(value);
		graph = new Scene::SceneGraph();
		graph->SetActiveCamera(new Virtual::Camera);			
		render = new Render::SimpleRender(GetVideoDriver());
		render->SetScene(graph);	
		render->SetPaintEngine(GetPaintEngine());
		System::Mouse::Instance()->LockInWindow(false);			

		std::vector<Math::Line2D> lines;
		lines.push_back(Math::Line2D(Math::vec2(200, 200), Math::vec2(250, 220)));
		lines.push_back(Math::Line2D(Math::vec2(200, 500), Math::vec2(250, 420)));
		//	initial draw
		auto p = GetPaintEngine();		
		p->Begin(0);
		p->SetLineWidth(2);
		p->DrawRect(Math::Rect(100, 100, 50, 50));
		p->DrawRect(Math::Rect(0, 0, 50, 50));
		p->SetLineWidth(5);
		p->DrawLines(&lines[0], lines.size());
		p->SetFontSize(64);
		p->DrawString(100, 100, L"Hello world");
		p->End();	
	}

	virtual void OnIdleEvent(System::IdleEvent* e) override
	{
		Punk::Application::OnIdleEvent(e);
				
		/*	It is possible to drawing on idle, but if no changes
		*	happened there is no need to draw data every frame 
		*/
		
		/*auto p = GetPaintEngine();
		if (p)
		{
			p->Begin(0);
			p->DrawRect(Math::Rect(100, 100, 50, 50));
			p->DrawRect(Math::Rect(0, 0, 50, 50));
			p->End();
		}*/

		render->Render();
		
	}

	virtual void OnResizeEvent(System::WindowResizeEvent* e) override
	{
		Punk::Application::OnResizeEvent(e);

		graph->GetCameraNode()->GetCamera()->SetViewport(0,0,e->width, e->height);
		//	we will redraw 2d surface only when resized
		auto p = GetPaintEngine();
		int count = 100;
		wchar_t* texts[] = { L"Hello world", L"Vitaju šanoŭnaje spadarstva!", L"Вітаю спадароў-праграмулікаў" };
		if (p)
		{
			auto w = GetWindow()->GetWidth();
			auto h = GetWindow()->GetHeight();
			std::vector<Math::Line2D> lines;
			srand(0);
			for (int i = 0; i < count; ++i)
			{
				lines.push_back(Math::Line2D(Math::vec2(rand() % w, rand() % h), Math::vec2(rand() % w, rand() % h)));
			}

			p->Begin(0);
			p->SetLineWidth(2);
			for (int i = 0; i < count; ++i)
			{
				p->SetFillColor(rand() / (float)RAND_MAX, rand() / (float)RAND_MAX, rand() / (float)RAND_MAX, rand() / (float)RAND_MAX);
				p->SetColor(rand() / (float)RAND_MAX, rand() / (float)RAND_MAX, rand() / (float)RAND_MAX, rand() / (float)RAND_MAX);
				p->DrawRect(Math::Rect(rand() % w, rand() % h, rand() % w, rand() % h));
			}
			p->SetLineWidth(5);
			p->DrawLines(&lines[0], lines.size());			
			for ( int i = 0; i < count; ++i)
			{
				p->SetFontSize(10 + rand() % 54);
				p->SetColor(rand() / (float)RAND_MAX, rand() / (float)RAND_MAX, rand() / (float)RAND_MAX, rand() / (float)RAND_MAX);
				p->DrawString(rand() % w, rand() % h, texts[rand() % 3]);
			}
			p->End();
		}
	}
};

namespace unit_tests
{
	TEST_CLASS(painter_test)
	{
	public:
		
		TEST_METHOD(PaintEngineTest)
		{
			MyApp app;
			app.Init(Punk::Config());		
			app.Run();
			System::AsyncLoader::Destroy();
		}

	};
}