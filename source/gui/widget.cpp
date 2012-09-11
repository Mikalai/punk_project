#include <algorithm>
#include "widget.h"
#include "manager.h"
#include "../math/math.h"
#include "../utility/font_builder.h"
//#include "../render/render.h"
#include "../system/event_manager.h"
#include "gui_render.h"
#include <algorithm>

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
		, m_parent(parent)
		, m_back_color_0(0.6f, 0.6f, 0.6f, 0.5f)
		, m_back_color_1(1, 1, 1, 0.8f)
		, m_text_color_0(0, 0, 0, 1)
		, m_text_color_1(1, 0, 0, 1)
		, m_back_color(m_back_color_0)
		, m_text_color(m_text_color_0)
		, m_animation(0)
		, m_animation_duration(0.1f)		
		, m_next_widget(0)
		, m_prev_widget(0)
		, m_manager(0)
		, m_vertical_align(VERTICAL_ALIGN_CENTER)
		, m_horizontal_align(HORIZONTAL_ALIGN_CENTER)
	{
		m_text_texture = new OpenGL::Texture2D;;
		m_text_texture->Create(int(GetWidth()*System::Window::Instance()->GetWidth()), int(GetHeight()*System::Window::Instance()->GetHeight()), GL_RED, 0);
		m_background_texture = 0;
		RenderTextToTexture();
		if (m_parent)
			m_parent->AddChild(this);
	}

	Widget::~Widget()
	{
	}

	void Widget::RemoveChild(Widget* child)
	{
		std::vector<std::shared_ptr<Widget>>::iterator it;
		for (it = m_children.begin(); it != m_children.end(); ++it)
		{
			if (it->get() == child)
				break;
		}
		if (it != m_children.end())
			m_children.erase(it);
	}

	void Widget::RemoveAll()
	{
		m_children.clear();
	}

	void Widget::AddChild(Widget* child)
	{
		m_children.push_back(std::shared_ptr<Widget>(child));
		child->SetParent(this);		
	}

	void Widget::OnResize(System::WindowResizeEvent* e)
	{
		m_text_texture->Create(int(GetWidth()*System::Window::Instance()->GetWidth()), int(GetHeight()*System::Window::Instance()->GetHeight()), GL_RED, 0);
		RenderTextToTexture();
		std::for_each(m_children.begin(), m_children.end(), [&e] (std::shared_ptr<Widget>& w) { w->OnResize(e); } );

		m_OnResized(e);
	}

	void Widget::OnMouseMove(System::MouseMoveEvent* e)
	{
		if (IsVisible() && IsEnabled())
		{
			m_OnMouseMove(e);
			bool wasIn = IsPointIn(Widget::WindowToViewport(float(e->x_prev), float(e->y_prev)));
			bool isIn = IsPointIn(Widget::WindowToViewport(float(e->x), float(e->y)));
			if (!wasIn && isIn)
			{
				System::MouseEnterEvent* new_event = System::MouseEnterEvent::Raise();
				new_event->anyData = this;
				System::EventManager::Instance()->FixEvent(new_event);
			}

			if (wasIn && !isIn)
			{
				System::MouseLeaveEvent* new_event = System::MouseLeaveEvent::Raise();
				new_event->anyData = this;
				System::EventManager::Instance()->FixEvent(new_event);
			}

			if (m_leftButtonDown && m_moveable)
			{
				m_x += e->x - e->x_prev;
				m_y += e->y - e->y_prev;
			}
		}

		std::for_each(m_children.begin(), m_children.end(), [&e] (std::shared_ptr<Widget>& w) { w->OnMouseMove(e); } );
	}

	void Widget::OnMouseEnter(System::MouseEnterEvent* e)
	{
		if (IsVisible() && IsEnabled())
		{
			m_isCursorIn = true;
			m_OnMouseEnter(e);
			//std::for_each(m_children.begin(), m_children.end(), [&e] (std::shared_ptr<Widget>& w) { w->OnMouseEnter(e); } );
		}
	}

	void Widget::OnMouseLeave(System::MouseLeaveEvent* e)
	{
		if (IsVisible() && IsEnabled())
		{
			m_isCursorIn = false;
			m_leftButtonDown = false;
			m_rightButtonDown = false;
			m_middleButtonDown = false;
			m_OnMouseLeave(e);
			std::for_each(m_children.begin(), m_children.end(), [&e] (std::shared_ptr<Widget>& w) { w->OnMouseLeave(e); } );
		}
	}

	void Widget::OnMouseLeftButtonUp(System::MouseLeftButtonUpEvent* e)
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
			std::for_each(m_children.begin(), m_children.end(), [&e] (std::shared_ptr<Widget>& w) { w->OnMouseLeftButtonUp(e); } );
		}
	}

	void Widget::OnMouseLeftButtonDown(System::MouseLeftButtonDownEvent* e)
	{
		if (IsVisible() && IsEnabled())
		{
			if (m_isCursorIn)
			{
				m_leftButtonDown = true;
			}
			else
			{
				if (m_isFocused)
					m_isFocused = false;
			}
			std::for_each(m_children.begin(), m_children.end(), [&e] (std::shared_ptr<Widget>& w) { w->OnMouseLeftButtonDown(e); } );
		}
	}

	void Widget::OnMouseWheel(System::MouseWheelEvent* e)
	{
		if (IsVisible() && IsEnabled())
		{
			std::for_each(m_children.begin(), m_children.end(), [&e] (std::shared_ptr<Widget>& w) { w->OnMouseWheel(e); } );
		}
	}

	void Widget::OnKeyChar(System::KeyCharEvent* e)
	{
		if (IsVisible() && IsEnabled())
		{
			std::for_each(m_children.begin(), m_children.end(), [&e] (std::shared_ptr<Widget>& w) { w->OnKeyChar(e); } );
		}
	}

	void Widget::OnKeyDown(System::KeyDownEvent* event)
	{ 
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
	}

	void Widget::OnIdle(System::IdleEvent* e)
	{		
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
					m_animation = std::min(m_animation, m_animation_duration);
					m_back_color = Math::linear_interpolation(m_back_color_0, m_back_color_1, m_animation / m_animation_duration);
					m_text_color = Math::linear_interpolation(m_text_color_0, m_text_color_1, m_animation / m_animation_duration);
				}
			}
			else
			{
				if (m_animation > 0)
				{
					m_animation -= time_in_s;
					m_animation = std::max(m_animation, float(0.0));
					m_back_color = Math::linear_interpolation(m_back_color_0, m_back_color_1, m_animation / m_animation_duration);
					m_text_color = Math::linear_interpolation(m_text_color_0, m_text_color_1, m_animation / m_animation_duration);
				}
			}			
			std::for_each(m_children.begin(), m_children.end(), [&e] (std::shared_ptr<Widget>& w) { w->OnIdle(e); } );
		}
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
		RenderTextToTexture();
		//m_textRender->SetText(m_text.c_str());
	}

	void Widget::SetFont(const char* font)
	{
		m_font = font;		
		RenderTextToTexture();
	}

	void Widget::SetTextSize(int size)
	{
		m_fontSize = size;
		RenderTextToTexture();
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
			throw System::SystemError(L"Bad color type" + LOG_LOCATION_STRING);
		}

		c[0] = r;
		c[1] = g; 
		c[2] = b; 
		c[3] = a;
	}

	float Widget::GetWidth() const
	{
		if (m_parent == 0)
			return m_width;
		return m_width * m_parent->GetWidth();
	}

	float Widget::GetHeight() const
	{
		if (m_parent == 0)
			return m_height;
		return m_height * m_parent->GetHeight();
	}

	float Widget::GetScreenWidth() const
	{
		return GetWidth() * (float)System::Window::Instance()->GetWidth();
	}

	float Widget::GetScreenHeight() const
	{
		return GetHeight() * (float)System::Window::Instance()->GetHeight();
	}

	float Widget::GetX() const
	{
		if (m_parent == 0)
			return m_x;
		return m_parent->GetX() + m_x * m_parent->GetWidth();
	}

	float Widget::GetY() const
	{
		if (m_parent == 0)
			return m_y;
		return m_parent->GetY() + m_y * m_parent->GetHeight();
	}

	float Widget::GetScreenX() const
	{
		return GetX() * (float)System::Window::Instance()->GetWidth();
	}

	float Widget::GetScreenY() const
	{
		return GetY() * (float)System::Window::Instance()->GetHeight();
	}

	const OpenGL::Texture2D* Widget::GetBackgroundTexture() const
	{
		return m_background_texture;
	}

	const OpenGL::Texture2D* Widget::GetTextTexture() const
	{
		return m_text_texture;
	}

	void Widget::SetBackgroundTexture(OpenGL::Texture2D* texture)
	{
		m_background_texture = texture;
	}

	void Widget::Render(IGUIRender* render) const
	{
		if (m_isVisible)
			render->RenderWidget(this);
	}

	Widget* Widget::GetChild(int index)
	{
		return m_children[index].get();
	}

	const Widget* Widget::GetChild(int index) const
	{
		return m_children[index].get();
	}

	void Widget::SetParent(Widget* widget)
	{
		m_parent = widget;
		OnResize(0);
	}

	Widget* Widget::GetParent() 
	{
		return m_parent;
	}

	int Widget::CalculateTextXOffset(const wchar_t* text)
	{
		int start_x;
		if (HORIZONTAL_ALIGHT_LEFT == m_horizontal_align)
			start_x = 0;
		else if (HORIZONTAL_ALIGN_CENTER == m_horizontal_align)
		{
			int length = Utility::FontBuilder::Instance()->CalculateLength(text);
			if (length >= m_text_texture->GetWidth())
				start_x = 0;
			else
				start_x = (m_text_texture->GetWidth() - length) / 2;
		}
		else if (HORIZONTAL_ALIGN_RIGHT == m_horizontal_align)
		{
			int length = Utility::FontBuilder::Instance()->CalculateLength(text);
			if (length >= m_text_texture->GetWidth())
				start_x = 0;
			else
				start_x = m_text_texture->GetWidth() - length;
		}
		return start_x;
	}

	int Widget::CalculateTextYOffset(const wchar_t* text)
	{
		const wchar_t* cur = text;		
		int length = Utility::FontBuilder::Instance()->CalculateLength(cur);
		if (length == 0)
			return 1;		
		int height_M = Utility::FontBuilder::Instance()->GetHeight(L'M');
		int lines = m_text_texture->GetHeight() / height_M;
		int start_y = 0;
		if (VERTICAL_ALIGN_BOTTOM == m_vertical_align)
		{
			start_y = 0;
		}
		else if (VERTICAL_ALIGN_CENTER == m_vertical_align)
		{
			start_y = m_text_texture->GetHeight() / 2 - lines*height_M / 2;
		}
		else if (VERTICAL_ALIGN_TOP == m_vertical_align)
		{
			start_y = m_text_texture->GetHeight() - height_M;
		}
		return start_y;
	}

	void Widget::RenderTextToTexture()
	{
		if (m_text.Length() == 0)
		{
			m_text_texture->Fill(0);
			return;
		}

		int x = CalculateTextXOffset(m_text.Data());
		int y = CalculateTextYOffset(m_text.Data());
		m_text_texture->Fill(0);
		Utility::FontBuilder::Instance()->SetCurrentFace(m_font);
		Utility::FontBuilder::Instance()->SetCharSize(m_fontSize, m_fontSize);
		for (const wchar_t* a = m_text.Data(); *a; a++)
		{ 
			int width;
			int height;
			int x_offset;
			int y_offset;
			int x_advance;
			int y_advance;
			unsigned char* buffer;
			Utility::FontBuilder::Instance()->RenderChar(*a, &width, &height, &x_offset, &y_offset, &x_advance, &y_advance, &buffer);
			if (x_offset < 0 && x == 0)
				x += -x_offset;
			if (x + x_offset + width >= m_text_texture->GetWidth())
			{
				y -= Utility::FontBuilder::Instance()->GetHeight(L'M');
				x = CalculateTextXOffset(a);
				if (y < 0)
					return;
			}							
			m_text_texture->CopyFromCPU(x + x_offset, m_text_texture->GetHeight() - (y + y_offset), width, height, GL_RED, buffer);			
			x += x_advance;				
		}/**/
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
		for (auto it = m_children.begin(); it != m_children.end(); ++it)
		{
			if ((*it)->IsVisible() && (*it)->IsEnabled() && (*it)->IsPointIn(WindowToViewport(x, y)))
				return (*it)->GetFocused(x, y);
		}
		return this;/**/
	}

	void Widget::SetSize(float x, float y, float width, float height)
	{
		m_x = x; m_y = y; m_width = width; m_height = height;
		m_text_texture->Resize(int(GetScreenWidth()), int(GetScreenHeight()));
	}

	unsigned Widget::GetChildrenCount() const
	{
		return m_children.size();
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

	const Math::Vector4<float>& Widget::BackColor() const
	{
		return m_back_color;
	}

	const Math::Vector4<float>& Widget::TextColor() const
	{
		return m_text_color;
	}

	Math::Vector4<float>& Widget::BackColor0()
	{
		return m_back_color_0;
	}

	Math::Vector4<float>& Widget::BackColor1()
	{
		return m_back_color_1;
	}

	Math::Vector4<float>& Widget::TextColor0()
	{
		return m_text_color_0;
	}

	Math::Vector4<float>& Widget::TextColor1()
	{
		return m_text_color_1;
	}

	const Math::Vector4<float>& Widget::BackColor0() const
	{
		return m_back_color_0;
	}

	const Math::Vector4<float>& Widget::BackColor1() const
	{
		return m_back_color_1;
	}

	const Math::Vector4<float>& Widget::TextColor0() const
	{
		return m_text_color_0;
	}

	const Math::Vector4<float>& Widget::TextColor1() const
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
		res[0] = x / (float)System::Window::Instance()->GetWidth();
		res[1] = y / (float)System::Window::Instance()->GetHeight();
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
}