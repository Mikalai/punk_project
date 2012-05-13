#include "../punk_engine/punk_engine.h"
#include <iostream>

class Viewer
{
	std::auto_ptr<GUI::Manager> m_gui;
	OpenGL::Driver m_driver;
	std::auto_ptr<OpenGL::RenderContextSkinning> m_skinning_context;
	std::auto_ptr<OpenGL::RenderContextLight> m_rc;
	Utility::Camera m_camera;
	float x, y, z;
	std::vector<std::shared_ptr<Utility::StaticMesh>> m_meshes; 
	std::vector<std::shared_ptr<OpenGL::StaticObject>> m_vaos;

	std::auto_ptr<Utility::StaticMesh> m_small_box;
	std::auto_ptr<OpenGL::StaticObject> m_small_box_vao;
	Utility::Armature* m_armature;
	Utility::Scene scene;
public:

	Viewer(const char* filename)
	{		
		/// Load scene
		scene.Load(System::string(filename));
		int objects_count = scene.GetObjectsCount();
		m_meshes.resize(objects_count);
		m_vaos.resize(objects_count);
		for (int i = 0; i < objects_count; ++i)
		{
			const System::string& name = scene.GetObjectName(i);
			m_meshes[i].reset(scene.CookSkinnedMesh(name));
		}

		scene.Load(L"small_box.pmd");
		m_small_box.reset(scene.CookStaticMesh(L"Cube"));

		m_armature = scene.GetArmature(L"Armature");
		//m_armature->GetArmatureAnimation().EnableTrack(L"die", true);
		m_armature->GetArmatureAnimation().EnableTrack(L"stand", true);		
		//m_armature->GetArmatureAnimation().EnableTrack(L"ArmatureAction", true);		
		m_armature->SetMeshOffset(m_meshes[0]->GetMeshOffset());
		//m_armature->PrintDebug(0, 0);
		//exit(0);
		/// start driver
		m_driver.Start(System::Window::GetInstance());
		m_driver.SetClearColor(0.7, 0.6, 0, 1);

		/// initialize different render contexts
		m_skinning_context.reset(new OpenGL::RenderContextSkinning());
		m_rc.reset(new OpenGL::RenderContextLight());

		/// for each mesh create static vao
		for (int i = 0; i < objects_count; ++i)
		{
			m_vaos[i].reset(new OpenGL::StaticObject());
			m_vaos[i]->SetStaticObject(m_meshes[i].get());			
			m_vaos[i]->Init();
		}

		m_small_box_vao.reset(new OpenGL::StaticObject());
		m_small_box_vao->SetStaticObject(m_small_box.get());
		m_small_box_vao->Init();
		/// init camera staff
		x = y = z = 10;

		m_gui.reset(new GUI::Manager());		
		/*	GUI::Widget* w = new GUI::Widget(0, 0, 1, 1);
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
		btn->SetMouseLeftClickHandler(System::EventHandler(b, this, &Viewer::OnButtonPress));*/
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
		case System::PUNK_KEY_1:
			m_armature->GetArmatureAnimation().EnableTrack(L"stand", true);	
			break;
		case System::PUNK_KEY_2:
			m_armature->GetArmatureAnimation().EnableTrack(L"walk", true);	
			break;
		case System::PUNK_KEY_3:
			m_armature->GetArmatureAnimation().EnableTrack(L"seat", true);	
			break;
		}
	}

	void OnIdle(System::Event* event)
	{	
		m_driver.ClearBuffer(OpenGL::Driver::COLOR_BUFFER|OpenGL::Driver::DEPTH_BUFFER);				
		static float a = 0;
		a+= 0.1;

		m_armature->GetArmatureAnimation().UpdateBones(a);									
/*
		m_rc->SetWorldMatrix(Math::mat4::CreateRotation(-1, 0, 0, 3.14 / 2.0));
		m_rc->SetViewMatrix(m_camera.GetViewMatrix());
		m_rc->SetProjectionMatrix(Math::mat4::CreatePerspectiveProjection(Math::PI/4.0, 1.3, 0.1, 100.0));
		m_rc->SetAmbientColor(Math::vec4(0,0,0,0));
		m_rc->SetSpecularColor(Math::vec4(1,1,1,1));
		m_rc->SetDiffuseColor(Math::vec4(1,1,1,1));
		m_rc->SetSpecularPower(16);
		m_rc->SetLightPosition(Math::vec3(10, 1, 10));
		m_rc->Begin();
		m_small_box_vao->Bind(m_rc->GetSupportedVertexAttributes());
		for (int j = 0; j < m_armature->GetBonesCount(); ++j)
		{
			const Math::mat4& m = m_armature->GetBoneByIndex(j)->GetAnimatedGlobalMatrix() * Math::mat4::CreateScaling(0.5, 0.5, 0.5);
			m_rc->SetWorldMatrix(m);
			m_rc->Begin();
			m_small_box_vao->Render();
		}		
		m_small_box_vao->Unbind();
		m_rc->End();/**/
		
		for (int i = 0; i < m_vaos.size(); ++i)
		{
			m_armature->SetMeshOffset(m_meshes[i]->GetMeshOffset());			
			m_skinning_context->SetWorldMatrix(m_meshes[i]->GetMeshOffset());
			m_skinning_context->SetViewMatrix(m_camera.GetViewMatrix());
			m_skinning_context->SetProjectionMatrix(Math::mat4::CreatePerspectiveProjection(Math::PI/4.0, 1.3, 0.1, 100.0));
			m_skinning_context->SetAmbientColor(Math::vec4(0,0,0,0));
			m_skinning_context->SetSpecularColor(Math::vec4(1,1,1,1));
			m_skinning_context->SetDiffuseColor(Math::vec4(1,1,1,1));
			m_skinning_context->SetSpecularPower(16);
			m_skinning_context->SetLightPosition(Math::vec3(10, 1, 10));

			for (int j = 0; j < m_armature->GetBonesCount(); ++j)
			{
				const Math::mat4& m = m_meshes[i]->GetMeshOffset().Inversed()*m_armature->GetBoneByIndex(j)->GetAnimatedGlobalMatrix()*m_meshes[i]->GetMeshOffset();
				m_skinning_context->SetBoneMatrix(j, m);
			}

			m_skinning_context->Begin();				
			m_vaos[i]->Bind(m_skinning_context->GetSupportedVertexAttributes());
			m_vaos[i]->Render();		
			m_vaos[i]->Unbind();
		}
		m_skinning_context->End();			

		m_gui->Render();/**/

		m_driver.SwapBuffers();
	}
};

int main(int argc, char** argv)
{
	System::Window::GetInstance()->SetTitle(L"Тэст скуры");
	System::Mouse::GetInstance()->LockInWindow(true);
	OpenGL::Module module;
	module.Init();
	Viewer viewer("animated_male2.pmd");
	System::EventManager::GetInstance()->SubscribeHandler(System::EVENT_IDLE, System::EventHandler(&viewer, &Viewer::OnIdle));
	System::EventManager::GetInstance()->SubscribeHandler(System::EVENT_KEY_DOWN, System::EventHandler(&viewer, &Viewer::OnKeyDown));
	System::Window::GetInstance()->Loop();

	module.Destroy();

	return 0;
}