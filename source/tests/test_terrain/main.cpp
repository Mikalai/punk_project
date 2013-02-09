#include "../../punk_engine.h"

class TerrainTest : public Punk::Application
{
public:

	TerrainTest()
		: x(0)
		, y(0)
		, m_left_down(false)
	{}

	virtual void Init(const Punk::Config& value) override
	{
		Punk::Application::Init(value);

		scene = System::GetFactory()->CreateFromTextFile(System::Environment::Instance()->GetModelFolder() + L"house.pmd");
		Virtual::TerrainManager::Instance()->Manage(L"test_map");
		System::Proxy<Virtual::FirstPersonCamera> c(new Virtual::FirstPersonCamera);
		c->SetPosition(Math::vec3(x, 0, y));
		scene->SetActiveCamera(c);

		observer = Virtual::TerrainManager::Instance()->CreateTerrainObserver(Math::vec3(c->GetPosition()));
		node.Reset(new Scene::DebugTextureViewNode);	
		System::Proxy<Scene::Node> root = scene->GetRootNode();

		widget.Reset(new GUI::Widget(0, 0, 0.1, 0.2, L"šæģļł"));

		GetGUIManager()->AddRootWidget(widget);

		render.Reset(new Render::SimpleRender(GetDriver()));
		render->SetGUIHud(widget);

		terrain_node.Reset(new Scene::TerrainNode());
		terrain_node->SetTerrainObserver(observer);
		root->Add(terrain_node);
		root->Add(node);
		Render::MeshCooker cooker;
		//		cooker.Visit(scene->GetRootNode());
		render->SetScene(scene);
		updater.SetScene(scene);	


		System::AsyncLoader::Instance()->MainThreadProc(1);
		t = GPU::OpenGL::Texture2D::CreateFromFile(System::Environment::Instance()->GetTextureFolder() + L"checker2.png");
	}

	virtual void OnMouseLeftButtonDownEvent(System::MouseLeftButtonDownEvent* e) override
	{		
		Punk::Application::OnMouseLeftButtonDownEvent(e);
		m_left_down = true;
	}

	virtual void OnMouseLeftButtonUpEvent(System::MouseLeftButtonUpEvent* e) override
	{
		Punk::Application::OnMouseLeftButtonUpEvent(e);
		m_left_down = false;
	}

	void OnMouseMoveEvent(System::MouseMoveEvent* e) override
	{
		Punk::Application::OnMouseMoveEvent(e);
		x += 0.001 * (float)(e->x - e->x_prev);
		y += 0.001 * (float)(e->y - e->y_prev);		

		System::Proxy<Virtual::FirstPersonCamera> c = scene->GetCameraNode()->GetCamera();
		c->SetYawRollPitch(x, y, 0);
	}

	virtual void OnKeyDownEvent(System::KeyDownEvent* e) override
	{
		Punk::Application::OnKeyDownEvent(e);
		switch (e->key)
		{
		case System::PUNK_KEY_F5:
			{
				std::ofstream stream("scene.save", std::ios_base::binary);
				scene->Save(stream);
			}
			break;
		case System::PUNK_KEY_F9:
			{			
				scene.Reset(new Scene::SceneGraph);
				std::ifstream stream("scene.save", std::ios_base::binary);
				scene->Load(stream);
				render->SetScene(scene);
			}
		case System::PUNK_KEY_A:
			{
			}
		default:
			break;
		}
	}

	virtual void OnIdleEvent(System::IdleEvent* e) override
	{	
		Punk::Application::OnIdleEvent(e);
		System::AsyncLoader::Instance()->MainThreadProc(1);
		//node->SetWatchTexture(t);
		node->SetWatchTexture(observer->GetTerrainView()->GetHeightMap());

		updater.Update();
		render->Render();
		System::Proxy<Virtual::FirstPersonCamera> c = scene->GetCameraNode()->GetCamera();
		bool update = false;
		float scale = 0.07;
		if (System::Keyboard::Instance()->GetKeyState(System::PUNK_KEY_A))
		{
			c->SetPosition(c->GetPosition() + c->GetRightVector() * -scale);
			update = true;
		}
		if (System::Keyboard::Instance()->GetKeyState(System::PUNK_KEY_D))
		{
			c->SetPosition(c->GetPosition() + c->GetRightVector() * scale);
			update = true;
		}
		if (System::Keyboard::Instance()->GetKeyState(System::PUNK_KEY_W))
		{
			c->SetPosition(c->GetPosition() + c->GetDirection() * scale);
			update = true;
		}
		if (System::Keyboard::Instance()->GetKeyState(System::PUNK_KEY_S))
		{
			c->SetPosition(c->GetPosition() + c->GetDirection() * -scale);
			update = true;
		}

		if (update)
		{
			System::string text = System::string::Format(L"X: %f; Z: %f, Height: %f", c->GetPosition().X(), c->GetPosition().Z(), c->GetPosition().Y());
			widget->SetText(text);
			observer->SetPosition(c->GetPosition());
		}

		//OpenGL::Driver* d = OpenGL::Driver::Instance();
		//OpenGL::RenderPass* pass = new OpenGL::RenderPass;
		//Math::mat4 m = Math::mat4::CreateRotation(1, 0, 0, y)*Math::mat4::CreateRotation(0, 1, 0, x);;
		//Render::SolidObjectRender::Parameters p(*m_object, &camera,pass, &m);
		//
		//pass->SetRenderTarget(rt);
		//render->Render(&p);
		//frame.Begin();
		//frame.AddRenderPass(pass);
		//frame.End();	
	}

private:
	System::Proxy<GPU::OpenGL::Texture2D> t;
	System::Proxy<Scene::SceneGraph> scene;
	System::Proxy<Virtual::TerrainObserver> observer;
	bool m_left_down;
	System::Proxy<Scene::DebugTextureViewNode> node;
	System::Proxy<Scene::TerrainNode> terrain_node;
	Scene::BoundingVolumeUpdater updater;
	System::Proxy<Render::SimpleRender> render;
	System::Proxy<GUI::Widget> widget;
	float x;
	float y;
};

int main()
{	
	try
	{
		System::GetFactory()->Init();
		TerrainTest app;
		app.Init(Punk::Config());		
		app.Run();
		System::AsyncLoader::Destroy();
	}
	catch(System::PunkException& e)
	{
		out_error() << e.ToString() << std::endl;
	}
	catch(...)
	{
		out_error() << "Fuck!!!" << std::endl;
	}
	return 0;
}
