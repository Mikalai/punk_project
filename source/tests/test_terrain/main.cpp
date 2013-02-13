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

		scene = Cast<Scene::SceneGraph*>(Utility::LoadWorld(System::Environment::Instance()->GetModelFolder() + L"cube.pmd"));
		GetTerrainManager()->Manage(L"test_map");
		Virtual::FirstPersonCamera* c(new Virtual::FirstPersonCamera);
		c->SetPosition(Math::vec3(x, 0, y));
		scene->SetActiveCamera(c);

		observer = GetTerrainManager()->CreateTerrainObserver(Math::vec3(c->GetPosition()));
		node = new Scene::DebugTextureViewNode;	
		Scene::Node* root = scene->GetRootNode();

		widget = new GUI::Widget(0, 0, 0.5, 0.5, L"Hello World!!!");

		GetGUIManager()->AddRootWidget(widget);

		render = new Render::SimpleRender(GetDriver());
		render->SetGUIHud(widget);

		terrain_node = new Scene::TerrainNode();
		terrain_node->SetTerrainObserver(observer);
		root->Add(terrain_node);
		root->Add(node);
		Render::MeshCooker cooker;
 		cooker.Visit(scene->GetRootNode());
		render->SetScene(scene);
		updater.SetScene(scene);	


		System::AsyncLoader::Instance()->MainThreadProc(1);		
		t = new GPU::OpenGL::Texture2D;
		unsigned char data[256*256];
		memset(data, 0xFF, 256*256);
		t->Create(64, 64, ImageModule::IMAGE_FORMAT_RGBA, data, false);
		t = GPU::OpenGL::Texture2D::CreateFromFile(System::Environment::Instance()->GetTextureFolder() + L"checker2.png", true);
	}

	virtual ~TerrainTest()
	{
		safe_delete(t);
		safe_delete(render);
		safe_delete(observer);
		safe_delete(scene);
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

		Virtual::FirstPersonCamera* c = Cast<Virtual::FirstPersonCamera*>(scene->GetCameraNode()->GetCamera());
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
				safe_delete(scene);
				scene = new Scene::SceneGraph;
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
		//node->SetWatchTexture(widget->GetTextTexture());
		node->SetWatchTexture(t);
		//node->SetWatchTexture(observer->GetTerrainView()->GetHeightMap());
		//node->SetWatchTexture(t);

		updater.Update();
		render->Render();
		Virtual::FirstPersonCamera* c = Cast<Virtual::FirstPersonCamera*>(scene->GetCameraNode()->GetCamera());
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
		//	System::string text = System::string::Format(L"X: %f; Z: %f, Height: %f", c->GetPosition().X(), c->GetPosition().Z(), c->GetPosition().Y());
		//	widget->SetText(text);
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
	GPU::OpenGL::Texture2D* t;
	Scene::SceneGraph* scene;
	Virtual::TerrainObserver* observer;
	bool m_left_down;
	Scene::DebugTextureViewNode* node;
	Scene::TerrainNode* terrain_node;
	Scene::BoundingVolumeUpdater updater;
	Render::SimpleRender* render;
	GUI::Widget* widget;
	float x;
	float y;
};

int main()
{	
	try
	{
		//System::GetFactory()->Init();
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
