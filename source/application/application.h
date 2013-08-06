#ifndef _H_PUNK_APPLICATION
#define _H_PUNK_APPLICATION

#include "../config.h"
#include "../system/module.h"
#include "../gpu/module.h"
#include "application_config.h"
#include "../gui/gui_adapter.h"
#include "../gui/interface.h"
#include "../physics/interface.h"

namespace Utility
{
    class AsyncParser;
    class FontBuilder;
}

namespace Punk
{

	class PUNK_ENGINE_API Application : public System::WindowAdapter, public GUI::Adapter
	{
	public:
		Application();
		virtual ~Application();
		System::Window* GetWindow();
		System::EventManager* GetEventManager();
		Gpu::VideoDriver* GetVideoDriver();
		Virtual::TerrainManager* GetTerrainManager();
		GUI::Manager* GetGUIManager();
		Physics::Simulator* GetSimulator();
		Gpu::PaintEngine* GetPaintEngine();
        System::Mouse* GetMouse();
        Utility::AsyncParser* GetAsyncParser();

		int Run();
		void SetTimeScale(int64_t nominator, int64_t denominator);

		virtual void WndOnIdleEvent(System::IdleEvent* event) override;
		virtual void WndOnMouseMiddleButtonUpEvent(System::MouseMiddleButtonUpEvent* event) override;
		virtual void WndOnMouseMiddleButtonDownEvent(System::MouseMiddleButtonDownEvent* event) override;
		virtual void WndOnMouseRightButtonUpEvent(System::MouseRightButtonUpEvent* event) override;
		virtual void WndOnMouseRightButtonDownEvent(System::MouseRightButtonDownEvent* event) override;
		virtual void WndOnMouseLeftButtonUpEvent(System::MouseLeftButtonUpEvent* event) override;
		virtual void WndOnMouseLeftButtonDownEvent(System::MouseLeftButtonDownEvent* event) override;
		virtual void WndOnMouseHooverEvent(System::MouseHooverEvent* event) override;
		virtual void WndOnMouseMoveEvent(System::MouseMoveEvent* event) override;
		virtual void WndOnMouseWheelEvent(System::MouseWheelEvent* event) override;
		virtual void WndOnCharEvent(System::KeyCharEvent* value) override;
		virtual void WndOnWideCharEvent(System::KeyWCharEvent* event) override;
		virtual void WndOnKeyDownEvent(System::KeyDownEvent* event) override;
		virtual void WndOnKeyUpEvent(System::KeyUpEvent* event) override;
		virtual void WndOnResizeEvent(System::WindowResizeEvent* event) override;
		virtual void WndOnCreateEvent() override;
		virtual void WndOnDestroyEvent() override;
		virtual void OnSetFocusedEvent(GUI::SetFocusedEvent* event) override;
		virtual void OnSetUnFocusedEvent(GUI::SetUnFocusedEvent* event) override;
		virtual void OnMouseEnterEvent(GUI::MouseEnterEvent* event) override;
		virtual void OnMouseLeaveEvent(GUI::MouseLeaveEvent* event) override;
#ifdef _WIN32
		virtual LRESULT CustomDefWindowProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam) override;
#endif

		//	User can override next methods
        virtual void OnRender(Gpu::Frame* frame);		
		virtual void OnInit(const Config& value);
		virtual void OnResize(System::WindowResizeEvent* event);
		virtual void OnKeyDown(System::KeyDownEvent* event);
		virtual void OnKeyUp(System::KeyUpEvent* event);
		virtual void OnMouseWheel(System::MouseWheelEvent* event);
		virtual void OnMouseMove(System::MouseMoveEvent* event);
        virtual void OnMouseLeftButtonDown(System::MouseLeftButtonDownEvent* event);
        virtual void OnMouseRightButtonDown(System::MouseRightButtonDownEvent* event);
        virtual void OnDestroy();
        virtual void OnIdle(System::IdleEvent* event);

		void Init(const Config& value);
	private:
		void Clear();
	private:

        Utility::AsyncParser* m_async_parser;
        Utility::FontBuilder* m_font_builder;
		Gpu::PaintEngine* m_paint_engine;
		System::Window* m_window;
		System::EventManager* m_event_manager;
		Gpu::VideoDriver* m_video_driver;
		Physics::Simulator* m_simulator;
		Virtual::TerrainManager* m_terrain_manager;
		System::Timer m_timer;
        System::Mouse* m_mouse;
		void Step(System::Event* event);
		void Render();		
		void Resize(System::WindowResizeEvent* event);
		void KeyDown(System::KeyDownEvent* event);
		void KeyUp(System::KeyUpEvent* event);
		void MouseWheel(System::MouseWheelEvent* event);		
		void MouseMove(System::MouseMoveEvent* event);
        void MouseLeftButtonDown(System::MouseLeftButtonDownEvent* event);
        void MouseRightButtonDown(System::MouseRightButtonDownEvent* event);
        void Idle(System::IdleEvent* event);

		//
		//	to perform speed up and slow down
		//
		int64_t m_time_scale_nominator;
		int64_t m_time_scale_denomiator;

	};
}

#endif
