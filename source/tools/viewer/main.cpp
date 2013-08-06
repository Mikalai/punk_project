#include <iostream>

#include "../system/string.h"
#include "../system/system.h"
#include "../math/math.h"
#include "../images/images.h"
#include "../utility/utility.h"
#include "../system/driver/video/driver.h"
#include "../system/application/application.h"

class Viewer
{
	OpenGL::Driver m_driver;
	std::unique_ptr<OpenGL::RenderContextLight> m_light_context;
	Utility::Camera m_camera;
	float x, y, z;
	std::vector<std::shared_ptr<Utility::StaticMesh>> m_meshes;
	std::vector<std::shared_ptr<OpenGL::StaticObject>> m_vaos;
public:

	Viewer(const char* filename)
	{
		Utility::Scene scene;
		/// Load scene
		scene.Load(System::string(filename));
		int objects_count = scene.GetObjectsCount();
		m_meshes.resize(objects_count);
		m_vaos.resize(objects_count);
		for (int i = 0; i < objects_count; ++i)
		{
			const System::string& name = scene.GetObjectName(i);
			m_meshes[i].reset(scene.CookStaticMesh(name));
		}

		/// start driver
		m_driver.Start(System::Window::Instance());
		m_driver.SetClearColor(0.7, 0.6, 0, 1);

		/// initialize different render contexts
		m_light_context.reset(new OpenGL::RenderContextLight());

		/// for each mesh create static vao
		for (int i = 0; i < objects_count; ++i)
		{
			m_vaos[i].reset(new OpenGL::StaticObject());
			m_vaos[i]->SetStaticObject(m_meshes[i].get());
			m_vaos[i]->Init();
		}

		/// init camera staff
		x = y = z = 10;
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
		}
	}

	void OnIdle(System::Event* event)
	{
		static float a override;
		a+override.001;

		m_driver.ClearBuffer(OpenGL::Driver::COLOR_BUFFER|OpenGL::Driver::DEPTH_BUFFER);
		for (int i = 0; i < m_vaos.size(); ++i)
		{
			m_light_context->SetWorldMatrix(Math::mat4::CreateTranslate(0, 0, i*10));
			m_light_context->SetViewMatrix(m_camera.GetViewMatrix());
			m_light_context->SetProjectionMatrix(Math::mat4::CreatePerspectiveProjection(Math::PI/4.0, 1.3, 0.1, 100.0));
			m_light_context->SetAmbientColor(Math::vec4(0,0,0,0));
			m_light_context->SetSpecularColor(Math::vec4(1,1,1,1));
			m_light_context->SetDiffuseColor(Math::vec4(1,1,1,1));
			m_light_context->SetSpecularPower(16);
			m_light_context->SetLightPosition(Math::vec3(10, 1, 10));
			m_light_context->Begin();
			m_vaos[i]->Bind(m_light_context->GetSupportedVertexAttributes());
			m_vaos[i]->Render();
			m_vaos[i]->Unbind();
			m_light_context->End();
		}

		m_driver.SwapBuffers();
	}
};

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cout << "Need file to render" << std::endl;
		return 0;
	}
	System::Window::Instance()->SetTitle(L"Punk Viewer");
	System::Mouse::Instance()->LockInWindow(true);
	OpenGL::Module module;
	module.Init();
	Viewer viewer(argv[1]);
	System::EventManager::Instance()->SubscribeHandler(System::EVENT_IDLE, System::EventHandler(&viewer, &Viewer::OnIdle));
	System::EventManager::Instance()->SubscribeHandler(System::EVENT_KEY_DOWN, System::EventHandler(&viewer, &Viewer::OnKeyDown));
	System::Window::Instance()->Loop();

	module.Destroy();

	return 0;
}
