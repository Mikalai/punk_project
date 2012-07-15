#include "../punk_engine/system/string.h"
#include "../punk_engine/system/system.h"
#include "../punk_engine/math/math.h"
#include "../punk_engine/images/images.h"
#include "../punk_engine/utility/utility.h"
#include "../punk_engine/system/driver/video/driver.h"
#include "../punk_engine/system/application/application.h"
#include "../punk_engine/render/render.h"

using namespace OpenGL;

class Test
{
	OpenGL::Driver m_driver;
	std::auto_ptr<Render::SimpleRender> m_render;
	std::auto_ptr<OpenGL::QuadObject> m_quad;
	std::auto_ptr<OpenGL::GridObject> m_grid;
	std::auto_ptr<OpenGL::StaticObject> m_static_vao;
	std::auto_ptr<Utility::StaticMesh> m_static_mesh;
	ImageModule::RGBImage m_image;
	ImageModule::RGBImage m_gray_image;
	std::auto_ptr<OpenGL::Texture2D> m_texture;
	std::auto_ptr<OpenGL::Texture2D> m_height_map;
	std::auto_ptr<OpenGL::TextureContext> m_texture_context;
	Utility::Camera m_camera;
	float x, y, z;
public:
	
	Test()
	{
		Utility::Scene scene;
		scene.Load(L"simple_house.pmd");
		m_static_mesh.reset(scene.CookStaticMesh(L"Cube"));
		System::Buffer buffer;
		m_static_mesh->Save(buffer);
		System::BinaryFile::Save(System::Environment::Instance()->GetModelFolder() + L"simple_house.mesh", buffer);

		x = y = z = 10;
		m_driver.Start(System::Window::Instance());
		m_driver.SetClearColor(0.7, 0.6, 0, 1);

		m_static_vao.reset(new OpenGL::StaticObject());
		m_static_vao->SetStaticObject(m_static_mesh.get());
		m_static_vao->Init();

		m_quad.reset(new OpenGL::QuadObject());
		m_quad->Init();

		m_grid.reset(new OpenGL::GridObject());
		m_grid->SetWidth(1);
		m_grid->SetHeight(1);
		m_grid->SetHeightSlice(16);
		m_grid->SetWidthSlice(16);
		m_grid->Init();/**/

		m_image = ImageModule::Importer().LoadRGB(System::Environment::Instance()->GetTexutreFolder() + L"diffuse_map2.png");
		m_gray_image = ImageModule::Importer().LoadRGB(System::Environment::Instance()->GetTexutreFolder() + L"house_normal2.png");
		m_height_map.reset(new OpenGL::Texture2D(m_gray_image));		
		m_texture.reset(new OpenGL::Texture2D(m_image));

		//m_texture.reset(new OpenGL::Texture2D(m_image));
		//m_texture_context.reset(new OpenGL::TextureContext());
		//m_texture_context->SetTexture0(m_texture.release());
		//m_texture_context->SetTexture1(m_height_map.release());
	//	m_camera.SetPositionAndDirection(Math::vec3(0,1.8, 0), Math::vec3(0, 0, 1), Math::vec3(0,1,0));
	//	m_camera.SetProperties(Math::PI/4, 1.3, 1, 1000);				
		m_render.reset(new Render::SimpleRender);
	}

	void OnMouseMove(System::Event* event)
	{
		System::MouseMoveEvent& e = static_cast<System::MouseMoveEvent&>(*event);
	}

	void OnKeyDown(System::Event* event)
	{
		System::KeyDownEvent& e = static_cast<System::KeyDownEvent&>(*event);
		switch (e.key)
		{
		case System::PUNK_KEY_A:
			x -= 1;
			break;
		case System::PUNK_KEY_D:
			x += 1;
			break;
		case System::PUNK_KEY_SHIFT:
			System::Mouse::Instance()->LockInWindow(!System::Mouse::Instance()->IsLocked());
			break;
		}
	}

	void OnIdle(System::Event* event)
	{		
		m_render->AddStaticRenderable(Render::StaticRenderable::Build(m_static_vao.get(), m_texture.get(), m_height_map.get(), Math::mat4::CreateTranslate(0, 0, 0)));
		
		m_render->AddStaticRenderable(Render::StaticRenderable::Build(m_static_vao.get(), m_texture.get(), m_height_map.get(), Math::mat4::CreateTranslate(0, 0, 5)));

		m_render->AddStaticRenderable(Render::StaticRenderable::Build(m_static_vao.get(), m_texture.get(), m_height_map.get(), Math::mat4::CreateTranslate(0, 0, -10)*Math::mat4::CreateRotation(0, 1, 0, Math::PI/4.0)));

		m_render->SetViewMatrix(m_camera.GetViewMatrix());
		m_render->SetProjectionMatrix(m_camera.GetProjectionMatrix());		
		m_render->Process();
		m_driver.SwapBuffers();
	}
};

int main()
{
	System::Window::Instance()->SetTitle(L"Punk Render Pipeline Test");
	System::Mouse::Instance()->LockInWindow(true);
	System::Mouse::Instance()->Show(true);
	OpenGL::Module module;
	module.Init();
	Test test;
	System::EventManager::Instance()->SubscribeHandler(System::EVENT_IDLE, System::EventHandler(&test, &Test::OnIdle));
	System::EventManager::Instance()->SubscribeHandler(System::EVENT_KEY_DOWN, System::EventHandler(&test, &Test::OnKeyDown));
	System::EventManager::Instance()->SubscribeHandler(System::EVENT_MOUSE_MOVE, System::EventHandler(&test, &Test::OnMouseMove));
	System::Window::Instance()->Loop();

	module.Destroy();
	return 0;
}