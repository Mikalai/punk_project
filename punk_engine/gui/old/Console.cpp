#include "Console.h"
#include "Manager.h"

GUIConsole::GUIConsole() : GUIElement(0, 0, GUIManager::g_render->GetSrceenWidth(), GUIManager::g_render->GetScreenHeight() / 2, "")
{
	m_child.push_back(new GUITextBox(0, m_height-20, m_width, 20, ""));
	m_child.back()->SetParent(this);
	m_child.push_back(new GUIScrollBar(m_width-20, 0, 20, m_height-20, 10));
	m_child.back()->SetParent(this);
/*	m_input = dynamic_cast<GUITextBox*>(g_manager->CreateTextBox(0, GUIManager::g_render->GetScreenHeight()/2, GUIManager::g_render->GetSrceenWidth(), 20, ""));
	m_input->OnKeyEnter(EventHandler(this, &GUIConsole::OnEnterHandlerCallback));//this, &GUIConsole::OnEnterHandler1));
	m_input->SetBackColor(0.2f, 0.2f, 0.2f, 1);
	m_input->SetFontColor(0, 1, 0, 1);*/
	m_fontColor = Color(0,1,0,0);
	m_backColor = Color(0,0,0,0);
}


void GUIConsole::OnEnterHandlerCallback(Parameters params)
{
	m_history.push_back(m_child[0]->GetText());
	dynamic_cast<GUITextBox*>(m_child[0])->Reset();			//text box
	params.data.userInput = &m_history.back();
	onKeyEnterMethod(params);		
	dynamic_cast<GUIScrollBar*>(m_child[1])->SetMaxScroll(m_history.size());	//scroll bar
}

void GUIConsole::Update(float delta)
{
	for (std::vector<GUIElement*>::iterator i = m_child.begin(); i != m_child.end(); i++)
		(*i)->Update(delta);
}

void GUIConsole::Add(PunkString text)
{
	m_history.push_back(text);
}

PunkString GUIConsole::Last()
{
	return m_history.back();
}

GUIConsole::~GUIConsole()
{
	for (std::vector<GUIElement*>::iterator i = m_child.begin(); i != m_child.end(); i++)
		delete (*i);
}

void GUIConsole::ElementDraw()
{
	GUIManager::g_render->Enter2DMode((int)m_x, (int)m_y, (int)m_width, (int)m_height, 0, 0, (int)m_width, (int)m_height);
	GUIManager::g_render->SetColor(m_backColor.r,m_backColor.g,m_backColor.b,m_backColor.a);
	GUIManager::g_render->RenderRect(m_x, m_y, m_width, m_height);	
	float y = m_height-45;
	int skip = dynamic_cast<GUIScrollBar*>(m_child[1])->GetScrollPosition();
	GUIManager::g_render->SetColor(m_fontColor.r,m_fontColor.g,m_fontColor.b,m_fontColor.a);
	for (std::vector<PunkString>::reverse_iterator i = m_history.rbegin(); i != m_history.rend(); i++)
	{
		if (skip <= 0)
		{
			int lines = 0;			
			GUIManager::g_render->SmartRenderText(m_x, y, m_width, m_height, (TextOptions)TEXT_WRAP, &lines, i->CString());
			y -= 16*lines;
			if (y < 0)
				break;
		}
		else
		{
			skip--;
		}
	}
	m_child[0]->Draw();
	m_child[1]->Draw();	
	GUIManager::g_render->Leave2DMode();
}

void GUIConsole::Resize(unsigned int width, unsigned int height)
{
	m_x = 0;
	m_y = 0;
	m_width = GUIManager::g_render->GetSrceenWidth();
	m_height = (float)height / 2;
	m_child[0]->SetWidth((float)width);
	m_child[0]->SetPosition(0, (float)m_height-20);
	m_child[1]->SetHeight(m_height-20);
	m_child[1]->SetPosition(m_width-20, 0);
	dynamic_cast<GUIScrollBar*>(m_child[1])->ResizeElements();
}

void GUIConsole::OnKeyEnter(Handler eventHandler)
{
	GUIElement::OnKeyEnter(eventHandler);
}

void GUIConsole::MouseLeftButtonDown(int x, int y, MouseFlags flags)
{
	for (std::vector<GUIElement*>::iterator i = m_child.begin(); i != m_child.end(); i++)
	{
		if ((*i)->IsMouseOver())
		{
			(*i)->MouseLeftButtonDown(x, y, flags);
			break;
		}
	}
}

void GUIConsole::MouseLeftButtonUp(int x, int y, MouseFlags flags)
{
	for (std::vector<GUIElement*>::iterator i = m_child.begin(); i != m_child.end(); i++)
	{
		if ((*i)->IsEnabled())
			(*i)->MouseLeftButtonUp(x-(int)m_x, y-(int)m_y, flags);
	}
}

void GUIConsole::MouseMove(int x, int y, MouseFlags flags)
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


void GUIConsole::MouseLeave(int x, int y, MouseFlags flags)
{
	for (std::vector<GUIElement*>::iterator i = m_child.begin(); i != m_child.end(); i++)
	{
		if ((*i)->IsEnabled())
			(*i)->MouseLeave(x-(int)m_x, y-(int)m_y, flags);
	}
	GUIElement::MouseLeave(x,y,flags);
}

void GUIConsole::KeyChar(unsigned int code, KeyFlags flags)
{
	switch(code)
	{
	case BUTTON_ENTER:
		OnEnterHandlerCallback(Parameters(code, flags));
		break;
	default:
		dynamic_cast<GUITextBox*>(m_child[0])->KeyChar(code, flags);
	}
}

void GUIConsole::KeyDown(unsigned code, KeyFlags flags)
{
	dynamic_cast<GUITextBox*>(m_child[0])->KeyDown(code, flags);
}

void GUIConsole::MouseWheel(int delta, int x, int y, MouseFlags)
{
	GUIScrollBar* m_scroll = dynamic_cast<GUIScrollBar*>(m_child[1]);
	m_scroll->SetScrollPosition(m_scroll->GetScrollPosition() + delta);
}