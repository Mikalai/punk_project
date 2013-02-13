#ifndef _H_PUNK_APPLICATION
#define _H_PUNK_APPLICATION

#include "../config.h"
#include "../system/module.h"
#include "../gpu/module.h"
#include "application_config.h"
#include "../gui/gui_adapter.h"
#include "../gui/interface.h"
#include "../physics/interface.h"

namespace Punk
{

	class PUNK_ENGINE Application : public System::WindowAdapter, public GUI::Adapter
	{
	public:
		Application();	
		virtual ~Application();
		System::Window* GetWindow();
		System::EventManager* GetEventManager();
		GPU::OpenGL::Driver* GetDriver();
		Virtual::TerrainManager* GetTerrainManager();
		GUI::Manager* GetGUIManager();

		int Run();		
		void SetTimeScale(__int64 nominator, __int64 denominator);

		virtual void OnIdleEvent(System::IdleEvent* event);
		virtual void OnMouseMiddleButtonUpEvent(System::MouseMiddleButtonUpEvent* event);
		virtual void OnMouseMiddleButtonDownEvent(System::MouseMiddleButtonDownEvent* event);
		virtual void OnMouseRightButtonUpEvent(System::MouseRightButtonUpEvent* event);
		virtual void OnMouseRightButtonDownEvent(System::MouseRightButtonDownEvent* event);
		virtual void OnMouseLeftButtonUpEvent(System::MouseLeftButtonUpEvent* event);
		virtual void OnMouseLeftButtonDownEvent(System::MouseLeftButtonDownEvent* event);
		virtual void OnMouseHooverEvent(System::MouseHooverEvent* event);
		virtual void OnMouseMoveEvent(System::MouseMoveEvent* event);
		virtual void OnMouseWheelEvent(System::MouseWheelEvent* event);
		virtual void OnCharEvent(System::KeyCharEvent* value);
		virtual void OnWideCharEvent(System::KeyWCharEvent* event);
		virtual void OnKeyDownEvent(System::KeyDownEvent* event);
		virtual void OnKeyUpEvent(System::KeyUpEvent* event);
		virtual void OnResizeEvent(System::WindowResizeEvent* event);
		virtual void OnCreateEvent();
		virtual void OnDestroyEvent();
		virtual void OnSetFocusedEvent(GUI::SetFocusedEvent* event);
		virtual void OnSetUnFocusedEvent(GUI::SetUnFocusedEvent* event);
		virtual void OnMouseEnterEvent(GUI::MouseEnterEvent* event);
		virtual void OnMouseLeaveEvent(GUI::MouseLeaveEvent* event);

		virtual void Init(const Config& value);

	private:
		System::Window* m_window;
		System::EventManager* m_event_manager;
		GPU::OpenGL::Driver* m_video_driver;
		Physics::BulletSimulator* m_simulator;
		Virtual::TerrainManager* m_terrain_manager;

		System::Timer m_timer;	

		void Step(System::Event* event);
		void Render();
		
		//
		//	to perform speed up and slow down	
		//
		__int64 m_time_scale_nominator;
		__int64 m_time_scale_denomiator;


	};
}

#endif