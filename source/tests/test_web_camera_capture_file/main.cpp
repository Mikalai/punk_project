#include "../../punk_engine.h"


std::auto_ptr<Virtual::Cameras::FirstPersonCamera> g_camera;
OpenGL::RenderTarget* rt;
OpenGL::Frame frame;
std::auto_ptr<OpenGL::RenderContextSolidTexture3D> rc;
std::auto_ptr<OpenGL::QuadObject> m_quad;

std::unique_ptr<OpenGL::Texture2D> g_camera_texture;

void* buffer;
int length;

bool m_left_down = false;

float x = 0;
float y = 0;

CRITICAL_SECTION cs;

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

	OpenGL::TextureContext* texture_context = new OpenGL::TextureContext;

	OpenGL::RenderContextSolidTexture3D::PolicyParameters* p = new OpenGL::RenderContextSolidTexture3D::PolicyParameters;

	//EnterCriticalSection(&cs);
	g_camera_texture->Create(640, 480, GL_RGB, (const unsigned char*)buffer);
	//LeaveCriticalSection(&cs);

	p->m_proj_view_world = g_camera->GetViewProjectionMatrix()*Math::mat4::CreateRotation(1, 0, 0, x)*Math::mat4::CreateRotation(0, 1, 0, y);
	p->m_diffuse_color.Set(1, 1, 1, 1);
	p->m_diffuse_texture = 0;

	OpenGL::Batch* b = new OpenGL::Batch;
	b->m_textures.push_back(g_camera_texture.get()); //OpenGL::Texture2DManager::Instance()->Load(L"checker2.png"));
	b->m_parameters = p;
	b->m_renderable = m_quad.get();

	pass->SetRenderTarget(rt);
	pass->AddBatch(texture_context, rc.get(), b); 

	frame.Begin();
	frame.AddRenderPass(pass);
	frame.End();	

}

int main()
{
	//InitOpenCL();

	System::Window::Instance()->SetTitle(L"OpenGL Init test");
	System::Mouse::Instance()->LockInWindow(false);

	InitializeCriticalSection(&cs);
	length = Math::round_up(640*480*3, 256);
	buffer = new char[length];
	System::SetCriticalSection(&cs);	
	System::SetTexture(buffer, &length);	

	System::TestCamera();

	Virtual::Cameras::FirstPersonCameraOptions options;	
	g_camera.reset(new Virtual::Cameras::FirstPersonCamera(options));
	g_camera->SetPositionAndTarget(Math::vec3(0, 5, 5), Math::vec3(0,0,0), Math::vec3(0,1,0));

	
	OpenGL::Driver::Instance()->Start();

	System::EventManager::Instance()->SubscribeHandler(System::EVENT_IDLE, System::EventHandler(Idle));
	System::EventManager::Instance()->SubscribeHandler(System::EVENT_MOUSE_LBUTTON_DOWN, System::EventHandler(OnMouseLeftButtonDown));	
	System::EventManager::Instance()->SubscribeHandler(System::EVENT_MOUSE_LBUTTON_UP, System::EventHandler(OnMouseLeftButtonUp));
	System::EventManager::Instance()->SubscribeHandler(System::EVENT_MOUSE_MOVE, System::EventHandler(OnMouseMove));

	m_quad.reset(new OpenGL::QuadObject);
	m_quad->Cook(2,2);

	rc.reset(new OpenGL::RenderContextSolidTexture3D);	
	OpenGL::RenderTargetBackBuffer::RenderTargetBackBufferProperties p;		
	rt = OpenGL::Driver::Instance()->CreateRenderTarget(&p);
	rt->SetClearColor(1, 0, 0, 1);
	
	g_camera_texture.reset(new OpenGL::Texture2D);
	g_camera_texture->Create(640, 480, 0, 0);
	

	if (!rt)
	{
		out_error() << "Render target was not created" << std::endl;
		return 0;
	}

	System::Window::Instance()->Loop();

	delete buffer;
	g_camera_texture.release();
	
	System::MegaDestroyer::Destroy();

	DeleteCriticalSection(&cs);
	return 0;
}
