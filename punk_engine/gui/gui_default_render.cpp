#include "gui_default_render.h"
#include "../math/mat4.h"
#include "widget.h"

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

	void DefaultGUIRender::RenderWidget(const Widget* widget)
	{
		unsigned children_count = widget->GetChildrenCount();
		for (int i = 0; i < children_count; ++i)
		{
			const Widget* child = widget->GetChild(i);
			child->Render(this);
		}
		m_rc->SetProjectionMatrix(Math::mat4::CreateIdentity());
		m_rc->SetWorldMatrix(Math::mat4::CreateTranslate(widget->GetX() - 1, widget->GetY() - 1, 0) * Math::mat4::CreateScaling(2*widget->GetWidth(), 2*widget->GetHeight(), 1));
		m_rc->SetDiffuseColor(Math::vec4(1,1,1,0.5));
		m_rc->Begin();
		m_tc->SetTexture0(widget->GetBackgroundTexture());
		m_tc->SetTexture1(widget->GetTextTexture());
		m_tc->Bind();
		m_quad->Bind(m_rc->GetSupportedVertexAttributes());
		m_quad->Render();
		m_quad->Unbind();
		m_tc->Unbind();
		m_rc->End();

		//		m_driver->GetRenderContext()->Begin(m_driver->GetShaderProgram(L"solid_color_2d"));
		//OpenGL::RenderContext* rc = m_driver->GetRenderContext();
		//ShaderProgram* sp = rc->GetShaderProgram();				
		//float x = px + widget->GetX();
		//float y = py + widget->GetY();				
		//Math::mat4 pvw =  Math::mat4::CreateTranslate(-1+x,-1+y,0)*Math::mat4::CreateScaling(2,2,1)*Math::mat4::CreateScaling(widget->GetWidth(), widget->GetHeight(), 1);
		//sp->SetUniformMatrix4f(sp->GetLocation(UNIFORM_PROJVIEWWORLD), pvw);
		//sp->SetUniformVector4f(sp->GetLocation(UNIFORM_DIFFUSE_COLOR), Math::vec4(0,0,1,0.5));
		//sp->SetUniformFloat(sp->GetLocation(UNIFORM_RADIUS), 0.05);
		//rc->DisableDepthTest();
		//rc->EnableBlending();
		//m_driver->RenderQuad();
		//rc->DisableBlending();
		//rc->EnableDepthTest();
		//m_driver->GetRenderContext()->End();
	}
}