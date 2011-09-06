#include "Container.h"
#include <algorithm>

GUIContainer::GUIContainer(float x, float y, float width, float height) :
GUIElement(x,y,width,height,""),
m_focusedElement(NULL)
{}

void GUIContainer::AddControl(GUIElement *element)
{
	element->SetParent(this);
	m_child.push_back(element);
}

GUIElement* GUIContainer::GetControl(unsigned int index)
{
	return m_child[index];
}

void GUIContainer::Remove(GUIElement *element)
{
	m_child.erase(std::find(m_child.begin(), m_child.end(), element));
}

unsigned GUIContainer::GetCount() const
{
	return m_child.size();
}

void GUIContainer::MouseLeftButtonDoubleClick(int x, int y, MouseFlags flags)
{
	for (std::vector<GUIElement*>::iterator i = m_child.begin(); i != m_child.end(); i++)
	{
		if ((*i)->IsEnabled())
			(*i)->MouseLeftButtonDoubleClick(x-(int)m_x, y-(int)m_y, flags);
	}
}

void GUIContainer::MouseLeftButtonDown(int x, int y, MouseFlags flags)
{
	for (std::vector<GUIElement*>::iterator i = m_child.begin(); i != m_child.end(); i++)
	{
		if ((*i)->IsMouseOver())
		{
			(*i)->MouseLeftButtonDown(x, y, flags);
			if (m_focusedElement != NULL && *i != m_focusedElement)
			{				
				m_focusedElement->SetFocused(false);
				m_focusedElement->SetZDepth(0.0f);
				m_focusedElement = *i;
				m_focusedElement->SetZDepth(1.0f);
				m_focusedElement->SetFocused(true);
			}
			else
			{
				m_focusedElement = *i;
			}
			break;
		}
	}
	std::sort(m_child.begin(), m_child.end(), GUIElement::Compare());
}

void GUIContainer::MouseLeftButtonUp(int x, int y, MouseFlags flags)
{
	for (std::vector<GUIElement*>::iterator i = m_child.begin(); i != m_child.end(); i++)
	{
		if ((*i)->IsEnabled())
			(*i)->MouseLeftButtonUp(x-(int)m_x, y-(int)m_y, flags);
	}
}

void GUIContainer::MouseMiddleButtonDoubleClick(int x, int y, MouseFlags flags)
{
	for (std::vector<GUIElement*>::iterator i = m_child.begin(); i != m_child.end(); i++)
	{
		if ((*i)->IsEnabled())
			(*i)->MouseMiddleButtonDoubleClick(x-(int)m_x, y-(int)m_y, flags);
	}
}

void GUIContainer::MouseMiddleButtonDown(int x, int y, MouseFlags flags)
{
	for (std::vector<GUIElement*>::iterator i = m_child.begin(); i != m_child.end(); i++)
	{
		if ((*i)->IsEnabled())
			(*i)->MouseMiddleButtonDown(x-(int)m_x, y-(int)m_y, flags);
	}
}

void GUIContainer::MouseMiddleButtonUp(int x, int y, MouseFlags flags)
{
	for (std::vector<GUIElement*>::iterator i = m_child.begin(); i != m_child.end(); i++)
	{
		if ((*i)->IsEnabled())
			(*i)->MouseMiddleButtonUp(x-(int)m_x, y-(int)m_y, flags);
	}
}

void GUIContainer::MouseMove(int x, int y, MouseFlags flags)
{ 	
	for (std::vector<GUIElement*>::iterator i = m_child.begin(); i != m_child.end(); i++)
	{
		if ((*i)->IsEnabled())
		{
			if (!(*i)->IsMouseOver() && (*i)->IsPointIn(x-(int)m_x, y-(int)m_y))
				(*i)->MouseEnter(x-(int)m_x, y-(int)m_y, flags);
			if ((*i)->IsMouseOver() && !(*i)->IsPointIn(x-(int)m_x,y-(int)m_y))
				(*i)->MouseLeave(x-(int)m_x, y-(int)m_y, flags);		
			if ((*i)->IsPointIn(x-(int)m_x,y-(int)m_y))	
			{
				(*i)->MouseMove(x-(int)m_x, y-(int)m_y, flags);
				break;
			}
		}
	}
	GUIElement::MouseMove(x, y, flags);
}

void GUIContainer::MouseRightButtonDoubleClick(int x, int y, MouseFlags flags)
{
	for (std::vector<GUIElement*>::iterator i = m_child.begin(); i != m_child.end(); i++)
	{
		if ((*i)->IsEnabled())
			(*i)->MouseRightButtonDoubleClick(x-(int)m_x, y-(int)m_y, flags);
	}
}

void GUIContainer::MouseRightButtonDown(int x, int y, MouseFlags flags)
{
	for (std::vector<GUIElement*>::iterator i = m_child.begin(); i != m_child.end(); i++)
	{
		if ((*i)->IsEnabled())
			(*i)->MouseRightButtonDown(x-(int)m_x, y-(int)m_y, flags);
	}
}

void GUIContainer::MouseRightButtonUp(int x, int y, MouseFlags flags)
{
	for (std::vector<GUIElement*>::iterator i = m_child.begin(); i != m_child.end(); i++)
	{
		if ((*i)->IsEnabled())
			(*i)->MouseRightButtonUp(x-(int)m_x, y-(int)m_y, flags);
	}
}

void GUIContainer::MouseWheel(int delta, int x, int y, MouseFlags flags)
{
	for (std::vector<GUIElement*>::iterator i = m_child.begin(); i != m_child.end(); i++)
	{
		if ((*i)->IsEnabled())
			(*i)->MouseWheel(delta, x-(int)m_x, y-(int)m_y, flags);
	}
}

void GUIContainer::KeyChar(unsigned int code, KeyFlags flags)
{
	if (m_focusedElement)
		m_focusedElement->KeyChar(code, flags);
}
void GUIContainer::KeyDown(unsigned int code, KeyFlags flags)
{
	if (m_focusedElement)
		m_focusedElement->KeyDown(code, flags);
}

void GUIContainer::KeyUp(unsigned int code, KeyFlags flags)
{
	if (m_focusedElement)
		m_focusedElement->KeyUp(code, flags);
}

void GUIContainer::Resize(unsigned width, unsigned height)
{
	for (std::vector<GUIElement*>::iterator i = m_child.begin(); i != m_child.end(); i++)
	{
		if ((*i)->IsEnabled())
			(*i)->Resize(width, height);
	}
}

void GUIContainer::MouseEnter(int x, int y, MouseFlags flags)
{
	GUIElement::MouseEnter(x, y, flags);
}

void GUIContainer::MouseLeave(int x, int y, MouseFlags flags)
{
	for (std::vector<GUIElement*>::iterator i = m_child.begin(); i != m_child.end(); i++)
	{
		if ((*i)->IsEnabled())
			(*i)->MouseLeave(x-(int)m_x, y-(int)m_y, flags);
	}
	GUIElement::MouseLeave(x,y,flags);
}