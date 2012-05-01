#include <iostream>

#include "../punk_engine/system/string.h"
#include "../punk_engine/system/system.h"
#include "../punk_engine/math/math.h"
#include "../punk_engine/images/images.h"
#include "../punk_engine/utility/utility.h"
#include "../punk_engine/system/driver/video/driver.h"
#include "../punk_engine/gui/gui.h"

class Viewer
{
	std::auto_ptr<GUI::Manager> m_gui;
	OpenGL::Driver m_driver;
	std::auto_ptr<OpenGL::RenderContextLight> m_light_context;
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
		m_driver.Start(System::Window::GetInstance());
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

		m_gui.reset(new GUI::Manager());		
		GUI::Widget* w = new GUI::Widget(0, 0, 1, 1);
	//	m_gui->AddRootWidget(w);	
		GUI::Button* btn;
		w->AddChild(btn = new GUI::Button(0.2, 0.1, 0.5, 0.1));		
		w->AddChild(new GUI::VerticalSlider(0, 0, 0.1, 0.8f, 0, 100, 0));
		w->AddChild(new GUI::VerticalScrollBar(0.1, 0, 0.1, 1));
		w->AddChild(new GUI::TextBox(0.5, 0.9, 0.1, 0.1));
		w->AddChild(new GUI::TextBox(0.5, 0.6, 0.1, 0.1));
		GUI::ListBox* lb = new GUI::ListBox(0.7, 0, 0.1, 1);
		for (int i = 0; i < 20; ++i)
		{
			lb->AddItem(new GUI::ListBox::ListBoxItem("Item 1"));
			lb->AddItem(new GUI::ListBox::ListBoxItem("Item 2"));
		}
		w->AddChild(lb);
		GUI::TabWidget* tw = new GUI::TabWidget(0, 0, 1, 0.5, 0);
		tw->AddTab(L"Tab 1", w);
		tw->AddTab(L"Tab 2", new GUI::Widget(0, 0, 1, 1));
		m_gui->AddRootWidget(tw);

		GUI::Balloon* b = new GUI::Balloon(0.1, 0.8, 0.4, 0.1, L"Hello world", 0);
		b->SetText(L"I'm a cool balloon widget. I am the best of all the balloons widgets ever made in humanity. Yeah!. True I am incredible");
		m_gui->AddRootWidget(b);
		btn->SetMouseLeftClickHandler(System::EventHandler(b, this, &Viewer::OnButtonPress));
	}

	void OnButtonPress(System::Event* event)
	{
		GUI::Balloon* b = static_cast<GUI::Balloon*>(event->reciever);
		if (b)
		{
			b->Blink();
		}
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
		static float a = 0;
		a+= 0.001;

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
		}/**/

		m_gui->Render();
		
		m_driver.SwapBuffers();
	}
};

int main(int argc, char** argv)
{
	System::Window::GetInstance()->SetTitle(L"Тэставаньне графічнага інтэрфэйса картыстальніка");
	System::Mouse::GetInstance()->LockInWindow(true);
	OpenGL::Module module;
	module.Init();
	Viewer viewer("sklad.pmd");
	System::EventManager::GetInstance()->SubscribeHandler(System::EVENT_IDLE, System::EventHandler(&viewer, &Viewer::OnIdle));
	System::EventManager::GetInstance()->SubscribeHandler(System::EVENT_KEY_DOWN, System::EventHandler(&viewer, &Viewer::OnKeyDown));
	System::Window::GetInstance()->Loop();

	module.Destroy();

	return 0;
}