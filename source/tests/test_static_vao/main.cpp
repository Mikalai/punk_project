#include "../../punk_engine.h"

Utility::Camera camera;
OpenGL::RenderTarget* rt;
OpenGL::Frame frame;
std::auto_ptr<OpenGL::RenderContextBumpMapping> rc;
std::auto_ptr<OpenGL::StaticObject> m_vao;
std::auto_ptr<OpenGL::TextureContext> m_textures;

System::HResource m_object;

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

	OpenGL::RenderContextBumpMapping::PolicyParameters* p = new OpenGL::RenderContextBumpMapping::PolicyParameters;
	Math::mat4 world = Math::mat4::CreateRotation(1, 0, 0, y)*Math::mat4::CreateRotation(0, 1, 0, x);
	Math::mat4 view = camera.GetViewMatrix();
	Math::mat4 proj = camera.GetProjectionMatrix();	
	p->m_ambient.Set(0,0,0,1);
	p->m_diffuse.Set(1,1,1,1);
	p->m_diffuse_texture = 0;
	p->m_light_position.Set(100, 100, 100);
	p->m_normal_matrix = (view*world).RotationPart().Inversed().Transposed();
	p->m_normal_texture = 1;
	p->m_proj = proj;
	p->m_specular.Set(1,1,1,1);
	p->m_specular_power = 256.0f;
	p->m_view = view;
	p->m_world = world;	

	OpenGL::Batch* b = new OpenGL::Batch;
	b->m_parameters = p;
	b->m_renderable = static_cast<OpenGL::Renderable*>(*m_object);
	b->m_textures.push_back(static_cast<OpenGL::Texture2D*>(*OpenGL::Texture2DManager::Instance()->Load(L"cs.png")));
	b->m_textures.push_back(static_cast<OpenGL::Texture2D*>(*OpenGL::Texture2DManager::Instance()->Load(L"cs_normal.png")));
	pass->SetRenderTarget(rt);
	pass->AddBatch(m_textures.get(), rc.get(), b); 

	frame.Begin();
	frame.AddRenderPass(pass);
	frame.End();	

}

int main()
{
	camera.SetPositionAndTarget(Math::vec3(0, 5, 5), Math::vec3(0,0,0), Math::vec3(0,1,0));

	System::Window::Instance()->SetTitle(L"OpenGL static object test");
	System::Mouse::Instance()->LockInWindow(false);
	OpenGL::Driver::Instance()->Start();

	System::EventManager::Instance()->SubscribeHandler(System::EVENT_IDLE, System::EventHandler(Idle));
	System::EventManager::Instance()->SubscribeHandler(System::EVENT_MOUSE_LBUTTON_DOWN, System::EventHandler(OnMouseLeftButtonDown));	
	System::EventManager::Instance()->SubscribeHandler(System::EVENT_MOUSE_LBUTTON_UP, System::EventHandler(OnMouseLeftButtonUp));
	System::EventManager::Instance()->SubscribeHandler(System::EVENT_MOUSE_MOVE, System::EventHandler(OnMouseMove));

	m_textures.reset(new OpenGL::TextureContext);

	m_object = OpenGL::StaticObjectManager::Instance()->Load(L"cube.static_vao");

	rc.reset(new OpenGL::RenderContextBumpMapping);	
	OpenGL::RenderTargetBackBuffer::RenderTargetBackBufferProperties p;		
	rt = OpenGL::Driver::Instance()->CreateRenderTarget(&p);
	rt->SetClearColor(0.6, 0.6, 0.6, 1);

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
