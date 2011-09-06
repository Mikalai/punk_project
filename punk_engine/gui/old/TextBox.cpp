#include "TextBox.h"
#include "Manager.h"

GUITextBox::GUITextBox(float x, float y, float width, float height, PunkString text) :
GUIElement(x,y,width,height, text),
m_limit(0),
m_start(0),
m_cursorPos(0),
m_isReadOnly(false),
m_options(TEXT_CLIP)
{}

void GUITextBox::ElementDraw()
{
	GUIManager::g_render->SetColor(m_backColor.r,m_backColor.g,m_backColor.b,m_backColor.a);
	GUIManager::g_render->RenderRect(m_x, m_y, m_width, m_height);
	GUIManager::g_render->SetColor(m_fontColor.r,m_fontColor.g,m_fontColor.b,m_fontColor.a);
	GUIManager::g_render->SmartRenderText(m_x, m_y + m_height / 2 - m_fontSize / 4, m_width, m_height, (TextOptions)m_options, 0, m_text.CString());
}

void GUITextBox::Update(float delta)
{
	
}
GUITextBox::~GUITextBox()
{}

void GUITextBox::SetText(double number, int numberOfDigits)
{
	GUIElement::SetText(Convert::ToString(number, numberOfDigits));
}

void GUITextBox::SetText(float number)
{
	GUIElement::SetText(Convert::ToString(number));
}

void GUITextBox::SetText(unsigned number, int radix)
{
	GUIElement::SetText(Convert::ToString((int)number, radix));
}

void GUITextBox::SetText(int number, int radix)
{
	GUIElement::SetText(Convert::ToString(number, radix));
}

void GUITextBox::SetLimit(unsigned limit)
{
	m_limit = limit;
}

unsigned GUITextBox::GetLimit() const
{
	return m_limit;
}

void GUITextBox::SetReadOnly(bool isReadOnly)
{
	m_isReadOnly = isReadOnly;
}

int GUITextBox::GetTextAsInteger() const
{
	return Convert::ToInt32(m_text);
}

double GUITextBox::GetTextAsDouble() const
{
	return Convert::ToDouble(m_text);
}

void GUITextBox::SetAutoSize(bool isAutoSize)
{
}

void GUITextBox::KeyChar(unsigned int code, KeyFlags flags)
{
	if (!m_isFocused)
		return;
	switch(code)
	{
	case BUTTON_BACKSPACE:
		return;
	case BUTTON_ENTER:
		return;
	default:
		m_text.Insert(m_cursorPos, code);
		m_cursorPos++;
	}			
}

void GUITextBox::KeyDown(unsigned int code, KeyFlags flags)
{
	if (!m_isFocused)
		return;	
	switch(code)
	{
	case BUTTON_ENTER:
		onKeyEnterMethod(Parameters(code, flags));
		break;
	case BUTTON_BACKSPACE:
		if (m_cursorPos > 0)
		{
			m_text.RemoveAt(m_cursorPos-1);
			m_cursorPos--;
		}
		break;
	case BUTTON_LEFT:
		if (m_cursorPos > 0)
			m_cursorPos--;
		break;
	case BUTTON_RIGHT:
		if (m_cursorPos < m_text.Length())
			m_cursorPos++;
		break;
	}
}


void GUITextBox::Reset()
{
	m_text = "";
	m_cursorPos = 0;
}

void GUITextBox::SetDrawOptions(TextOptions options)
{
	m_options = options;
}