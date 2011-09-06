#include "Static.h"
#include "Manager.h"

GUIStatic::GUIStatic(float x, float y, PunkString text) : GUIElement(x, y, 0, 0, text) {}

void GUIStatic::Draw()
{
	GUIManager::g_render->Enter2DMode();
	GUIManager::g_render->SetFont(m_fontName.CString(), m_fontSize);
	GUIManager::g_render->SetColor(m_fontColor.r, m_fontColor.g, m_fontColor.b, m_fontColor.a);
	GUIManager::g_render->RenderText(m_x+m_width/2-m_text.Length()*m_fontSize/4,m_y+m_height/2-m_fontSize/4,m_width,m_height,"%s", m_text.CString());
	GUIManager::g_render->Leave2DMode();
}

void GUIStatic::Update(float delta)
{
}

void GUIStatic::SetSize(float width, float height)
{
	GUIElement::SetSize(width, height);
}

void GUIStatic::SetPosition(float x, float y)
{
	GUIElement::SetPosition(x, y);
}

void GUIStatic::Enable()
{
	GUIElement::Enable();
}

void GUIStatic::Disable()
{
	GUIElement::Disable();
}

void GUIStatic::Show()
{
	GUIElement::Show();
}

void GUIStatic::Hide()
{
	GUIElement::Hide();
}

bool GUIStatic::IsEnabled() const
{
	return GUIElement::IsEnabled();
}

bool GUIStatic::IsVisible() const
{
	return GUIElement::IsVisible();
}

void GUIStatic::SetEnabled(bool isEnabled) 
{
	GUIElement::SetEnabled(isEnabled);
}

void GUIStatic::SetVisible(bool isVisible)
{
	GUIElement::SetVisible(isVisible);
}

void GUIStatic::SetText(const PunkString& text)
{
	GUIElement::SetText(text);
}