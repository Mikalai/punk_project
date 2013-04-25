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
		GPU::VideoDriver* GetVideoDriver();
		Virtual::TerrainManager* GetTerrainManager();
		GUI::Manager* GetGUIManager();
		Physics::Simulator* GetSimulator();
		GPU::PaintEngine* GetPaintEngine();
        System::Mouse* GetMouse();

		int Run();
		void SetTimeScale(__int64 nominator, __int64 denominator);

		virtual void OnIdleEvent(System::IdleEvent* event) override;
		virtual void OnMouseMiddleButtonUpEvent(System::MouseMiddleButtonUpEvent* event) override;
		virtual void OnMouseMiddleButtonDownEvent(System::MouseMiddleButtonDownEvent* event) override;
		virtual void OnMouseRightButtonUpEvent(System::MouseRightButtonUpEvent* event) override;
		virtual void OnMouseRightButtonDownEvent(System::MouseRightButtonDownEvent* event) override;
		virtual void OnMouseLeftButtonUpEvent(System::MouseLeftButtonUpEvent* event) override;
		virtual void OnMouseLeftButtonDownEvent(System::MouseLeftButtonDownEvent* event) override;
		virtual void OnMouseHooverEvent(System::MouseHooverEvent* event) override;
		virtual void OnMouseMoveEvent(System::MouseMoveEvent* event) override;
		virtual void OnMouseWheelEvent(System::MouseWheelEvent* event) override;
		virtual void OnCharEvent(System::KeyCharEvent* value) override;
		virtual void OnWideCharEvent(System::KeyWCharEvent* event) override;
		virtual void OnKeyDownEvent(System::KeyDownEvent* event) override;
		virtual void OnKeyUpEvent(System::KeyUpEvent* event) override;
		virtual void OnResizeEvent(System::WindowResizeEvent* event) override;
		virtual void OnCreateEvent() override;
		virtual void OnDestroyEvent() override;
		virtual void OnSetFocusedEvent(GUI::SetFocusedEvent* event) override;
		virtual void OnSetUnFocusedEvent(GUI::SetUnFocusedEvent* event) override;
		virtual void OnMouseEnterEvent(GUI::MouseEnterEvent* event) override;
		virtual void OnMouseLeaveEvent(GUI::MouseLeaveEvent* event) override;

		virtual void Init(const Config& value);

	private:
		GPU::PaintEngine* m_paint_engine;
		System::Window* m_window;
		System::EventManager* m_event_manager;
		GPU::VideoDriver* m_video_driver;
		Physics::Simulator* m_simulator;
		Virtual::TerrainManager* m_terrain_manager;
		System::Timer m_timer;
        System::Mouse* m_mouse;
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
