#include "stdafx.h"
#include "CppUnitTest.h"
#include "../../../source/punk_engine.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

class MyApp : public Punk::Application
{
	Scene::SceneGraph* graph;
	Render::SimpleRender* render;
	GPU::OpenGL::Texture2D* t;
public:
	virtual void Init(const Punk::Config& value) override
	{
		Application::Init(value);
		graph = new Scene::SceneGraph();
		graph->SetActiveCamera(new Virtual::FirstPersonCamera);			
		render = new Render::SimpleRender(GetDriver());
		render->SetScene(graph);	
		render->SetPaintEngine(GetPaintEngine());
		System::Mouse::Instance()->LockInWindow(false);			

		//	initial draw
		GetPaintEngine()->Begin(0);
		GetPaintEngine()->DrawRect(Math::Rect(100, 100, 50, 50));
		GetPaintEngine()->DrawRect(Math::Rect(0, 0, 50, 50));
		GetPaintEngine()->End();
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

		//	we will redraw 2d surface only when resized
		auto p = GetPaintEngine();
		if (p)
		{
			p->Begin(0);
			p->DrawRect(Math::Rect(100, 100, 50, 50));
			p->DrawRect(Math::Rect(0, 0, 50, 50));
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