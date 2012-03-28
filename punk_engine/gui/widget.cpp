#include "widget.h"
#include "../utility/font_builder.h"
//#include "../render/render.h"
#include "../system/event_manager.h"

#include <algorithm>

namespace GUI
{
	Widget::Widget(float x, float y, float width, float height) : m_x(x),
		m_y(y), 
		m_width(width), 
		m_height(height), 
		m_isVisible(true), 
		m_isEnabled(true),
		m_isCursorIn(false),
		m_leftButtonDown(false),
		m_rightButtonDown(false),
		m_middleButtonDown(false),
		m_moveable(false),
		m_text("Widget"),
		m_fontSize(12)
	{
		m_inactiveColor[0] = 0.0f;
		m_inactiveColor[1] = 0.3f;
		m_inactiveColor[2] = 0.8f;
		m_inactiveColor[3] = 0.8f;

		m_activeColor[0] = 0.0f;
		m_activeColor[1] = 0.6f;
		m_activeColor[2] = 1.0f;
		m_activeColor[3] = 1.0f;

		m_textActiveColor[0] = m_textActiveColor[1] = m_textActiveColor[2] = m_textActiveColor[3] = 1.0f;
		m_textInactiveColor[0] = m_textInactiveColor[1] = m_textInactiveColor[2] = m_textInactiveColor[3] = 0.95f;

//		m_textTexture.Create(m_width, m_height, ImageLoader::IMAGE_FORMAT_RED, 1, 0);
	}

	Widget::~Widget()
	{
	}

/*	void Widget::RemoveChild(Widget* child)
	{
		std::vector<Widget*>::iterator it = std::find(m_children.begin(), m_children.end(), child);
		if (it != m_children.end())
			m_children.erase(it);
	}
	

	void Widget::AddChild(Widget* child)
	{
		m_children.push_back(child);
	}

	Widget* Widget::GetParent()
	{
		return m_parent;
	}

	const Widget* Widget::GetParent() const
	{
		return m_parent;
	}
	*/
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
//		RenderTextToTexture();
		//m_textRender->SetText(m_text.c_str());
	}

	void Widget::SetFont(const char* font)
	{
		m_font = font;		
	//	RenderTextToTexture();
	}

	void Widget::SetTextSize(int size)
	{
		m_fontSize = size;
		//RenderTextToTexture();
		//m_textRender->SetTextSize(size);
	}

	void Widget::SetColor(Widget::ColorType type, float r, float g, float b, float a)
	{
		float* c;
		switch(type)
		{
		case ACTIVE_COLOR:
			c = m_activeColor;
			break;
		case INACTIVE_COLOR:
			c = m_inactiveColor;
			break;
		case TEXT_ACTIVE_COLOR:
			c = m_textActiveColor;
			break;
		case TEXT_INACTIVE_COLOR:
			c = m_textInactiveColor;
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
		return m_width;
	}

	float Widget::GetHeight() const
	{
		return m_height;
	}

	float Widget::GetX() const
	{
//		if (m_parent == 0)
//			return m_x;
		return m_x;// + m_parent->GetX();
	}

	float Widget::GetY() const
	{
//		if (m_parent == 0)
	//		return m_y;
		return m_y;// + m_parent->GetY();
	}

	System::Descriptor Widget::GetBackGround() const
	{
		return m_background_texture;
	}

	System::Descriptor Widget::GetTextTexture() const
	{
		return m_text_texture;
	}

	void Widget::SetBackGroundTexture(System::Descriptor desc)
	{
		m_background_texture = desc;
	}

	void Widget::SetTextTexture(System::Descriptor desc)
	{
		m_text_texture = desc;
	}

/*	void Widget::RenderTextToTexture()
	{
	/*	int x = 0;
		int y = m_text_texture.GetHeight() - m_fontSize;
		m_textTexture.Fill(0);
		Utility::FontBuilder::SetCurrentFace(m_font);
		Render::FontBuilder::SetCharSize(m_fontSize, m_fontSize);
		for (const wchar_t* a = m_text.Data(); *a; a++)
		{ 
			int width;
			int height;
			int x_offset;
			int y_offset;
			int x_advance;
			int y_advance;
			unsigned char* buffer;
			Render::FontBuilder::RenderChar(*a, &width, &height, &x_offset, &y_offset, &x_advance, &y_advance, &buffer);
			if (x + x_offset + width >= m_textTexture.GetWidth())
			{
				y -= m_fontSize;
				x = 0;
				if (y < 0)
					return;
			}				
			m_textTexture.CopyFromCPU(x + x_offset, m_textTexture.GetHeight() - (y + y_offset), width, height, ImageLoader::IMAGE_FORMAT_RED, buffer);
			x += x_advance;				
		}
	}
	*/
	const System::string& Widget::GetText() const
	{
		return m_text;
	}


	void Widget::SetFocuse(bool value)
	{
		m_isFocused = value;
	}

	bool Widget::EventHandler(System::Event* event)
	{
		if (!m_isEnabled)
			return false;

		//if (SendChildren(event))
		//return true;

		switch(event->eventCode)
		{
		case System::EVENT_SET_FOCUSED:
			m_isFocused = true;
			break;
		case System::EVENT_SET_UNFOCUSED:
			m_isFocused = false;
			break;
		case System::EVENT_MOUSE_ENTER:
			{
				m_isCursorIn = true;
				m_OnMouseEnter(event);
				//SendChildren(event);
			}
			break;
		case System::EVENT_MOUSE_LEAVE:
			{
				m_isCursorIn = false;
				m_leftButtonDown = false;
				m_rightButtonDown = false;
				m_middleButtonDown = false;
				SendChildren(event);
				m_OnMouseLeave(event);
			}
			break;
		case System::EVENT_IDLE:
			if (m_isCursorIn)
			{
				m_color[0] += (m_activeColor[0] - m_color[0]) / 2.0f;
				m_color[1] += (m_activeColor[1] - m_color[1]) / 2.0f;
				m_color[2] += (m_activeColor[2] - m_color[2]) / 2.0f;
				m_color[3] += (m_activeColor[3] - m_color[3]) / 2.0f;	

				m_textColor[0] += (m_textActiveColor[0] - m_textColor[0]) / 2.0f;
				m_textColor[1] += (m_textActiveColor[1] - m_textColor[1]) / 2.0f;
				m_textColor[2] += (m_textActiveColor[2] - m_textColor[2]) / 2.0f;
				m_textColor[3] += (m_textActiveColor[3] - m_textColor[3]) / 2.0f;

			}
			else
			{
				m_color[0] += (m_inactiveColor[0] - m_color[0]) / 10.0f;
				m_color[1] += (m_inactiveColor[1] - m_color[1]) / 10.0f;
				m_color[2] += (m_inactiveColor[2] - m_color[2]) / 10.0f;
				m_color[3] += (m_inactiveColor[3] - m_color[3]) / 10.0f;	

				m_textColor[0] += (m_textInactiveColor[0] - m_textColor[0]) / 10.0f;
				m_textColor[1] += (m_textInactiveColor[1] - m_textColor[1]) / 10.0f;
				m_textColor[2] += (m_textInactiveColor[2] - m_textColor[2]) / 10.0f;
				m_textColor[3] += (m_textInactiveColor[3] - m_textColor[3]) / 10.0f;
			}
			SendChildren(event);
			break;
		case System::EVENT_MOUSE_LBUTTON_DOWN:
			{
				if (m_isCursorIn)
				{
					m_leftButtonDown = true;
				}
				SendChildren(event);
			}
			break;
		case System::EVENT_MOUSE_LBUTTON_UP:
			{
				if (m_isCursorIn)
				{
					if (m_leftButtonDown)
					{
						m_leftButtonDown = false;
						m_OnLeftClick(event);
					}
				}
				SendChildren(event);
			}
			break;
		case System::EVENT_MOUSE_RBUTTON_DOWN:
			{
				if (m_isCursorIn)
				{
					m_rightButtonDown = true;
				}
				SendChildren(event);
			}
			break;
		case System::EVENT_MOUSE_RBUTTON_UP:
			{
				if (m_isCursorIn)
				{
					if (m_rightButtonDown)
					{
						m_rightButtonDown = false;
						m_OnRightClick(event);
					}
				}
				SendChildren(event);
			}
			break;
		case System::EVENT_MOUSE_MBUTTON_DOWN:
			{
				if (m_isCursorIn)
				{
					m_middleButtonDown = true;
				}
				SendChildren(event);
			}
			break;
		case System::EVENT_MOUSE_MBUTTON_UP:
			{
				if (m_isCursorIn)
				{
					if (m_middleButtonDown)
					{
						m_middleButtonDown = false;
						m_OnMiddleClick(event);
					}
				}
				SendChildren(event);
			}
			break;
		case System::EVENT_MOUSE_MOVE:
			{
/*				System::MouseMoveEvent* e = static_cast<System::MouseMoveEvent*>(event);
				for (std::vector<Widget*>::iterator it = m_children.begin(); it != m_children.end(); it++)
				{
					if (!(*it)->IsVisible() || !(*it)->IsEnabled())
						continue;

					bool wasIn = (*it)->IsPointIn(e->x_prev, e->y_prev);
					bool isIn = (*it)->IsPointIn(e->x, e->y);

					if (!wasIn && isIn)
					{
						System::MouseEnterEvent* new_event = System::MouseEnterEvent::Raise();
						new_event->anyData = *it;
						CommonStaff::g_eventManager.FixEvent(new_event);
					}

					if (wasIn && !isIn)
					{
						System::MouseLeaveEvent* new_event = System::MouseLeaveEvent::Raise();
						new_event->anyData = *it;
						CommonStaff::g_eventManager.FixEvent(new_event);
					}

					if (isIn)
					{
						(*it)->EventHandler(event);
					}
				}
				if (m_leftButtonDown && m_moveable)
				{
					m_x += e->x - e->x_prev;
					m_y += e->y - e->y_prev;
				}
				//SendChildren(event);*/
			}
			break;
		}	
		return false;
	}

	Widget* Widget::GetFocused(float x, float y)
	{		
/*		for (std::vector<Widget*>::iterator it = m_children.begin(); it != m_children.end(); ++it)
		{
			if ((*it)->IsPointIn(x, y))
				return (*it)->GetFocused(x, y);
		}*/
		return this;/**/
	}

	void Widget::SetSize(float x, float y, float width, float height)
	{
		m_x = x; m_y = y; m_width = width; m_height = height;
	//	m_textTexture.Resize(m_width, m_height);
	}

	bool Widget::SendChildren(System::Event* event)
	{
/*		for (std::vector<Widget*>::iterator it = m_children.begin(); it != m_children.end(); it++)
		{
			(*it)->EventHandler(event);
		}*/
		return false;
	}

	bool Widget::IsPointIn(float px, float py)
	{
		if (px < GetX() || px > GetX() + m_width)
			return false;
		if (py < GetY() || py > GetY() + m_height)
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

	void Widget::OnLeftClick(System::Handler onLeftClick)
	{		
		m_OnLeftClick = onLeftClick;
	}

	void Widget::OnRightClick(System::Handler onRightClick)
	{
		m_OnRightClick = onRightClick;
	}

	void Widget::OnMiddleClick(System::Handler onMiddleClick)
	{
		m_OnMiddleClick = onMiddleClick;
	}

	void Widget::OnMouseEnter(System::Handler onMouseEnter)
	{
		m_OnMouseEnter = onMouseEnter;
	}

	void Widget::OnMouseLeave(System::Handler onMouseLeave)
	{
		m_OnMouseLeave = onMouseLeave;
	}

	void Widget::OnChar(System::Handler onChar)
	{
		m_OnChar = onChar;
	}

	void Widget::OnKeyDown(System::Handler onKeyDown)
	{
		m_OnKeyDown = onKeyDown;
	}

	void Widget::OnKeyUp(System::Handler onKeyUp)
	{
		m_OnKeyUp = onKeyUp;
	}

	void Widget::OnWheel(System::Handler onWheel)
	{
		m_OnWheel = onWheel;
	}
}