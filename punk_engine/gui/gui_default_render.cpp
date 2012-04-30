#include "gui_default_render.h"
#include "../math/mat4.h"
#include "widget.h"
#include "list_box.h"
#include "vertical_slider.h"

namespace GUI
{
	DefaultGUIRender::DefaultGUIRender()
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

	void DefaultGUIRender::RenderList(const ListBox* list_box) 
	{
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
		m_tc->SetTexture0(slider->GetBackgroundTexture());
		m_tc->SetTexture1(slider->GetTextTexture());
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
		m_rc->Begin();	
		m_tc->SetTexture0(slider->GetBackgroundTexture());
		m_tc->SetTexture1(slider->GetTextTexture());
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
	void DefaultGUIRender::RenderWidget(const Widget* widget)
	{
		m_rc->SetProjectionMatrix(Math::mat4::CreateIdentity());
		float x = -1 + 2*widget->GetX();
		float y = -1 + 2*widget->GetY();
		float w = widget->GetWidth();
		float h = widget->GetHeight();
		m_rc->SetWorldMatrix(Math::mat4::CreateTranslate(x, y, 0) * Math::mat4::CreateScaling(2*w, 2*h, 1));
		m_rc->SetDiffuseColor(widget->BackColor());
		m_rc->SetTextColor(widget->TextColor());
		m_rc->Begin();
		m_tc->SetTexture0(widget->GetBackgroundTexture());
		m_tc->SetTexture1(widget->GetTextTexture());
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
			child->Render(this);
		}
	}
}