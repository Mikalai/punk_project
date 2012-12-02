#include "../../punk_engine.h"

std::unique_ptr<Virtual::World> g_world;
std::auto_ptr<Virtual::Cameras::FirstPersonCamera> g_camera;
OpenGL::RenderTarget* rt;
std::auto_ptr<OpenGL::RenderContextSolidTexture3D> rc;

bool m_left_down = false;

float x = 0;
float y = 0;
float rho = 5;

void OnMouseLeftButtonDown(System::Event* ee)
{
	m_left_down = true;
}

void OnMouseLeftButtonUp(System::Event* ee)
{
	m_left_down = false;
}

void OnMouseWheelScroll(System::Event* ee)
{
	System::MouseWheelEvent* e = static_cast<System::MouseWheelEvent*>(ee);
	rho += 0.1f * (float)e->delta;	
	g_camera->SetPosition(rho*Math::vec3(sin(x), cos(x)*sin(y), cos(x)*cos(y)));
};

void OnMouseMove(System::Event* ee)
{
	System::MouseMoveEvent* e = static_cast<System::MouseMoveEvent*>(ee);

	if (m_left_down)
	{
		x += 0.001 * (float)(e->x - e->x_prev);
		y += 0.001 * (float)(e->y - e->y_prev);
	}
	g_camera->SetPosition(rho*Math::vec3(sin(x), cos(x)*sin(y), cos(x)*cos(y)));
}

void Idle(System::Event*)
{
	OpenGL::Driver* d = OpenGL::Driver::Instance();

	OpenGL::Frame frame;

	frame.Begin();

	Render::SimpleRender render;
	render.SetActiveCamera(g_camera.get());
	render.SetRenderTarget(rt);

	render.Render(*g_world, frame);

	frame.End();	
}

void CreateWorld()
{
	
	Virtual::Cameras::FirstPersonCameraOptions options;	
	g_camera.reset(new Virtual::Cameras::FirstPersonCamera(options));
	g_camera->SetPositionAndTarget(Math::vec3(0, 5, 5), Math::vec3(0,0,0), Math::vec3(0,1,0));


	Utility::WorldDesc world_desc;
	if (!Utility::Parser::LoadWorld(System::Environment::Instance()->GetModelFolder() + L"shop_interior2.pmd", world_desc))
	{
		out_error() << "Can't load world descriptor from file" << std::endl;
		exit(-1);
	}

	g_world.reset(new Virtual::World(world_desc));
}

int main()
{
	System::Window::Instance()->SetTitle(L"OpenGL Init test");
	System::Mouse::Instance()->LockInWindow(false);	
	OpenGL::Driver::Instance()->Start();

	System::EventManager::Instance()->SubscribeHandler(System::EVENT_IDLE, System::EventHandler(Idle));
	System::EventManager::Instance()->SubscribeHandler(System::EVENT_MOUSE_LBUTTON_DOWN, System::EventHandler(OnMouseLeftButtonDown));	
	System::EventManager::Instance()->SubscribeHandler(System::EVENT_MOUSE_LBUTTON_UP, System::EventHandler(OnMouseLeftButtonUp));
	System::EventManager::Instance()->SubscribeHandler(System::EVENT_MOUSE_MOVE, System::EventHandler(OnMouseMove));
	System::EventManager::Instance()->SubscribeHandler(System::EVENT_MOUSE_WHEEL, System::EventHandler(OnMouseWheelScroll));

	OpenGL::RenderTargetBackBuffer::RenderTargetBackBufferProperties p;		
	rt = OpenGL::Driver::Instance()->CreateRenderTarget(&p);
	rt->SetClearColor(0.6, 0.6, 0.6, 1);

	if (!rt)
	{
		out_error() << "Render target was not created" << std::endl;
		return 0;
	}

	CreateWorld();

	System::Window::Instance()->Loop();
	
	System::MegaDestroyer::Destroy();
	return 0;
}
