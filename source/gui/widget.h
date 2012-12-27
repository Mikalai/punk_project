#ifndef _H_PUNK_GUI_WIDGET
#define _H_PUNK_GUI_WIDGET

#include <vector>
#include <memory>
#include "../system/types.h"
#include "../system/compound_object.h"
#include "../string/string.h"
#include "../config.h"
//#include "../opengl/driver.h"
#include "../math/math.h"
#include "../opengl/textures/text_surface.h"

namespace GUI
{
	class IGUIRender;

	class Manager;

	class PUNK_ENGINE Widget : public System::CompoundObject
	{
	public:

		enum ColorType {ACTIVE_COLOR = 1, INACTIVE_COLOR, TEXT_ACTIVE_COLOR, TEXT_INACTIVE_COLOR};

		enum VerticalAlign { VERTICAL_ALIGN_TOP, VERTICAL_ALIGN_CENTER, VERTICAL_ALIGN_BOTTOM };
		enum HorizontalAlign { HORIZONTAL_ALIGHT_LEFT, HORIZONTAL_ALIGN_CENTER, HORIZONTAL_ALIGN_RIGHT};

	public:

		Widget(float x = 0, float y = 0, float width = 1, float height = 1, const System::string& text = L"", Widget* parent = 0);

		virtual ~Widget();
		virtual void SetText(const System::string& text);

		void SetVerticalTextAlign(VerticalAlign v) { m_vertical_align = v; }
		void SetHorizontalTextAlign(HorizontalAlign v) { m_horizontal_align = v; }
		VerticalAlign SetVerticalTextAlign(VerticalAlign v) const { return m_vertical_align; }
		HorizontalAlign SetHorizontalTextAlign(HorizontalAlign v) const { return m_horizontal_align; }

		void SetParent(Widget* w) { m_parent = w; }
		Widget* GetParent() { return m_parent; }
		const Widget* GetParent() const { return m_parent; }

		void SetWidth(float width);
		void SetHeight(float height);
		float GetWidth() const;
		float GetHeight() const;
		float GetScreenWidth() const;
		float GetScreenHeight() const;		
		float GetX() const;
		float GetY() const;
		float GetScreenX() const;
		float GetScreenY() const;
		void SetX(float x);
		void SetY(float y);
		bool IsVisible() const;
		bool IsEnabled() const;
		void Show(bool isVisible);
		void Enable(bool isEnabled);
		void FixPosition(bool isFixed);
		bool IsFixedPosition() const;
		void SetSize(float x, float y, float width, float height);
		void SetColor(ColorType type, float r, float g, float b, float a);		
		void SetFont(const System::string& font);
		void SetTextSize(int size);
		int GetTextSize() const {return m_fontSize;}
		void SetAnyData(void* data);
		void* GetAnyData();


		const System::string& GetText() const;
		void SetFocuse(bool isFocused);

		virtual void SetNextWidget(Widget* widget);	
		virtual void SetPrevWidget(Widget* widget);
		Widget* GetNextWidget() { return m_next_widget; }
		Widget* GetPrevWidget() { return m_prev_widget; }
		virtual void Render(IGUIRender* render) const;

		bool IsPointIn(const Math::vec2& point_in_viewport) const;
		Widget* GetFocused(float x, float y);
		bool IsCursorIn() const;

		void Store(System::Buffer& buffer) {}
		void Restore(System::Buffer& buffer) {}

		System::Proxy<OpenGL::Texture2D> GetTextTexture() const;
		void SetBackgroundTexture(System::Proxy<OpenGL::Texture2D> texture);
		System::Proxy<OpenGL::Texture2D> GetBackgroundTexture() const;

		const Manager* GetManager() const;
		Manager* GetManager();
		void SetManager(Manager* manager);

		/// Work with color goes here
		Math::Vector4<float>& BackColor0();
		Math::Vector4<float>& BackColor1();
		Math::Vector4<float>& TextColor0();
		Math::Vector4<float>& TextColor1();

		const Math::Vector4<float>& BackColor0() const;
		const Math::Vector4<float>& BackColor1() const;
		const Math::Vector4<float>& TextColor0() const;
		const Math::Vector4<float>& TextColor1() const;

		const Math::Vector4<float>& TextColor() const;
		const Math::Vector4<float>& BackColor() const;

		/*********************************************************************/
		/*	Handlers
		/*********************************************************************/

		void SetMouseLeftClickHandler(System::Handler onLeftClick);
		void SetMouseRightClickHandler(System::Handler onRightClick);
		void SetMouseMiddleClickHandler(System::Handler onMiddleClick);
		void SetMouseEnterHandler(System::Handler onMouseEnter);
		void SetMouseLeaveHandler(System::Handler onMouseLeave);
		void SetMouseMoveHandler(System::Handler onMouseMove);
		void SetCharHandler(System::Handler onChar);
		void SetKeyDownHandler(System::Handler onKeyDown);
		void SetKeyUpHandler(System::Handler onKeyUp);
		void SetWheelHandler(System::Handler onWheel);
		void SetIdleHandler(System::Handler onIdle);
		void SetResizedHandler(System::Handler onResized);


		friend class Manager;

		static const Math::Vector2<float> WindowToViewport(float x, float y);

	protected:

		VerticalAlign m_vertical_align;
		HorizontalAlign m_horizontal_align;

		float m_width;
		float m_height;
		float m_x, m_y;

		int m_fontSize;

		Math::Vector4<float> m_back_color_0;
		Math::Vector4<float> m_back_color_1;
		Math::Vector4<float> m_text_color_0;
		Math::Vector4<float> m_text_color_1;
		Math::Vector4<float> m_back_color;
		Math::Vector4<float> m_text_color;
		float m_animation;
		float m_animation_duration;
		float m_animation_speed;

		bool m_isVisible;
		bool m_isEnabled;
		bool m_isCursorIn;
		bool m_leftButtonDown;
		bool m_rightButtonDown;
		bool m_middleButtonDown;
		bool m_moveable;
		bool m_isFocused;

		System::string m_text;
		System::string m_font;

		Widget* m_next_widget;	
		Widget* m_prev_widget;

		System::Proxy<OpenGL::TextSurface> m_text_texture;
		System::Proxy<OpenGL::Texture2D> m_background_texture;

		void* m_any_data;

		Widget* m_parent;
		Manager* m_manager;

		/******************************************************************/
		/*			LIST OF HANDLERS
		/******************************************************************/
	protected:

		System::Handler m_OnLeftClick;
		System::Handler m_OnRightClick;
		System::Handler m_OnMiddleClick;
		System::Handler m_OnMouseEnter;
		System::Handler m_OnMouseLeave;
		System::Handler m_OnMouseMove;
		System::Handler m_OnChar;
		System::Handler m_OnKeyDown;
		System::Handler m_OnKeyUp;
		System::Handler m_OnWheel;
		System::Handler m_OnIdle;
		System::Handler m_OnResized;

	protected:		
		virtual bool OnResize(System::WindowResizeEvent* event);
		virtual bool OnMouseMove(System::MouseMoveEvent* event);
		virtual bool OnIdle(System::IdleEvent* event);
		virtual bool OnMouseEnter(System::MouseEnterEvent* event);
		virtual bool OnMouseLeave(System::MouseLeaveEvent* event);
		virtual bool OnMouseLeftButtonDown(System::MouseLeftButtonDownEvent* event);
		virtual bool OnMouseLeftButtonUp(System::MouseLeftButtonUpEvent* event);
		virtual bool OnMouseWheel(System::MouseWheelEvent* event);
		virtual bool OnKeyChar(System::KeyCharEvent* event);	
		virtual bool OnKeyDown(System::KeyDownEvent* event);	
		virtual bool OnAdd(System::Proxy<System::Object> object);
		//virtual bool OnRemove(System::Proxy<System::Object> object);
	};
}

#endif