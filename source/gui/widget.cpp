#include "../system/logger.h"
#include <algorithm>
#include "widget.h"
#include "manager.h"
#include "../math/math.h"
#include "../utility/fonts/font_builder.h"
#include "../system/input/keyboard.h"
#include "../system/window/module.h"
#include "../system/event_manager.h"
#include "gui_render.h"
#include "events/module.h"

namespace GUI
{
	Widget::Widget(float x, float y, float width, float height, const System::string& text, Widget* parent)
		: m_x(x)
		, m_y(y)
		, m_width(width)
		, m_height(height)
		, m_isVisible(true)
		, m_isEnabled(true)
		, m_isCursorIn(false)
		, m_leftButtonDown(false)
		, m_rightButtonDown(false)
		, m_middleButtonDown(false)
		, m_moveable(false)
		, m_isFocused(false)
		, m_text(text)
		, m_fontSize(14)
		, m_back_color_0(0.0f, 0.0f, 1.0f, 1.0f)
		, m_back_color_1(1.0f, 1.0f, 0.1f, 0.8f)
		, m_text_color_0(0.0f, 0.0f, 0.0f, 1.0f)
		, m_text_color_1(1.0f, 0.0f, 0.0f, 1.0f)
		, m_back_color(m_back_color_0)
		, m_text_color(m_text_color_0)
		, m_animation(0)
		, m_animation_duration(0.1f)
		, m_next_widget(0)
		, m_prev_widget(0)
		, m_manager(0)
		, m_vertical_align(VERTICAL_ALIGN_CENTER)
		, m_horizontal_align(HORIZONTAL_ALIGN_CENTER)
		, m_parent(parent)
		, m_background_texture(nullptr)
		, m_any_data(nullptr)
	{
//        m_text_texture = new Gpu::OpenGL::TextSurface(nullptr);
//		m_text_texture->SetSize(int(GetWidth()*Manager::Instance()->GetWindow()->GetWidth()), int(GetHeight()*Manager::Instance()->GetWindow()->GetHeight()));
//		m_text_texture->SetVerticalAlignment(Gpu::OpenGL::TextSurface::VERTICAL_CENTER);
//		m_text_texture->SetHorizontalAlignment(Gpu::OpenGL::TextSurface::HORIZONTAL_CENTER);
//		m_text_texture->SetText(m_text);
		SetManager(GUI::Manager::Instance());
	}

	Widget::~Widget()
	{
		safe_delete(m_text_texture);
	}

	bool Widget::OnResize(System::WindowResizeEvent* e)
	{
		bool result = false;
		m_text_texture->SetSize(int(GetWidth()*Manager::Instance()->GetWindow()->GetWidth()), int(GetHeight()*Manager::Instance()->GetWindow()->GetHeight()));
		m_text_texture->SetText(m_text);
		for (Object* o : *this)
		{
			Widget* child = As<Widget*>(o);
			if (child)
				child->OnResize(e);
		}
		m_OnResized(e);
		return result;
	}

	bool Widget::OnMouseMove(System::MouseMoveEvent* e)
	{
		bool result = false;
		bool child_processed = false;
		for (Object* o : *this)
		{
			Widget* w = As<Widget*>(o);
			if (w)
				if (w->OnMouseMove(e))
					child_processed = true;
		}

		if (!child_processed && IsVisible() && IsEnabled())
		{
			bool wasIn = IsPointIn(Widget::WindowToViewport(float(e->x_prev), float(e->y_prev)));
			bool isIn = IsPointIn(Widget::WindowToViewport(float(e->x), float(e->y)));
			if (!wasIn && isIn)
			{
				MouseEnterEvent* new_event = new MouseEnterEvent;
				new_event->anyData = this;
				Manager::Instance()->GetAdapter()->OnMouseEnterEvent(new_event);
				result = true;
			}

			if (wasIn && !isIn)
			{
				MouseLeaveEvent* new_event = new MouseLeaveEvent;
				new_event->anyData = this;
				Manager::Instance()->GetAdapter()->OnMouseLeaveEvent(new_event);
				result = true;
			}

			if (!child_processed && m_leftButtonDown && m_moveable)
			{
				m_x += (e->x - e->x_prev) / (float)Manager::Instance()->GetWindow()->GetWidth();
				m_y += (e->y - e->y_prev) / (float)Manager::Instance()->GetWindow()->GetHeight();
				result = true;
			}

			if (isIn)
			{
				m_OnMouseMove(e);
				result = true;
			}
		}
		return result;
	}

	bool Widget::OnMouseEnter(MouseEnterEvent* e)
	{
		bool result = false;
		if (IsVisible() && IsEnabled())
		{
			m_isCursorIn = true;
			m_OnMouseEnter(e);
			//std::for_each(m_children.begin(), m_children.end(), [&e] (std::shared_ptr<Widget>& w) { w->OnMouseEnter(e); } );
		}
		return result;
	}

	bool Widget::OnMouseLeave(MouseLeaveEvent* e)
	{
		if (IsVisible() && IsEnabled())
		{
			m_isCursorIn = false;
			m_leftButtonDown = false;
			m_rightButtonDown = false;
			m_middleButtonDown = false;
			m_OnMouseLeave(e);
			for (Object* o : *this)
			{
				Widget* w = As<Widget*>(o);
				if (w)
					w->OnMouseLeave(e);
			}
		}
		return false;
	}

	bool Widget::OnMouseLeftButtonUp(System::MouseLeftButtonUpEvent* e)
	{
		if (IsVisible() && IsEnabled())
		{
			if (m_isCursorIn)
			{
				if (m_leftButtonDown)
				{
					m_leftButtonDown = false;
					m_OnLeftClick(e);
				}
			}
			for (Object* o : *this)
			{
				Widget* w = As<Widget*>(o);
				if (w)
					w->OnMouseLeftButtonUp(e);
			}
		}
		return false;
	}

	bool Widget::OnMouseLeftButtonDown(System::MouseLeftButtonDownEvent* e)
	{
		if (!IsVisible() || !IsEnabled())
			return false;

		bool result = false;
		bool child_processed = false;

		for (Object* o : *this)
		{
			Widget* w = As<Widget*>(o);
			if (w)
				child_processed = w->OnMouseLeftButtonDown(e);
		}

		if (!child_processed)
		{
			if (m_isCursorIn)
			{
				m_leftButtonDown = true;
				result = true;
			}
			else
			{
				if (m_isFocused)
					m_isFocused = false;
			}
		}
		return result;
	}

	bool Widget::OnMouseWheel(System::MouseWheelEvent* e)
	{
		bool result = false;
		if (IsVisible() && IsEnabled())
		{
			for (Object* o : *this)
			{
				Widget* w = As<Widget*>(o);
				if (w)
					w->OnMouseWheel(e);
			}
		}
		return result;
	}

	bool Widget::OnKeyChar(System::KeyCharEvent* e)
	{
		bool result = false;
		if (IsVisible() && IsEnabled())
		{
			for (Object* o : *this)
			{
				Widget* w = As<Widget*>(o);
				if (w)
					w->OnKeyChar(e);
			}
		}
		return result;
	}

	bool Widget::OnKeyDown(System::KeyDownEvent* event)
	{
		bool result = false;
		if (m_isFocused)
			m_OnKeyDown(event);

		switch(event->key)
		{
		case System::PUNK_KEY_ENTER:
			if (m_isFocused)
				OnMouseLeftButtonDown(0);
			break;
		case System::PUNK_KEY_TAB:
			{
				if (!System::Keyboard::Instance()->GetKeyState(System::PUNK_KEY_SHIFT))
				{
					if (m_next_widget)
					{
						GetManager()->SetFocusedWidget(m_next_widget);
					}
				}
				else
				{
					if (m_prev_widget)
					{
						GetManager()->SetFocusedWidget(m_prev_widget);
					}
				}
			}
			break;
		}
		return result;
	}

	bool Widget::OnIdle(System::IdleEvent* e)
	{
		bool result = false;
		if (m_isFocused)
			m_OnIdle(e);

		if (IsVisible() && IsEnabled())
		{
			float time_in_s = float(e->elapsed_time_s);
			if (m_isCursorIn)
			{
				if (m_animation < m_animation_duration)
				{
					m_animation += time_in_s;
					m_animation = Math::Min(m_animation, m_animation_duration);
					m_back_color = Math::linear_interpolation(m_back_color_0, m_back_color_1, m_animation / m_animation_duration);
					m_text_color = Math::linear_interpolation(m_text_color_0, m_text_color_1, m_animation / m_animation_duration);
				}
			}
			else
			{
				if (m_animation > 0)
				{
					m_animation -= time_in_s;
					m_animation = Math::Max(m_animation, float(0.0));
					m_back_color = Math::linear_interpolation(m_back_color_0, m_back_color_1, m_animation / m_animation_duration);
					m_text_color = Math::linear_interpolation(m_text_color_0, m_text_color_1, m_animation / m_animation_duration);
				}
			}
			for (Object* o : *this)
			{
				Widget* w = As<Widget*>(o);
				if (w)
					w->OnIdle(e);
			}
		}
		return result;
	}

	void Widget::FixPosition(bool isFixed)
	{
		m_moveable = !isFixed;
	}

	bool Widget::IsFixedPosition() const
	{
		return !m_moveable;
	}

	void Widget::SetX(float x)
	{
		m_x = x;
	}

	void Widget::SetY(float y)
	{
		m_y = y;
	}

	void Widget::SetText(const System::string& text)
	{
		m_text = text;
		m_text_texture->SetText(m_text);
		//m_textRender->SetText(m_text.c_str());
	}

	void Widget::SetFont(const System::string& font)
	{
		m_font = font;
		m_text_texture->SetFont(font);
		m_text_texture->SetText(m_text);
	}

	void Widget::SetTextSize(int size)
	{
		m_fontSize = size;
		m_text_texture->SetTextSize(size);
		m_text_texture->SetText(m_text);
		//m_textRender->SetTextSize(size);
	}

	void Widget::SetColor(Widget::ColorType type, float r, float g, float b, float a)
	{
		float* c;
		switch(type)
		{
		case ACTIVE_COLOR:
			c = m_back_color_0;
			break;
		case INACTIVE_COLOR:
			c = m_back_color_1;
			break;
		case TEXT_ACTIVE_COLOR:
			c = m_text_color_0;
			break;
		case TEXT_INACTIVE_COLOR:
			c = m_text_color_1;
			break;
		default:
			out_error() << L"Bad color type" << std::endl;
		}

		c[0] = r;
		c[1] = g;
		c[2] = b;
		c[3] = a;
	}

	float Widget::GetWidth() const
	{
		if (GetParent() == nullptr)
			return m_width;
		return m_width * GetParent()->GetWidth();
	}

	float Widget::GetHeight() const
	{
		if (GetParent() == nullptr)
			return m_height;
		return m_height * GetParent()->GetHeight();
	}

	float Widget::GetScreenWidth() const
	{
		return GetWidth() * (float)Manager::Instance()->GetWindow()->GetWidth();
	}

	float Widget::GetScreenHeight() const
	{
		return GetHeight() * (float)Manager::Instance()->GetWindow()->GetHeight();
	}

	float Widget::GetX() const
	{
		if (GetParent() == nullptr)
			return m_x;
		return GetParent()->GetX() + m_x * GetParent()->GetWidth();
	}

	float Widget::GetY() const
	{
		if (GetParent() == nullptr)
			return m_y;
		return GetParent()->GetY() + m_y * GetParent()->GetHeight();
	}

	float Widget::GetScreenX() const
	{
		return GetX() * (float)Manager::Instance()->GetWindow()->GetWidth();
	}

	float Widget::GetScreenY() const
	{
		return GetY() * (float)Manager::Instance()->GetWindow()->GetHeight();
	}

	const Gpu::Texture2D* Widget::GetBackgroundTexture() const
	{
		return m_background_texture;
	}

	const Gpu::Texture2D* Widget::GetTextTexture() const
	{
		return m_text_texture->GetTexture();
	}

	void Widget::SetBackgroundTexture(Gpu::Texture2D* texture)
	{
		m_background_texture = texture;
	}

	void Widget::Render(IGUIRender* render) const
	{
		if (m_isVisible)
			render->RenderWidget(this);
	}

	const System::string& Widget::GetText() const
	{
		return m_text;
	}


	void Widget::SetFocuse(bool value)
	{
		m_isFocused = value;
	}

	Widget* Widget::GetFocused(float x, float y)
	{
		for (Object* o : *this)
		{
			Widget* child = As<Widget*>(o);
			if (child)
				if (child->IsVisible() && child->IsEnabled() && child->IsPointIn(WindowToViewport(x, y)))
					return child->GetFocused(x, y);
		}
		return this;/**/
	}

	void Widget::SetSize(float x, float y, float width, float height)
	{
		m_x = x; m_y = y; m_width = width; m_height = height;
		m_text_texture->SetSize(int(GetScreenWidth()), int(GetScreenHeight()));
		m_text_texture->SetText(m_text);
	}

	void Widget::SetAnyData(void* data)
	{
		m_any_data = data;
	}

	void* Widget::GetAnyData()
	{
		return m_any_data;
	}

	bool Widget::IsPointIn(const Math::vec2& p) const
	{
		float x = GetX();
		float y = GetY();
		float w = GetWidth();
		float h = GetHeight();
		if (p.X() < x || p.X() > x + w)
			return false;
		if (p.Y() < y || p.Y() > y + h)
			return false;
		return true;
	}

	bool Widget::IsVisible() const
	{
		return m_isVisible;
	}

	bool Widget::IsEnabled() const
	{
		return m_isEnabled;
	}

	void Widget::Show(bool isVisible)
	{
		m_isVisible = isVisible;
	}

	void Widget::Enable(bool isEnabled)
	{
		m_isEnabled = isEnabled;
	}

	const Math::vec4& Widget::BackColor() const
	{
		return m_back_color;
	}

	const Math::vec4& Widget::TextColor() const
	{
		return m_text_color;
	}

	Math::vec4& Widget::BackColor0()
	{
		return m_back_color_0;
	}

	Math::vec4& Widget::BackColor1()
	{
		return m_back_color_1;
	}

	Math::vec4& Widget::TextColor0()
	{
		return m_text_color_0;
	}

	Math::vec4& Widget::TextColor1()
	{
		return m_text_color_1;
	}

	const Math::vec4& Widget::BackColor0() const
	{
		return m_back_color_0;
	}

	const Math::vec4& Widget::BackColor1() const
	{
		return m_back_color_1;
	}

	const Math::vec4& Widget::TextColor0() const
	{
		return m_text_color_0;
	}

	const Math::vec4& Widget::TextColor1() const
	{
		return m_text_color_1;
	}

	void Widget::SetMouseLeftClickHandler(System::Handler onLeftClick)
	{
		m_OnLeftClick = onLeftClick;
	}

	void Widget::SetMouseRightClickHandler(System::Handler onRightClick)
	{
		m_OnRightClick = onRightClick;
	}

	void Widget::SetMouseMoveHandler(System::Handler onMouseMove)
	{
		m_OnMouseMove = onMouseMove;
	}

	void Widget::SetMouseMiddleClickHandler(System::Handler onMiddleClick)
	{
		m_OnMiddleClick = onMiddleClick;
	}

	void Widget::SetMouseEnterHandler(System::Handler onMouseEnter)
	{
		m_OnMouseEnter = onMouseEnter;
	}

	void Widget::SetMouseLeaveHandler(System::Handler onMouseLeave)
	{
		m_OnMouseLeave = onMouseLeave;
	}

	void Widget::SetCharHandler(System::Handler onChar)
	{
		m_OnChar = onChar;
	}

	void Widget::SetKeyDownHandler(System::Handler onKeyDown)
	{
		m_OnKeyDown = onKeyDown;
	}

	void Widget::SetKeyUpHandler(System::Handler onKeyUp)
	{
		m_OnKeyUp = onKeyUp;
	}

	void Widget::SetIdleHandler(System::Handler onIdle)
	{
		m_OnIdle = onIdle;
	}

	void Widget::SetWheelHandler(System::Handler onWheel)
	{
		m_OnWheel = onWheel;
	}

	void Widget::SetResizedHandler(System::Handler onResized)
	{
		m_OnResized = onResized;
	}

	const Math::Vector2<float> Widget::WindowToViewport(float x, float y)
	{
		Math::Vector2<float> res;
		res[0] = x / (float)Manager::Instance()->GetWindow()->GetWidth();
		res[1] = y / (float)Manager::Instance()->GetWindow()->GetHeight();
		return res;
	}

	bool Widget::IsCursorIn() const
	{
		return m_isCursorIn;
	}

	void Widget::SetNextWidget(Widget* w)
	{
		if (w)
		{
			m_next_widget = w;
			w->SetPrevWidget(this);
		}
	}

	void Widget::SetPrevWidget(Widget* widget)
	{
		m_prev_widget = widget;
	}

	const Manager* Widget::GetManager() const
	{
		if (m_manager)
			return m_manager;
		if (m_parent)
			return m_parent->GetManager();
		return 0;
	}

	Manager* Widget::GetManager()
	{
		if (m_manager)
			return m_manager;
		if (m_parent)
			return m_parent->GetManager();
		return 0;
	}

	void Widget::SetManager(Manager* manager)
	{
		m_manager = manager;
	}

	bool Widget::OnAdd(System::Object* object)
	{
		Widget* w = Cast<Widget*>(object);
		w->SetParent(this);
		return true;
	}

	/*bool OnRemove(Object* object)
	{
	System::Proxy<Widget> w = object;
	if (w.IsValid())
	w->SetParent(nullptr);
	return true;
	}*/
}
