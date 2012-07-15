#include "../system/system.h"
#include "../system/driver/video/driver.h"

#include "scene_render.h"

namespace Render
{
	SceneRenderVisitor::SceneRenderVisitor(SceneRender& r) : render(r)
	{
	}

	void SceneRenderVisitor::operator() (System::Descriptor desc, Data& data)
	{
		//System::ResourceManager* rm = System::ResourceManager::Instance();
		//switch(desc.Type())
		//{
		//case System::RESOURCE_WIDGET:
		//	{
		//		System::Resource<GUI::Widget>* rw = rm->GetResource<GUI::Widget>(desc);
		//		GUI::Widget* w = rw->Lock();
		//		render.WidgetRender(data.x, data.y, w);
		//		rw->Unlock();
		//		data.x += w->GetX();
		//		data.y += w->GetY();
		//	}
		//	break;
		//case System::RESOURCE_BUTTON:
		//	{
		//		auto rb = rm->GetResource<GUI::Button>(desc);
		//		auto b = rb->Lock();
		//		render.ButtonRender(data.x, data.y, b);
		//		rb->Lock();
		//		data.x += b->GetX();
		//		data.y += b->GetY();
		//	}
		//	break;
		//case System::RESOURCE_MESH:
		//	{				
		//	}
		//}
	}

	SceneRender::SceneRender() : m_driver(0) {}

	void SceneRender::SetVideoDriver(OpenGL::Driver* driver)
	{
		m_driver = driver;
	}

	void SceneRender::Renderer(const Scene::SceneGraph& graph)
	{

	}

	void SceneRender::WidgetRender(float px, float py, GUI::Widget* widget)
	{
		m_driver->GetRenderContext()->Begin(m_driver->GetShaderProgram(L"solid_color_2d"));
		OpenGL::RenderContext* rc = m_driver->GetRenderContext();
		ShaderProgram* sp = rc->GetShaderProgram();				
		float x = px + widget->GetX();
		float y = py + widget->GetY();				
		Math::mat4 pvw =  Math::mat4::CreateTranslate(-1+x,-1+y,0)*Math::mat4::CreateScaling(2,2,1)*Math::mat4::CreateScaling(widget->GetWidth(), widget->GetHeight(), 1);
		sp->SetUniformMatrix4f(sp->GetLocation(UNIFORM_PROJVIEWWORLD), pvw);
		sp->SetUniformVector4f(sp->GetLocation(UNIFORM_DIFFUSE_COLOR), Math::vec4(0,0,1,0.5));
		sp->SetUniformFloat(sp->GetLocation(UNIFORM_RADIUS), 0.05);
		rc->DisableDepthTest();
		rc->EnableBlending();
		m_driver->RenderQuad();
		rc->DisableBlending();
		rc->EnableDepthTest();
		m_driver->GetRenderContext()->End();
	}

	void SceneRender::ButtonRender(float px, float py, GUI::Button* button)
	{
		int win_width = System::Window::Instance()->GetWidth();
		int win_height = System::Window::Instance()->GetHeight();

		if (button->GetTextTexture() == System::Descriptor::Root())
		{
			System::Descriptor d = m_driver->CreateStringTexture(button->GetText(), System::Window::Instance()->GetWidth()*button->GetWidth(), System::Window::Instance()->GetHeight()*button->GetHeight(), 14, L"Courier New");
			button->SetTextTexture(d);
		}

		auto res_text = System::ResourceManager::Instance()->GetResource<OpenGL::TextTexture2D>(button->GetTextTexture());
		auto texture = res_text->Lock();

		if (texture->GetWidth() != (int)((float)win_width*button->GetWidth()) || texture->GetHeight() != (int)((float)win_height*button->GetHeight()))
		{
			texture->Resize(win_width*button->GetWidth(), win_height*button->GetHeight());
			texture->RenderText(button->GetText(), 14);
		}
		else
		if (texture->GetText() != button->GetText())
		{
			texture->RenderText(button->GetText(), 14);//button->GetText());
		}

		WidgetRender(px, py, button);
		m_driver->GetRenderContext()->Begin(m_driver->GetShaderProgram(L"textured_2d"));
		OpenGL::RenderContext* rc = m_driver->GetRenderContext();
		OpenGL::TextureContext* tc = m_driver->GetTextureContext();		
		ShaderProgram* sp = rc->GetShaderProgram();
		float x = px + button->GetX();
		float y = py + button->GetY();
		Math::mat4 pvw = Math::mat4::CreateTranslate(-1+x, -1+y, 0) * Math::mat4::CreateScaling(2,2,1)*Math::mat4::CreateScaling(button->GetWidth(), button->GetHeight(), 1);
		//Math::mat4 pvw =  Math::mat4::CreateTranslate(-1+x,-1+y,0)*Math::mat4::CreateScaling(2,2,1)*Math::mat4::CreateScaling(-button->GetWidth(), -button->GetHeight(), 1);
		sp->SetUniformMatrix4f(sp->GetLocation(UNIFORM_PROJVIEWWORLD), pvw);
		sp->SetUniformVector4f(sp->GetLocation(UNIFORM_DIFFUSE_COLOR), Math::vec4(1,1,1,1));
		tc->SetTexture0(texture);
		tc->Apply();
		sp->SetTexture(sp->GetLocation(UNIFORM_DIFFUSE_MAP), 0);
		sp->SetUniformFloat(sp->GetLocation(UNIFORM_RADIUS), 0.05);
		rc->DisableDepthTest();
		rc->EnableBlending();
		m_driver->RenderQuad();
		rc->EnableDepthTest();
		m_driver->GetRenderContext()->End();

		res_text->Unlock();
	}
}