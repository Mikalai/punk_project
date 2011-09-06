#include "Element.h"
#include "Manager.h"

GUIElement::GUIElement() : 
	m_x(10),
	m_y(10),
	m_width(10),
	m_height(10), 
	m_text(PUNK_TEXT("Element")),
	m_fontColor(Color(0,0,0,1)),
	m_backColor(Color(1,1,1,1)),
	m_fontSize(16),
	m_fontName("System"),
	m_left(false),
	m_right(false),
	m_middle(false),
	m_background(NULL),
	m_isVisible(true),
	m_isEnable(true), 
	m_isMouseOver(false),
	m_parent(NULL),
	m_prevMouseX(0),
	m_prevMouseY(0),
	m_zDepth(0) {}

GUIElement::GUIElement(float x, float y, float width, float height, PunkString text) :
	m_x(x),
	m_y(y),
	m_width(width),
	m_height(height),
	m_text(text),
	m_fontColor(Color(0,0,0,1)),
	m_backColor(Color(1,1,1,1)),
	m_fontSize(16),
	m_fontName("System"),
	m_left(false),
	m_right(false),
	m_middle(false),
	m_isMouseOver(false),
	m_background(NULL),
	m_isVisible(true),
	m_isEnable(true), 
	m_parent(NULL),
	m_prevMouseX(0),
	m_prevMouseY(0),
	m_zDepth(0) {}

GUIElement::GUIElement(const GUIElement &element)
{
	m_x = element.m_x;
	m_y = element.m_y;
	m_width = element.m_width;
	m_height = element.m_height;
}

void GUIElement::Draw()
{
	if (!m_parent)
		GUIManager::g_render->Enter2DMode();
	ElementDraw();
	if (!m_parent)
		GUIManager::g_render->Leave2DMode();
}

void GUIElement::ElementDraw()
{
}

GUIElement& GUIElement::operator =(const GUIElement &element)
{
	if (&element != this)
	{
		m_x = element.m_x;
		m_y = element.m_y;
		m_width = element.m_width;
		m_height = element.m_height;
	}
	return *this;
}

void GUIElement::GetPosition(float* x, float* y)
{
	*x = m_x; *y = m_y;
}

const PunkString& GUIElement::GetText() const
{
	return m_text;
}

float GUIElement::GetX() const
{
	return m_x;
}

float GUIElement::GetY() const
{
	return m_y;
}

float GUIElement::GetWidth() const
{
	return m_width;
}

float GUIElement::GetHeight() const
{
	return m_height;
}

void GUIElement::SetHeight(float height)
{
	m_height = height;
}

void GUIElement::SetPosition(float x, float y)
{
	m_x = x; m_y = y;
}

void GUIElement::SetText(const PunkString &text)
{
	m_text = text;
}

void GUIElement::SetWidth(float width)
{
	m_width = width;
}

void GUIElement::SetBackColor(float r, float g, float b, float a)
{
	m_backColor.r = r; m_backColor.g = g; m_backColor.b = b; m_backColor.a = a;
}

void GUIElement::SetFontColor(float r, float g, float b, float a)
{
	m_fontColor.r = r; m_fontColor.g = g; m_fontColor.b = b; m_fontColor.a = a;
}

const Color& GUIElement::GetBackColor() const
{
	return m_backColor;
}

const Color& GUIElement::GetFontColor() const
{
	return m_fontColor;
}

void GUIElement::SetFont(const PunkString &fontName, int size)
{
	m_fontSize = size;
	m_fontName = fontName;
}

void GUIElement::SetFontSize(int size)
{
	m_fontSize = size;
}

const PunkString& GUIElement::GetFontName() const
{
	return m_fontName;
}

int GUIElement::GetFontSize() const
{
	return m_fontSize;
}

bool GUIElement::IsPointIn(int x, int y)
{
	if (x < m_x || x > m_x+m_width ||
		y < m_y || y > m_y+m_height)
		return false;
	return true;
}

void GUIElement::MouseMove(int x, int y, MouseFlags flags)
{
	m_prevMouseX = x;
	m_prevMouseY = y;
}

void GUIElement::MouseLeftButtonDoubleClick(int x, int y, MouseFlags flags)
{
}

void GUIElement::MouseLeftButtonDown(int x, int y, MouseFlags flags)
{
	//if (m_isFocused)
		m_left = true;
}

void GUIElement::MouseLeftButtonUp(int x, int y, MouseFlags flags)
{
	if (m_isMouseOver && m_left)
		MouseLeftButtonClick(x, y, flags);
	m_left = false;
}

void GUIElement::MouseMiddleButtonDoubleClick(int x, int y, MouseFlags flags)
{
}

void GUIElement::MouseMiddleButtonDown(int x, int y, MouseFlags flags)
{
	if (m_isFocused)
		m_middle = true;
}

void GUIElement::MouseMiddleButtonUp(int x, int y, MouseFlags flags)
{
	if (m_isFocused && m_middle)
		MouseMiddleButtonClick(x, y, flags);
	m_middle = false;
}

void GUIElement::MouseRightButtonDoubleClick(int x, int y, MouseFlags flags)
{
}

void GUIElement::MouseRightButtonDown(int x, int y, MouseFlags flags)
{
	if (m_isFocused)
		m_right = true;
}

void GUIElement::MouseRightButtonUp(int x, int y, MouseFlags flags)
{
	if (m_isFocused && m_right)		
		MouseRightButtonClick(x, y, flags);
	m_right = false;
}

void GUIElement::MouseWheel(int delta, int x, int y, MouseFlags flags)
{
}

void GUIElement::KeyChar(unsigned int code, KeyFlags flags)
{
}

void GUIElement::KeyDown(unsigned int code, KeyFlags flags)
{
}

void GUIElement::KeyUp(unsigned int code, KeyFlags flags)
{
}

void GUIElement::MouseLeftButtonClick(int x, int y, MouseFlags flags)
{
	onButtonClickMethod(Parameters((float)x, (float)y, flags)); 
}

void GUIElement::MouseMiddleButtonClick(int x, int y, MouseFlags flags)
{
}

void GUIElement::MouseRightButtonClick(int x, int y, MouseFlags flags)
{
}

void GUIElement::OnClick(Handler eventHandler)
{
	onButtonClickMethod = eventHandler;
}

void GUIElement::OnDblClk(Handler eventHandler)
{
	onButtonDblclkMethod = eventHandler;
}

void GUIElement::OnMouseEnter(Handler eventHandler)
{
	onMouseEnterMethod = eventHandler;
}

void GUIElement::OnMouseLeave(Handler eventHandler)
{
	onMouseLeaveMethod = eventHandler;
}

void GUIElement::SetSize(float width, float height)
{
	m_width = width;
	m_height = height;
}

void GUIElement::SetEnabled(bool isEnabled)
{
	m_isEnable = isEnabled;
}

void GUIElement::SetVisible(bool isVisible)
{
	m_isVisible = isVisible;
}

bool GUIElement::IsEnabled() const
{
	return m_isEnable;
}

bool GUIElement::IsVisible() const
{
	return m_isVisible;
}

void GUIElement::Enable()
{
	m_isEnable = true;
}

void GUIElement::Disable()
{
	m_isEnable = false;
}

void GUIElement::Show()
{
	m_isVisible = true;
}

void GUIElement::Hide()
{
	m_isVisible = false;
}

void GUIElement::OnKeyEnter(Handler eventHandler)
{
	onKeyEnterMethod = eventHandler;
}

void GUIElement::Resize(unsigned int width, unsigned int height)
{
}

void GUIElement::SetParent(GUIElement *element)
{
	m_parent = element;
}

GUIElement* GUIElement::GetParent()
{
	return m_parent;
}

void GUIElement::SetZDepth(float depth)
{
	m_zDepth = depth;
}

float GUIElement::GetZDepth() const
{
	return m_zDepth;
}

bool GUIElement::IsMouseOver() const
{
	return m_isMouseOver;
}

void GUIElement::MouseEnter(int x, int y, MouseFlags flags)
{
	m_isMouseOver = true;
}

void GUIElement::MouseLeave(int x, int y, MouseFlags flags)
{
	m_isMouseOver = false;
}

void GUIElement::SetFocused(bool isFocused)
{
	m_isFocused = isFocused;
}

bool GUIElement::IsFocused() const
{
	return m_isFocused;
}
/*
LRESULT CALLBACK ButtonProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubClass, DWORD_PTR dwRefData)
{
	TButton* button = (TButton*)dwRefData;
	switch(msg)
	{
	case WM_USER:
		{
			switch(wParam)
			{
			case MSG_CLICK:
				PrintInfo("TButton->MSG_CLICK");
				CALLHANDLER(button->onButtonClickMethod, wParam, lParam);
				break;
			case MSG_DBLCLK:
				PrintInfo("TButton->MSG_DBLCLK");
				CALLHANDLER(button->onButtonDblclkMethod, wParam, lParam);
				break;
			case MSG_ENTER:
				PrintInfo("TButton->MSG_ENTER");
				CALLHANDLER(button->onButtonEnterMethod, wParam, lParam);
				break;
			case MSG_LEAVE:
				PrintInfo("TButton->MSG_LEAVE");
				CALLHANDLER(button->onButtonLeaveMethod, wParam, lParam);
				break;
			}
			break;
		}
	}

	return DefSubclassProc(hwnd, msg, wParam, lParam);
}
*/