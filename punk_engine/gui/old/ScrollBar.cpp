#include "ScrollBar.h"
#include "Manager.h"

GUIScrollBar::GUIScrollBar(float x, float y, float width, float height, int maxPos, bool isVertical) :
GUIElement(x, y, width, height, ""), m_isVertical(isVertical), m_pos(0), m_max(maxPos)
{
	if (m_isVertical)
	{	
		//		 ___
		//		| 1 |
		//		|___|
		//		| 2 |
		//		|	|
		//		|___|
		//		| 3 |
		//		|___|
		//		| 4	|
		//		|	|
		//		|	|
		//		|___|
		//		| 5 |
		//		|___|
		//

		//
		//	1
		//
		m_btns.push_back(new GUIButton(0, 0,    width, 20, ""));
		m_btns.back()->SetBackColor(1,0,0,1);
		dynamic_cast<GUIButton*>(m_btns.back())->SetBackColorUp(Color(0.7f, 0.7f, 0.7f, 0.7f));
		dynamic_cast<GUIButton*>(m_btns.back())->SetBackColorDown(Color(0.2f, 0.2f, 0.2f, 1));
		dynamic_cast<GUIButton*>(m_btns.back())->SetBackColorMouseOver(Color(0.8f, 0.8f, 0.8f, 1));
		m_btns.back()->OnClick(EventHandler(this, &GUIScrollBar::MoveUp));

		//
		//	2
		//
		m_btns.push_back(new GUIButton(0, 20, width, 0, ""));
		dynamic_cast<GUIButton*>(m_btns.back())->SetBackColorUp(Color(0.5f, 0.5f, 0.5f, 0.7f));
		dynamic_cast<GUIButton*>(m_btns.back())->SetBackColorDown(Color(0.2f, 0.2f, 0.2f, 1));
		dynamic_cast<GUIButton*>(m_btns.back())->SetBackColorMouseOver(Color(0.6f, 0.6f, 0.6f, 1));
		m_btns.back()->SetBackColor(0,1,0,1);
		m_btns.back()->OnClick(EventHandler(this, &GUIScrollBar::MoveUpPage));
		//
		//	3
		//
		m_btns.push_back(new GUIButton(0, 20, width, 20, ""));
		dynamic_cast<GUIButton*>(m_btns.back())->SetBackColorUp(Color(0.7f, 0.7f, 0.7f, 0.7f));
		dynamic_cast<GUIButton*>(m_btns.back())->SetBackColorDown(Color(0.2f, 0.2f, 0.2f, 1));
		dynamic_cast<GUIButton*>(m_btns.back())->SetBackColorMouseOver(Color(0.8f, 0.8f, 0.8f, 1));
		m_btns.back()->SetBackColor(1,0,1,1);
		//
		//	4
		//
		m_btns.push_back(new GUIButton(0, 40, width, height-60, ""));
		dynamic_cast<GUIButton*>(m_btns.back())->SetBackColorUp(Color(0.5f, 0.5f, 0.5f, 0.7f));
		dynamic_cast<GUIButton*>(m_btns.back())->SetBackColorDown(Color(0.2f, 0.2f, 0.2f, 1));
		dynamic_cast<GUIButton*>(m_btns.back())->SetBackColorMouseOver(Color(0.6f, 0.6f, 0.6f, 1));
		m_btns.back()->SetBackColor(1,0,1,1);
		m_btns.back()->OnClick(EventHandler(this, &GUIScrollBar::MoveDownPage));
		//
		//	5
		//
		m_btns.push_back(new GUIButton(0, height-20, width, 20, ""));
		dynamic_cast<GUIButton*>(m_btns.back())->SetBackColorUp(Color(0.7f, 0.7f, 0.7f, 0.7f));
		dynamic_cast<GUIButton*>(m_btns.back())->SetBackColorDown(Color(0.2f, 0.2f, 0.2f, 1));
		dynamic_cast<GUIButton*>(m_btns.back())->SetBackColorMouseOver(Color(0.8f, 0.8f, 0.8f, 1));
		m_btns.back()->SetBackColor(1,1,0,1);
		m_btns.back()->OnClick(EventHandler(this, &GUIScrollBar::MoveDown));
	}
	for (std::vector<GUIButton*>::iterator i = m_btns.begin(); i != m_btns.end(); i++)
		(*i)->SetParent(this);
}

GUIScrollBar::~GUIScrollBar()
{
	for (std::vector<GUIButton*>::iterator i = m_btns.begin(); i != m_btns.end(); i++)
		delete (*i);
}


void GUIScrollBar::ResizeElements()
{
	float abc = m_height-60;
	float a = abc * m_pos / (float)m_max;
	float b = abc * (m_max - m_pos) / (float)m_max;
	m_btns[1]->SetHeight(a);
	m_btns[2]->SetPosition(0, 20+a);
	m_btns[3]->SetPosition(0, 40+a);
	m_btns[3]->SetHeight(b);
	m_btns[4]->SetPosition(0, m_height-20);
}

void GUIScrollBar::MoveDown(Parameters p)
{
	if (m_pos < m_max)
		m_pos++;
	ResizeElements();
}

void GUIScrollBar::MoveUp(Parameters p)
{
	if (m_pos > 0)
		m_pos--;
	ResizeElements();
}

void GUIScrollBar::MoveDownPage(Parameters p)
{
	m_pos += 10;
	if (m_pos > m_max)
		m_pos = m_max;
	ResizeElements();
}

void GUIScrollBar::MoveUpPage(Parameters p)
{
	m_pos -= 10;
	if (m_pos < 0)
		m_pos = 0;
	ResizeElements();
}

void GUIScrollBar::ElementDraw()
{
	GUIManager::g_render->Enter2DMode((int)m_x, (int)m_y, (int)m_width, (int)m_height, 0, 0, (int)m_width, (int)m_height);
	for (std::vector<GUIButton*>::iterator i = m_btns.begin(); i != m_btns.end(); i++)
		(*i)->Draw();
	GUIManager::g_render->Leave2DMode();
}

void GUIScrollBar::Update(float delta)
{
	for (std::vector<GUIButton*>::iterator i = m_btns.begin(); i != m_btns.end(); i++)
		(*i)->Update(delta);
}

void GUIScrollBar::SetScrollPosition(int pos)
{	
	m_pos = pos;
	if (m_pos < 0)
		m_pos = 0;
	if (m_pos > m_max)
		m_pos = m_max;
	ResizeElements();
}

int GUIScrollBar::GetScrollPosition() const
{
	return m_pos;
}

void GUIScrollBar::SetMaxScroll(int max)
{
	m_max = max;
}

int GUIScrollBar::GetMaxScroll() const
{
	return m_max;
}

void GUIScrollBar::MouseLeftButtonDown(int x, int y, MouseFlags flags)
{
	for (std::vector<GUIButton*>::iterator i = m_btns.begin(); i != m_btns.end(); i++)
	{
		if ((*i)->IsMouseOver())
		{
			(*i)->MouseLeftButtonDown(x, y, flags);
			break;
		}
	}
}

void GUIScrollBar::MouseLeftButtonUp(int x, int y, MouseFlags flags)
{
	for (std::vector<GUIButton*>::iterator i = m_btns.begin(); i != m_btns.end(); i++)
	{
		if ((*i)->IsEnabled())
			(*i)->MouseLeftButtonUp(x-(int)m_x, y-(int)m_y, flags);
	}
}

void GUIScrollBar::MouseMove(int x, int y, MouseFlags flags)
{ 	
	for (std::vector<GUIButton*>::iterator i = m_btns.begin(); i != m_btns.end(); i++)
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


void GUIScrollBar::MouseLeave(int x, int y, MouseFlags flags)
{
	for (std::vector<GUIButton*>::iterator i = m_btns.begin(); i != m_btns.end(); i++)
	{
		if ((*i)->IsEnabled())
			(*i)->MouseLeave(x-(int)m_x, y-(int)m_y, flags);
	}
	GUIElement::MouseLeave(x,y,flags);
}