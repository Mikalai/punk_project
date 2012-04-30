#ifndef _H_PUNK_GUI_WIDGET
#define _H_PUNK_GUI_WIDGET

#include <vector>
#include "../system/system.h"
#include "../system/string.h"
#include "config.h"
#include "../system/driver/video/driver.h"
#include "../math/math.h"

namespace GUI
{
	class IGUIRender;

	class Manager;

	class LIB_GUI Widget
	{
	public:

		enum ColorType {ACTIVE_COLOR = 1, INACTIVE_COLOR, TEXT_ACTIVE_COLOR, TEXT_INACTIVE_COLOR};

	protected:

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

		Widget* m_parent;		
		std::vector<Widget*> m_children;

		OpenGL::Texture2D* m_text_texture;
		OpenGL::Texture2D* m_background_texture;

	
		/******************************************************************/
		/*			LIST OF HANDLERS
		/******************************************************************/
	protected:

		System::Handler m_OnLeftClick;
		System::Handler m_OnRightClick;
		System::Handler m_OnMiddleClick;
		System::Handler m_OnMouseEnter;
		System::Handler m_OnMouseLeave;
		System::Handler m_OnChar;
		System::Handler m_OnKeyDown;
		System::Handler m_OnKeyUp;
		System::Handler m_OnWheel;

	protected:
		virtual void RenderTextToTexture();
		virtual void OnResize(System::WindowResizeEvent* event);
		virtual void OnMouseMove(System::MouseMoveEvent* event);
		virtual void OnIdle(System::IdleEvent* event);
		virtual void OnMouseEnter(System::MouseEnterEvent* event);
		virtual void OnMouseLeave(System::MouseLeaveEvent* event);
		virtual void OnMouseLeftButtonDown(System::MouseLeftButtonDownEvent* event);
		virtual void OnMouseLeftButtonUp(System::MouseLeftButtonUpEvent* event);
	public:

		Widget(float x = 0, float y = 0, float width = 1, float height = 1, Widget* parent = 0);
		
		void RemoveChild(Widget* child);
		void AddChild(Widget* child);

		virtual ~Widget();


		void SetWidth(float width);
		void SetHeight(float height);
		float GetWidth() const;
		float GetHeight() const;
		float GetX() const;
		float GetY() const;
		void SetX(float x);
		void SetY(float y);
		bool IsVisible() const;
		bool IsEnabled() const;
		void Show(bool isVisible);
		void Enable(bool isEnabled);
		void SetParent(Widget* parent);
		Widget* GetParent();
		const Widget* GetParent() const;
		void FixPosition(bool isFixed);
		bool IsFixedPosition() const;
		void SetSize(float x, float y, float width, float height);
		void SetColor(ColorType type, float r, float g, float b, float a);
		void SetText(const System::string& text);
		void SetFont(const char* fontName);
		void SetTextSize(int size);
		Widget* GetChild(int index);
		const Widget* GetChild(int index) const;
		unsigned GetChildrenCount() const;

		const System::string& GetText() const;
		void SetFocuse(bool isFocused);

		virtual void Render(IGUIRender* render) const;
		virtual bool EventHandler(System::Event* event);

		bool IsPointIn(const Math::vec2& point_in_viewport) const;

		bool SendChildren(System::Event* event);  

		Widget* GetFocused(float x, float y);

		void Store(System::Buffer& buffer) {}
		void Restore(System::Buffer& buffer) {}
		
		const OpenGL::Texture2D* GetTextTexture() const;
		void SetBackgroundTexture(OpenGL::Texture2D* texture);
		const OpenGL::Texture2D* GetBackgroundTexture() const;

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
		void SetCharHandler(System::Handler onChar);
		void SetKeyDownHandler(System::Handler onKeyDown);
		void SetKeyUpHandler(System::Handler onKeyUp);
		void SetWheelHandler(System::Handler onWheel);


		friend class Manager;

		static const Math::Vector2<float> WindowToViewport(float x, float y);
	};
}

#endif