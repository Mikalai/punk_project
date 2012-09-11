#include "../../punk_engine.h"

Utility::Camera camera;
OpenGL::RenderTarget* rt;
OpenGL::Frame frame;
std::auto_ptr<Render::SolidObjectRender> render;
HObject m_object;

bool m_left_down = false;

float x = 0;
float y = 0;

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

	if (m_left_down)
	{
		x += 0.001 * (float)(e->x - e->x_prev);
		y += 0.001 * (float)(e->y - e->y_prev);
	}
}

void Idle(System::Event*)
{
	OpenGL::Driver* d = OpenGL::Driver::Instance();
	OpenGL::RenderPass* pass = new OpenGL::RenderPass;
	Math::mat4 m = Math::mat4::CreateRotation(1, 0, 0, y)*Math::mat4::CreateRotation(0, 1, 0, x);;
	Render::SolidObjectRender::Parameters p(*m_object, &camera,pass, &m);
	
	pass->SetRenderTarget(rt);
	render->Render(&p);
	frame.Begin();
	frame.AddRenderPass(pass);
	frame.End();	
}

int main()
{
	camera.SetPositionAndTarget(Math::vec3(0, 2, 1), Math::vec3(0,1,0), Math::vec3(0,1,0));

	System::Window::Instance()->SetTitle(L"OpenGL object test");
	System::Mouse::Instance()->LockInWindow(false);
	OpenGL::Driver::Instance()->Start();

	System::EventManager::Instance()->SubscribeHandler(System::EVENT_IDLE, System::EventHandler(Idle));
	System::EventManager::Instance()->SubscribeHandler(System::EVENT_MOUSE_LBUTTON_DOWN, System::EventHandler(OnMouseLeftButtonDown));	
	System::EventManager::Instance()->SubscribeHandler(System::EVENT_MOUSE_LBUTTON_UP, System::EventHandler(OnMouseLeftButtonUp));
	System::EventManager::Instance()->SubscribeHandler(System::EVENT_MOUSE_MOVE, System::EventHandler(OnMouseMove));

	m_object = Utility::ObjectManager::Instance()->Load(L"shop_1.object");
	
	OpenGL::RenderTargetBackBuffer::RenderTargetBackBufferProperties p;		
	rt = OpenGL::Driver::Instance()->CreateRenderTarget(&p);
	rt->SetClearColor(0.6, 0.6, 0.6, 1);

	render.reset(new Render::SolidObjectRender);
	
	if (!rt)
	{
		out_error() << "Render target was not created" << std::endl;
		return 0;
	}

	System::Window::Instance()->Loop();

	OpenGL::StaticObjectManager::Destroy();
	OpenGL::Texture2DManager::Destroy();

	return 0;
}
