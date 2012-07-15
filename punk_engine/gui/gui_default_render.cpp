#include "gui_default_render.h"
#include "manager.h"
#include "../math/mat4.h"
#include "widget.h"
#include "list_box.h"
#include "vertical_scrollbar.h"
#include "vertical_slider.h"
#include "edit_box.h"
#include "tab_widget.h"
#include "balloon.h"

namespace GUI
{
	DefaultGUIRender::DefaultGUIRender()
		: m_selection_color_delta(0.1, 0.1, 0.1, 0.1)
	{
		m_quad.reset(new OpenGL::QuadObject());
		m_quad->Init();
		m_rc.reset(new OpenGL::RenderContextGUI());
		m_tc.reset(new OpenGL::TextureContext());
	}

	DefaultGUIRender::~DefaultGUIRender()
	{
	}

	void DefaultGUIRender::Begin(int x, int y, int width, int height)
	{
		//m_rc->SetProjectionMatrix(Math::mat4::CreateOrthographicProjection(x, x+width, y+height, y, 0, 1));
	}

	void DefaultGUIRender::End()
	{
		m_rc->End();
	}

	void DefaultGUIRender::RenderTabWidget(const TabWidget* tw) 
	{
		RenderWidget(tw);
	}

	void DefaultGUIRender::RenderListBox(const ListBox* lb)
	{
		RenderWidget(lb);

		if (lb->GetCurrentSelection() > lb->GetStartOffset() + lb->GetMaxVisibleItems())
			return;

		if (lb->GetCurrentSelection() != -1 && lb->GetCurrentSelection() >= lb->GetStartOffset())
		{
			Math::vec4 color(0.0f , 0.2f, 0.5f, 0.5f);
			float w = lb->GetWidth();
			float h = lb->GetHeight() * (float)lb->GetTextSize() / lb->GetTextTexture()->GetHeight();
			float start = lb->GetCurrentSelection() - lb->GetStartOffset();
			float x = -1 + 2*lb->GetX();			
			float y = -1 + 2*(lb->GetY() + lb->GetHeight() - (start + 1) * h);			
			m_rc->SetProjectionMatrix(Math::mat4::CreateIdentity());									
			m_rc->SetWorldMatrix(Math::mat4::CreateTranslate(x, y, 0) * Math::mat4::CreateScaling(2*w, 2*h, 1));
			m_rc->SetDiffuseColor(color);
			m_rc->SetTextColor(lb->TextColor());			
			m_tc->SetTexture1(lb->GetBackgroundTexture());
			m_rc->RenderDiffuseTexture(lb->GetBackgroundTexture() != 0);
			m_tc->SetTexture1(0);
			m_rc->Begin();
			m_tc->Bind();
			m_quad->Bind(m_rc->GetSupportedVertexAttributes());
			m_quad->Render();
			m_quad->Unbind();
			m_tc->Unbind();
			m_rc->End();
		}
	}

	void DefaultGUIRender::RenderTextBox(const TextBox* tb)
	{
		m_rc->SetProjectionMatrix(Math::mat4::CreateIdentity());
		float x = -1 + 2*tb->GetX();
		float y = -1 + 2*tb->GetY();
		float w = tb->GetWidth();
		float h = tb->GetHeight();
		m_rc->SetWorldMatrix(Math::mat4::CreateTranslate(x, y, 0) * Math::mat4::CreateScaling(2*w, 2*h, 1));
		if (tb->GetManager()->GetFocusedWidget() == tb)
			m_rc->SetDiffuseColor(tb->BackColor() + m_selection_color_delta);
		else
			m_rc->SetDiffuseColor(tb->BackColor());
		m_rc->SetTextColor(tb->TextColor());		
		m_tc->SetTexture1(tb->GetBackgroundTexture());
		m_rc->RenderDiffuseTexture(tb->GetBackgroundTexture() != 0);
		m_tc->SetTexture0(tb->GetTextTexture());
		m_rc->Begin();
		m_tc->Bind();
		m_quad->Bind(m_rc->GetSupportedVertexAttributes());
		m_quad->Render();
		m_quad->Unbind();
		m_tc->Unbind();
		m_rc->End();
	}

	void DefaultGUIRender::RenderVerticalSlider(const VerticalSlider* slider)
	{
		m_rc->SetProjectionMatrix(Math::mat4::CreateIdentity());
		float x = -1 + 2*slider->GetX();
		float y = -1 + 2*slider->GetY();
		float w = slider->GetWidth();
		float h = slider->GetHeight();
		m_rc->SetWorldMatrix(Math::mat4::CreateTranslate(x, y, 0) * Math::mat4::CreateScaling(2*w, 2*h, 1));
		m_rc->SetDiffuseColor(slider->BackColor());
		m_rc->SetTextColor(slider->TextColor());
		m_rc->Begin();
		m_tc->SetTexture1(slider->GetBackgroundTexture());
		m_tc->SetTexture0(0);
		m_tc->Bind();
		m_quad->Bind(m_rc->GetSupportedVertexAttributes());
		m_quad->Render();			
		m_quad->Unbind();
		m_tc->Unbind();
		m_rc->End();

		x = -1 + 2 * slider->GetX();
		y = -1 + 2 * (slider->GetY() + slider->GetHeight() * (slider->GetMax() - slider->GetCurrent()) / float(slider->GetMax() - slider->GetMin()));
		w = slider->GetWidth();
		h = 0.01;					
		m_rc->SetWorldMatrix(Math::mat4::CreateTranslate(x, y, 0) * Math::mat4::CreateScaling(2*w, 2*h, 1));
		m_rc->SetDiffuseColor(Math::vec4(1,1,1,1) - slider->BackColor());
		m_rc->SetTextColor(Math::vec4(1,1,1,1) - slider->TextColor());		
		m_tc->SetTexture1(slider->GetBackgroundTexture());
		m_rc->RenderDiffuseTexture(slider->GetBackgroundTexture() != 0);
		m_tc->SetTexture0(slider->GetTextTexture());
		m_rc->Begin();	
		m_tc->Bind();
		m_quad->Bind(m_rc->GetSupportedVertexAttributes());
		m_quad->Render();			
		m_quad->Unbind();
		m_tc->Unbind();
		m_rc->End();
		/**/
		unsigned children_count = slider->GetChildrenCount();
		for (int i = 0; i < children_count; ++i)
		{
			const Widget* child = slider->GetChild(i);
			child->Render(this);
		}
	}

	void DefaultGUIRender::RenderBalloon(const Balloon* widget)
	{
		m_rc->SetProjectionMatrix(Math::mat4::CreateIdentity());
		float x = -1 + 2*widget->GetX();
		float y = -1 + 2*widget->GetY();
		float w = widget->GetWidth()*widget->GetScale();
		float h = widget->GetHeight()*widget->GetScale();
		m_rc->SetWorldMatrix(Math::mat4::CreateTranslate(x, y, 0) * Math::mat4::CreateScaling(2*w, 2*h, 1));
		m_rc->SetDiffuseColor(widget->BackColor());
		m_rc->SetTextColor(widget->TextColor());		
		m_tc->SetTexture1(widget->GetBackgroundTexture());
		m_rc->RenderDiffuseTexture(widget->GetBackgroundTexture() != 0);
		m_tc->SetTexture0(widget->GetTextTexture());
		m_rc->Begin();
		m_tc->Bind();
		m_quad->Bind(m_rc->GetSupportedVertexAttributes());
		m_quad->Render();
		m_quad->Unbind();
		m_tc->Unbind();
		m_rc->End();

		unsigned children_count = widget->GetChildrenCount();
		for (int i = 0; i < children_count; ++i)
		{
			const Widget* child = widget->GetChild(i);
			if (child->IsVisible())
				child->Render(this);
		}
	}

	void DefaultGUIRender::RenderWidget(const Widget* widget)
	{
		m_rc->SetProjectionMatrix(Math::mat4::CreateIdentity());
		float x = -1 + 2*widget->GetX();
		float y = -1 + 2*widget->GetY();
		float w = widget->GetWidth();
		float h = widget->GetHeight();
		m_rc->SetWorldMatrix(Math::mat4::CreateTranslate(x, y, 0) * Math::mat4::CreateScaling(2*w, 2*h, 1));
		if (widget->GetManager()->GetFocusedWidget() == widget)
			m_rc->SetDiffuseColor(widget->BackColor() + m_selection_color_delta);
		else
			m_rc->SetDiffuseColor(widget->BackColor());
		m_rc->SetTextColor(widget->TextColor());		
		m_rc->RenderDiffuseTexture(widget->GetBackgroundTexture() != 0);
		m_tc->SetTexture1(widget->GetBackgroundTexture());		
		m_tc->SetTexture0(widget->GetTextTexture());
		m_rc->Begin();
		m_tc->Bind();		
		m_quad->Bind(m_rc->GetSupportedVertexAttributes());
		m_quad->Render();
		m_quad->Unbind();
		m_tc->Unbind();
		m_rc->End();

		unsigned children_count = widget->GetChildrenCount();
		for (int i = 0; i < children_count; ++i)
		{
			const Widget* child = widget->GetChild(i);
			if (child->IsVisible())
				child->Render(this);
		}
	}
}