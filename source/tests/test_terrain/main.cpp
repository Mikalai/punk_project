#include "../../punk_engine.h"

System::Proxy<GPU::OpenGL::Texture2D> t;
System::Proxy<Scene::SceneGraph> scene;
System::Proxy<Virtual::TerrainObserver> observer;
bool m_left_down = false;
System::Proxy<Scene::DebugTextureViewNode> node;
System::Proxy<Scene::TerrainNode> terrain_node;

Scene::BoundingVolumeUpdater updater;
Render::SimpleRender render;
System::Proxy<GUI::Widget> widget;

float x = 0, y = 0;
void OnMouseLeftButtonDown(System::Event* ee)
{
	m_left_down = true;
}

void OnMouseLeftButtonUp(System::Event* ee)
{
	m_left_down = false;
}

void OnMouseMove(System::Event* ee)
{
	System::MouseMoveEvent* e = static_cast<System::MouseMoveEvent*>(ee);

	//if (m_left_down)
	//{
	//	x += (float)(e->x - e->x_prev);
	//	y += (float)(e->y - e->y_prev);		
	//	observer->SetPosition(Math::vec3(x, 0, y));
	//}

	//if (m_left_down)
	{
		x += 0.001 * (float)(e->x - e->x_prev);
		y += 0.001 * (float)(e->y - e->y_prev);		

		System::Proxy<Virtual::FirstPersonCamera> c = scene->GetCameraNode()->GetCamera();
		c->SetYawRollPitch(x, y, 0);
	}
}

void OnKeyDown(System::Event* ee)
{
	System::KeyDownEvent* e = static_cast<System::KeyDownEvent*>(ee);
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
			render.SetScene(scene);
		}
	case System::PUNK_KEY_A:
		{
		}
	default:
		break;
	}
}

void Idle(System::Event*)
{	
	System::AsyncLoader::Instance()->MainThreadProc(1);
	//	GPU::GPU_INIT(0);
	//node->SetWatchTexture(t);
	node->SetWatchTexture(observer->GetTerrainView()->GetHeightMap());

	updater.Update();
	render.Render();
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

int main()
{	
	System::Proxy<System::Object> a(new System::Object);
	System::Proxy<System::Object> b(new System::Object);

	std::swap(a,b);
	try
	{
		System::GetFactory()->Init();

		System::Window::Instance()->SetTitle(L"OpenGL object test");
		System::Mouse::Instance()->LockInWindow(true);
		GPU::OpenGL::Driver::Instance()->Start();

		GPU::GPU_INIT(0);

		auto v = GPU::OpenGL::VideoMemory::Instance()->GetMaxAvailableMemory();

		System::EventManager::Instance()->SubscribeHandler(System::EVENT_IDLE, System::EventHandler(Idle));
		System::EventManager::Instance()->SubscribeHandler(System::EVENT_MOUSE_LBUTTON_DOWN, System::EventHandler(OnMouseLeftButtonDown));
		System::EventManager::Instance()->SubscribeHandler(System::EVENT_MOUSE_LBUTTON_UP, System::EventHandler(OnMouseLeftButtonUp));
		System::EventManager::Instance()->SubscribeHandler(System::EVENT_MOUSE_MOVE, System::EventHandler(OnMouseMove));
		System::EventManager::Instance()->SubscribeHandler(System::EVENT_KEY_DOWN, System::EventHandler(OnKeyDown));

		scene = System::GetFactory()->CreateFromTextFile(System::Environment::Instance()->GetModelFolder() + L"house.pmd");

		Virtual::TerrainManager::Instance()->Manage(L"test_map");

		System::Proxy<Virtual::FirstPersonCamera> c(new Virtual::FirstPersonCamera);
		c->SetPosition(Math::vec3(x, 0, y));
		scene->SetActiveCamera(c);

		observer = Virtual::TerrainManager::Instance()->CreateTerrainObserver(Math::vec3(c->GetPosition()));
		node.Reset(new Scene::DebugTextureViewNode);	
		System::Proxy<Scene::Node> root = scene->GetRootNode();

		widget.Reset(new GUI::Widget(0, 0, 0.1, 0.2, L"DF"));

		GUI::Manager::Instance()->AddRootWidget(widget);

		render.SetGUIHud(widget);

		terrain_node.Reset(new Scene::TerrainNode());
		terrain_node->SetTerrainObserver(observer);
		root->Add(terrain_node);
		root->Add(node);
		Render::MeshCooker cooker;
		//		cooker.Visit(scene->GetRootNode());
		render.SetScene(scene);
		updater.SetScene(scene);	


		System::AsyncLoader::Instance()->MainThreadProc(1);
		t = GPU::OpenGL::Texture2D::CreateFromFile(System::Environment::Instance()->GetTextureFolder() + L"checker2.png");

		System::Window::Instance()->Loop();


		System::AsyncLoader::Destroy();
	}
	catch(System::PunkException& e)
	{
		out_error() << e.ToString() << std::endl;
	}
	return 0;
}
