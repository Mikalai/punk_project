#include "Form.h"
#include "Manager.h"

GUIForm::GUIForm(float x, float y, float width, float height) : 
GUIContainer(x, y, width, height) 
{
	m_backColor = Color(0.6f, 0.6f, 0.6f, 1.0f);
}

GUIForm::~GUIForm()
{
	for (std::vector<GUIElement*>::iterator i = m_child.begin(); i != m_child.end(); i++)
	{
		delete *i;
	}
}

void GUIForm::ElementDraw()
{
	GUIManager::g_render->Enter2DMode((int)m_x, (int)m_y, (int)m_width, (int)m_height, 0, 0, (int)m_width, (int)m_height);
	GUIManager::g_render->SetColor(m_backColor.r, m_backColor.g, m_backColor.b, m_backColor.a);
	GUIManager::g_render->RenderRect(0, 0, m_width, m_height);
	for (std::vector<GUIElement*>::iterator i = m_child.begin(); i != m_child.end(); i++)
	{
		(*i)->Draw();
	}
	GUIManager::g_render->Leave2DMode();
}

void GUIForm::Update(float delta)
{
	for (std::vector<GUIElement*>::iterator i = m_child.begin(); i != m_child.end(); i++)
	{
		(*i)->Update(delta);
	}
}

void GUIForm::MouseMove(int x, int y, MouseFlags flags)
{
	if (flags & MOUSE_LEFT)
	{
		if (IsPointIn(m_prevMouseX, m_prevMouseY))
		{
			m_x += x - m_prevMouseX; 
			m_y += y - m_prevMouseY;
		}
	}
	GUIContainer::MouseMove(x, y, flags);
}