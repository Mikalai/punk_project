#include "../../../source/punk_engine.h"
#include "world.h"
#include "construction.h"

enum OperationType { RTS_OPERATION_NO, RTS_OPERATION_SELECT, RTS_OPERATION_CONSTRUCT_STEP_0, RTS_OPERATION_CONSTRUCT_STEP_1 };

class TerrainTest : public Punk::Application
{
public:

	TerrainTest()
		: x(0)
		, y(0)
		, m_left_down(false)
	{
		m_current_operation = RTS_OPERATION_SELECT;
	}

	//void AddNewCube()
	//{
	//	auto c = scene->GetCameraNode()->GetCamera()->GetPosition();
	//	Scene::TransformNode* trans_node = new Scene::TransformNode;
	//	{		
	//		m_cube = new Virtual::Cube();
	//		m_cube->EnterPhysicalSimulator(GetSimulator());
	//		Scene::StaticMeshNode* mesh_node = new Scene::StaticMeshNode();
	//		Virtual::StaticGeometry* geom = new Virtual::StaticGeometry;
	//		auto gpu_cube = new GPU::OpenGL::CubeObject;
	//		gpu_cube->Cook(1,1,1);
	//		geom->SetGPUBufferCache(gpu_cube); 
	//		mesh_node->SetGeometry(geom);
	//		m_cube->SetTransform(Math::mat4::CreateTranslate(c.X(), c.Y(), c.Z()));

	//		trans_node->Add(mesh_node);
	//		trans_node->SetUserData(m_cube);
	//	}		
	//	auto root = scene->GetRootNode();
	//	root->Add(trans_node);
	//}

	virtual void Init(const Punk::Config& value) override
	{
		Punk::Application::Init(value);

		m_world = new World(this);		
		//
		////		scene = Cast<Scene::SceneGraph*>(Utility::LoadWorld(System::Environment::Instance()->GetModelFolder() + L"cube.pmd"));
		//		Virtual::FirstPersonCamera* c(new Virtual::FirstPersonCamera);
		//		c->SetPosition(Math::vec3(x, 0, y));		
		////		scene->SetActiveCamera(c);
		//
		////		node = new Scene::TextureViewNode;			
		//	//	Scene::Node* root = scene->GetRootNode();
		//	//	node->SetSize(0, 0.5, 0.5, 0.5);
		////		widget = new GUI::Widget(0, 0, 0.5, 0.5, L"Hello World!!!");
		//
		//	//	GetGUIManager()->AddRootWidget(widget);
		//
		//
		////		render = new Render::SimpleRender(GetVideoDriver());
		////		render->SetGUIHud(widget);
		//		//render->SetPainter(GetPainter());
		//
		//		//GetPainter()->DrawLine(Math::vec2(-1, -1), Math::vec2(1, 1));
		//
		////		terrain_node = new Scene::TerrainNode();
		////		terrain_node->SetTerrainObserver(observer);
		////		root->Add(node);		
		//		Render::MeshCooker cooker;
		//		cooker.Visit(scene->GetRootNode());
		//	//	render->SetScene(scene);
		//		updater.SetScene(scene);	
		//
		//	//	AddNewCube();
		//
		//		System::AsyncLoader::Instance()->MainThreadProc(1);		
		//		t = new GPU::Texture2D;
		//		unsigned char data[256*256];
		//		memset(data, 0xFF, 256*256);
		//		t->Create(64, 64, ImageModule::IMAGE_FORMAT_RGBA, data, false);
		//		t = GPU::Texture2D::CreateFromFile(System::Environment::Instance()->GetTextureFolder() + L"checker2.png", true);		
	}

	virtual ~TerrainTest()
	{
		try
		{
			//			safe_delete(m_cube);
			//		safe_delete(t);
			//	safe_delete(render);		
			//safe_delete(scene);
			safe_delete(m_world);
		}
		catch(...)
		{
			out_error() << L"Complete fail" << std::endl;
		}
	}

	virtual void OnResizeEvent(System::WindowResizeEvent* event) override
	{
		Punk::Application::OnResizeEvent(event);
		m_world->GetCamera()->SetViewport(0, 0, event->width, event->height);
	}

	virtual void OnMouseLeftButtonDownEvent(System::MouseLeftButtonDownEvent* e) override
	{		
		Punk::Application::OnMouseLeftButtonDownEvent(e);

		////	if we initiate construction 
		//if (m_current_operation == RTS_OPERATION_CONSTRUCT_STEP_0)
		//{
		//		Math::vec3 p = m_world->IntersectTerrain(e->x, e->y);				
		//		m_current_construction->SetLocation(p);
		//		if (!m_world->CheckCollisitionWithObjects(m_current_construction->ToGameEntity()))
		//		{
		//			m_current_operation = RTS_OPERATION_CONSTRUCT_STEP_1;
		//		}
		//		m_world->AddGameEntity(m_current_construction->ToGameEntity());				
		//}
		//else if (m_current_operation == RTS_OPERATION_CONSTRUCT_STEP_1)
		//{
		//	if (!e->shiftButton)
		//		m_current_operation = RTS_OPERATION_NO;
		//	else 
		//		m_current_operation = RTS_OPERATION_CONSTRUCT_STEP_0;
		//}
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
		auto ray = m_world->GetCamera()->GetWorldRay(e->x, e->y);			
		m_world->OnSelectorMove(ray);
		
		x += 0.001 * (float)(e->x - e->x_prev);
		y += 0.001 * (float)(e->y - e->y_prev);		

		Virtual::Camera* c = Cast<Virtual::Camera*>(m_world->GetCamera());
		c->SetYawRollPitch(x, y, 0);
	}

	virtual void OnKeyDownEvent(System::KeyDownEvent* e) override
	{		
		Punk::Application::OnKeyDownEvent(e);		
		switch (e->key)
		{
		case System::PUNK_KEY_F5:
			{
				//std::ofstream stream("scene.save", std::ios_base::binary);
				//scene->Save(stream);
			}
			break;
		case System::PUNK_KEY_F9:
			{			
				//safe_delete(scene);
				//scene = new Scene::SceneGraph;
				//std::ifstream stream("scene.save", std::ios_base::binary);
				//scene->Load(stream);
				//render->SetScene(scene);
			}
		case System::PUNK_KEY_A:
			{
			}
			break;
		case System::PUNK_KEY_SPACE:
			{
				//				AddNewCube();
			}
			break;
		case System::PUNK_KEY_1:
			{
				//m_current_operation = OperationType::RTS_OPERATION_CONSTRUCT_STEP_0;	
				//m_current_construction = new Construction;
				//m_current_construction->SetScheme(m_house_scheme);				
			}
		default:
			break;
		}
	}

	virtual void OnIdleEvent(System::IdleEvent* e) override
	{	
		Punk::Application::OnIdleEvent(e);
		System::AsyncLoader::Instance()->MainThreadProc(1);
		m_world->Update(e->elapsed_time_s);
		m_world->Draw();
		//		node->SetWatchTexture(observer->GetTerrainView()->GetHeightMap());
		//		updater.Update();
		//		render->Render();

		Virtual::Camera* c = Cast<Virtual::Camera*>(m_world->GetCamera());
		bool update = false;
		float scale = 0.5;
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
			//widget->SetText(text);
			m_world->GetTerrainObserver()->SetPosition(c->GetPosition());
			//			observer->SetPosition(c->GetPosition());			
		}
	}

private:
	bool m_left_down;
	Scene::BoundingVolumeUpdater updater;
	float x;
	float y;
	World* m_world;
	OperationType m_current_operation;
	Construction* m_current_construction;
	HouseScheme* m_house_scheme;
};

//TEST_METHOD(TerrainManagerTest)
//{
//	TerrainTest app;
//	app.Init(Punk::Config());		
//	app.Run();
//	System::AsyncLoader::Destroy();
//}

int main()
{
	try
	{
		TerrainTest app;
		Punk::Config config;	
		app.Init(config);			
		app.Run();
		System::AsyncLoader::Destroy();
	}
	catch(System::PunkException& e)
	{
		out_error() << e.ToString() << std::endl;
	}
	catch(...)
	{
		out_error() << "Fuck" << std::endl;
	}
}
