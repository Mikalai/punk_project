#include "../../punk_engine.h"

System::Proxy<Scene::SceneGraph> scene;

bool m_left_down = false;

OpenGL::SimpleRender render;

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

	//if (m_left_down)
	{
		x += 0.001 * (float)(e->x - e->x_prev);
		y += 0.001 * (float)(e->y - e->y_prev);		

		System::Proxy<Virtual::Cameras::FirstPersonCamera> c = scene->GetCameraNode()->GetCamera();
		c->SetYawRollPitch(x, y, 0);
	}
}

void Idle(System::Event*)
{	
	render.Render();
	System::Proxy<Virtual::Cameras::FirstPersonCamera> c = scene->GetCameraNode()->GetCamera();
	if (System::Keyboard::Instance()->GetKeyState(System::PUNK_KEY_A))
		c->SetPosition(c->GetPosition() + c->GetRightVector() * -0.01f);
	if (System::Keyboard::Instance()->GetKeyState(System::PUNK_KEY_D))
		c->SetPosition(c->GetPosition() + c->GetRightVector() * 0.01f);
	if (System::Keyboard::Instance()->GetKeyState(System::PUNK_KEY_W))
		c->SetPosition(c->GetPosition() + c->GetDirection() * 0.01f);
	if (System::Keyboard::Instance()->GetKeyState(System::PUNK_KEY_S))
		c->SetPosition(c->GetPosition() + c->GetDirection() * -0.01f);
		
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
	System::Window::Instance()->SetTitle(L"OpenGL object test");
	System::Mouse::Instance()->LockInWindow(true);
	OpenGL::Driver::Instance()->Start();

	System::EventManager::Instance()->SubscribeHandler(System::EVENT_IDLE, System::EventHandler(Idle));
	System::EventManager::Instance()->SubscribeHandler(System::EVENT_MOUSE_LBUTTON_DOWN, System::EventHandler(OnMouseLeftButtonDown));
	System::EventManager::Instance()->SubscribeHandler(System::EVENT_MOUSE_LBUTTON_UP, System::EventHandler(OnMouseLeftButtonUp));
	System::EventManager::Instance()->SubscribeHandler(System::EVENT_MOUSE_MOVE, System::EventHandler(OnMouseMove));

	scene = System::GetFactory()->CreateFromTextFile(System::Environment::Instance()->GetModelFolder() + L"portal_test2.pmd");

	render.SetScene(scene);

	System::Proxy<Virtual::Cameras::FirstPersonCamera> c = scene->GetCameraNode()->GetCamera();	

	System::Window::Instance()->Loop();

	return 0;
}
