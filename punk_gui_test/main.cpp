#include <iostream>

#include "../punk_engine/punk_engine.h"
#include "field.h"
#include "main_menu.h"
#include "character_control.h"
#include "building.h"
#include "monster.h"

class Viewer
{
	std::auto_ptr<Field> m_field;
	std::auto_ptr<CharacterControl> m_cc;
	std::auto_ptr<MonsterControl> m_monster;
	MainMenu* m_main_menu;
	std::auto_ptr<GUI::Manager> m_gui;
	OpenGL::Driver m_driver;
	std::auto_ptr<OpenGL::RenderContextLight> m_light_context;
	std::auto_ptr<OpenGL::RenderContextBumpMapping> m_bump_context;
	Utility::Camera m_camera;
	System::Timer m_timer;
	float angle;
	bool m_game;

	std::auto_ptr<Building> m_building;
public:
	
	Viewer()
	{		
		angle = 0;
		m_game = false;
		/// start driver
		m_driver.Start(System::Window::Instance());
		System::Window::Instance()->SetSize(800, 600);
		System::Window::Instance()->SetPosition(200, 100);
		m_driver.SetClearColor(0.2, 0.2, 1, 1);
	
		m_gui.reset(new GUI::Manager());
		
		m_main_menu = new MainMenu;
		m_main_menu->OnStartResumeClick(System::EventHandler(this, &Viewer::OnStartButton));
		m_main_menu->OnQuitClick(System::EventHandler(this, &Viewer::OnQuitButton));

		m_gui->AddRootWidget(m_main_menu);

		m_field.reset(new Field);
		m_field->GetTerrain()->SetScale(0.1);
		m_field->SetCameraReference(&m_camera);	

		//m_camera.SetPositionAndDirection(Math::vec3(1000, 200, 1000), Math::vec3(0,0,-1), Math::vec3(0, 1, 0));
		
		m_camera.SetPositionAndTarget(Math::vec3(1002, 202, 1002), Math::vec3(1000,201,1000), Math::vec3(0, 1, 0));

		m_cc.reset(new CharacterControl);
		m_cc->SetLocation(Math::mat4::CreateTranslate(1000, 200, 1000)*Math::mat4::CreateRotation(0, 1, 0, Math::PI/8));
		m_cc->SetCamera(&m_camera);
		m_cc->SetField(m_field.get());

		m_monster.reset(new MonsterControl);
		m_monster->SetLocation(Math::mat4::CreateTranslate(990, 200, 1000)*Math::mat4::CreateRotation(0, 1, 0, Math::PI/8));
		m_monster->SetCamera(&m_camera);
		m_monster->SetField(m_field.get());

		System::EventManager::Instance()->SubscribeHandler(System::EVENT_MOUSE_MOVE, System::EventHandler(this, &Viewer::OnMouseMove));
		System::EventManager::Instance()->SubscribeHandler(System::EVENT_KEY_DOWN, System::EventHandler(this, &Viewer::OnKeyDown));
		System::EventManager::Instance()->SubscribeHandler(System::EVENT_KEY_UP, System::EventHandler(this, &Viewer::OnKeyUp));
		System::EventManager::Instance()->SubscribeHandler(System::EVENT_MOUSE_RBUTTON_DOWN, System::EventHandler(this, &Viewer::OnMouseRightDown));
		System::EventManager::Instance()->SubscribeHandler(System::EVENT_MOUSE_RBUTTON_UP, System::EventHandler(this, &Viewer::OnMouseRightUp));
		System::EventManager::Instance()->SubscribeHandler(System::EVENT_MOUSE_LBUTTON_DOWN, System::EventHandler(this, &Viewer::OnMouseLeftDown));

		m_building.reset(new Building);

		m_timer.UpdateStartPoint();
	}

	void OnStartButton(System::Event*)
	{
		m_main_menu->Show(false);
		m_game = true;			
	}

	void OnQuitButton(System::Event*)
	{
		System::Window::Instance()->BreakMainLoop();
	}
	
	void OnClear(System::Event*)
	{
	}

	void OnDelete(System::Event*)
	{
	}

	void OnLoad(System::Event*)
	{
	}

	void OnSave(System::Event*)
	{		
	}

	void ListAllFood()
	{
	}

	void OnButtonPress(System::Event* event)
	{
	}

	void OnMouseMove(System::Event* event)
	{
		System::MouseMoveEvent* e = (System::MouseMoveEvent*)(event);
		if (m_game)
		{
			m_cc->RotateHorizontal((e->x - e->x_prev) / 180.0f * Math::PI);
			m_cc->RotateVertical((e->y - e->y_prev) / 180.0f * Math::PI);
		}
	}

	void OnKeyDown(System::Event* event)
	{
		System::KeyDownEvent* e = static_cast<System::KeyDownEvent*>(event);
		switch (e->key)
		{
		case System::PUNK_KEY_ESCAPE:
			m_main_menu->Show(true);
			m_game = false;
			break;			
		case System::PUNK_KEY_W:
			m_cc->Forward();
			break;
		case System::PUNK_KEY_2:
			m_cc->Forward();
			break;
		case System::PUNK_KEY_3:
			m_cc->Die();
			break;
		}
	}

	void OnMouseLeftDown(System::Event* event)
	{
		if (m_game)
		{
			m_cc->Fire();
		}
	}

	void OnMouseRightDown(System::Event* event)
	{
		System::MouseRightButtonDownEvent* e = (System::MouseRightButtonDownEvent*)(event);
		m_cc->Aiming(true);
	}

	void OnMouseRightUp(System::Event* event)
	{
		System::MouseRightButtonUpEvent* e = (System::MouseRightButtonUpEvent*)(event);
		m_cc->Aiming(false);
	}

	void OnKeyUp(System::Event* event)
	{
		System::KeyUpEvent* e = static_cast<System::KeyUpEvent*>(event);
		switch (e->key)
		{
		case System::PUNK_KEY_ESCAPE:
			m_main_menu->Show(true);
			m_game = false;
			break;			
		case System::PUNK_KEY_W:			
			m_cc->Stop();
			break;
		case System::PUNK_KEY_2:
			m_cc->Forward();
			break;
		case System::PUNK_KEY_3:
			m_cc->Die();
			break;
		}
	}

	void OnIdle(System::Event* event)
	{	
		if (m_game)
		{
			float time = m_timer.GetCurrentSystemTimeUS();
			float delta = m_timer.GetElapsedTime();;
			m_field->Update(time, delta);
			m_cc->Update(time, delta);
			m_monster->Update(time, delta);
			m_timer.UpdateStartPoint();
			System::IdleEvent* e = (System::IdleEvent*)event;
			m_cc->Update(e->elapsed_time_s);
			m_monster->Update(e->elapsed_time_s);
		}

		m_driver.ClearBuffer(OpenGL::Driver::COLOR_BUFFER|OpenGL::Driver::DEPTH_BUFFER);				
		
		if (m_game)
		{			
			m_field->Render();
			m_monster->Render();
			m_cc->Render();					
			m_building->Render(&m_camera, m_field->GetTerrain());
		}

		m_gui->Render();		
		m_driver.SwapBuffers();
	}
};

int main(int argc, char** argv)
{
	System::Window::Instance()->SetTitle(L"Trash");	
	System::Mouse::Instance()->LockInWindow(false);
	OpenGL::Module module;
	module.Init();
	Viewer viewer;
	System::EventManager::Instance()->SubscribeHandler(System::EVENT_IDLE, System::EventHandler(&viewer, &Viewer::OnIdle));
	System::EventManager::Instance()->SubscribeHandler(System::EVENT_KEY_DOWN, System::EventHandler(&viewer, &Viewer::OnKeyDown));
	System::Window::Instance()->Loop();

	module.Destroy();

	return 0;
}