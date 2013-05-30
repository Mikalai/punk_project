#include "ogl_gui_render.h"
#include "../../gpu/module.h"
#include "../../gui/module.h"
#include "../../math/module.h"

namespace Render
{
	GUIRender::GUIRender(GPU::VideoDriver* driver)
		: m_selection_color_delta(0.1f, 0.1f, 0.1f, 0.1f)
		, m_quad(driver)
	{
		m_rc = GPU::AbstractRenderPolicy::find(GPU::RenderPolicySet::GUI);
        m_tc = new GPU::TextureContext();
	}

	GUIRender::~GUIRender()
	{
		try { Clear(); } catch(...) {}
	}

	void GUIRender::Clear()
	{
		m_rc = nullptr;
		safe_delete(m_tc);
	}

	void GUIRender::RenderWidget(const GUI::Widget* widget)
	{
//		if (!widget)
//			return;

////		m_states.Push();
//		m_states.CurrentState()->Get().m_projection = Math::mat4::CreateIdentity();
//		float x = -1 + 2*widget->GetX();
//		float y = -1 + 2*widget->GetY();
//		float w = widget->GetWidth();
//		float h = widget->GetHeight();
//		m_states.CurrentState()->Get().m_local = Math::mat4::CreateTranslate(x, y, 0) * Math::mat4::CreateScaling(2*w, 2*h, 1);
//		if (widget->GetManager()->GetFocusedWidget() == widget)
//			m_states.CurrentState()->Get().m_diffuse_color = widget->BackColor() + m_selection_color_delta;
//		else
//			m_states.CurrentState()->Get().m_diffuse_color = widget->BackColor();

//		m_states.CurrentState()->Get().m_text_color = widget->TextColor();
//		m_states.CurrentState()->Get().m_use_diffuse_texture = widget->GetBackgroundTexture() != nullptr;
//		m_tc->SetTexture(1, widget->GetBackgroundTexture());
//		m_tc->SetTexture(0, widget->GetTextTexture());
//		m_states.CurrentState()->Get().m_diffuse_slot_0 = 1;
//		m_states.CurrentState()->Get().m_text_slot = 0;
//		m_states.CurrentState()->Get().m_no_diffuse_texture_color = widget->GetBackColor();
//		m_states.CurrentState()->Get().m_texture_matrix = Math::mat4::CreateReflectX();
//		m_states.CurrentState()->Get().m_enable_blending = true;
//		m_tc->Bind();

//		m_rc->Begin();
//		m_rc->BindParameters(m_states.CurrentState()->Get());

//		m_quad.Bind(m_rc->GetRequiredAttributesSet());
//		m_quad.Render();
//		m_quad.Unbind();

//		m_tc->Unbind();
//		m_rc->End();

//		for (auto o : *widget)
//		{
//			GUI::Widget* child = As<GUI::Widget*>(o);
//			if (child)
//				if (child->IsVisible())
//					child->Render(this);
//		}
//		m_states.Pop();
	}

    void GUIRender::Begin(int, int, int, int)
	{
		//m_rc->SetProjectionMatrix(Math::mat4::CreateOrthographicProjection(x, x+width, y+height, y, 0, 1));
	}

	void GUIRender::End()
	{
		m_rc->End();
	}

	//void GUIRender::RenderTabWidget(const GUI::TabWidget* tw)
	//{
	//	RenderWidget(tw);
	//}

	//void GUIRender::RenderListBox(const GUI::ListBox* lb)
	//{
	//	if (lb->GetText() == L"QWERT")
	//		lb = lb;

	//	RenderWidget(lb);

	//	if (lb->GetCurrentSelection() > lb->GetStartOffset() + lb->GetMaxVisibleItems())
	//		return;

	//	if (lb->GetCurrentSelection() != -1 && lb->GetCurrentSelection() >= lb->GetStartOffset())
	//	{
	//		Math::vec4 color(0.0f , 0.2f, 0.5f, 0.5f);
	//		float w = lb->GetWidth();
	//		float h = lb->GetHeight() * (float)lb->GetTextSize() / lb->GetTextTexture()->GetHeight();
	//		float start = float(lb->GetCurrentSelection() - lb->GetStartOffset());
	//		float x = -1 + 2*lb->GetX();
	//		float y = -1 + 2*(lb->GetY() + lb->GetHeight() - (start + 1) * h);
	//		m_rc->SetProjectionMatrix(Math::mat4::CreateIdentity());
	//		m_rc->SetWorldMatrix(Math::mat4::CreateTranslate(x, y, 0) * Math::mat4::CreateScaling(2*w, 2*h, 1));
	//		m_rc->SetDiffuseColor(color);
	//		m_rc->SetTextColor(lb->TextColor());
	//		m_tc->SetTexture1(lb->GetBackgroundTexture());
	//		m_rc->RenderDiffuseTexture(lb->GetBackgroundTexture() != 0);
	//		m_tc->SetTexture1(0);
	//		m_rc->Begin();
	//		m_tc->Bind();
	//		m_quad->Bind(m_rc->GetSupportedint());
	//		m_quad->Render();
	//		m_quad->Unbind();
	//		m_tc->Unbind();
	//		m_rc->End();
	//	}
	//}

	//void GUIRender::RenderTextBox(const GUI::TextBox* tb)
	//{
	//	m_rc->SetProjectionMatrix(Math::mat4::CreateIdentity());
	//	float x = -1 + 2*tb->GetX();
	//	float y = -1 + 2*tb->GetY();
	//	float w = tb->GetWidth();
	//	float h = tb->GetHeight();
	//	m_rc->SetWorldMatrix(Math::mat4::CreateTranslate(x, y, 0) * Math::mat4::CreateScaling(2*w, 2*h, 1));
	//	if (tb->GetManager()->GetFocusedWidget() == tb)
	//		m_rc->SetDiffuseColor(tb->BackColor() + m_selection_color_delta);
	//	else
	//		m_rc->SetDiffuseColor(tb->BackColor());
	//	m_rc->SetTextColor(tb->TextColor());
	//	m_tc->SetTexture1(tb->GetBackgroundTexture());
	//	m_rc->RenderDiffuseTexture(tb->GetBackgroundTexture() != 0);
	//	m_tc->SetTexture0(tb->GetTextTexture());
	//	m_rc->Begin();
	//	m_tc->Bind();
	//	m_quad->Bind(m_rc->GetSupportedint());
	//	m_quad->Render();
	//	m_quad->Unbind();
	//	m_tc->Unbind();
	//	m_rc->End();
	//}

	//void GUIRender::RenderVerticalSlider(const GUI::VerticalSlider* slider)
	//{
	//	m_rc->SetProjectionMatrix(Math::mat4::CreateIdentity());
	//	float x = -1 + 2*slider->GetX();
	//	float y = -1 + 2*slider->GetY();
	//	float w = slider->GetWidth();
	//	float h = slider->GetHeight();
	//	m_rc->SetWorldMatrix(Math::mat4::CreateTranslate(x, y, 0) * Math::mat4::CreateScaling(2*w, 2*h, 1));
	//	m_rc->SetDiffuseColor(slider->BackColor());
	//	m_rc->SetTextColor(slider->TextColor());
	//	m_rc->Begin();
	//	m_tc->SetTexture1(slider->GetBackgroundTexture());
	//	m_tc->SetTexture0(0);
	//	m_tc->Bind();
	//	m_quad->Bind(m_rc->GetSupportedint());
	//	m_quad->Render();
	//	m_quad->Unbind();
	//	m_tc->Unbind();
	//	m_rc->End();

	//	x = -1 + 2 * slider->GetX();
	//	y = -1 + 2 * (slider->GetY() + slider->GetHeight() * (slider->GetMax() - slider->GetCurrent()) / float(slider->GetMax() - slider->GetMin()));
	//	w = slider->GetWidth();
	//	h = 0.01f;
	//	m_rc->SetWorldMatrix(Math::mat4::CreateTranslate(x, y, 0) * Math::mat4::CreateScaling(2*w, 2*h, 1));
	//	m_rc->SetDiffuseColor(Math::vec4(1,1,1,1) - slider->BackColor());
	//	m_rc->SetTextColor(Math::vec4(1,1,1,1) - slider->TextColor());
	//	m_tc->SetTexture1(slider->GetBackgroundTexture());
	//	m_rc->RenderDiffuseTexture(slider->GetBackgroundTexture() != 0);
	//	m_tc->SetTexture0(slider->GetTextTexture());
	//	m_rc->Begin();
	//	m_tc->Bind();
	//	m_quad->Bind(m_rc->GetSupportedint());
	//	m_quad->Render();
	//	m_quad->Unbind();
	//	m_tc->Unbind();
	//	m_rc->End();
	//	/**/
	//	unsigned children_count = slider->GetChildrenCount();
	//	for (int i = 0; i < (int)children_count; ++i)
	//	{
	//		const GUI::Widget* child = slider->GetChild(i);
	//		child->Render(this);
	//	}
	//}

	//void GUIRender::RenderBalloon(const GUI::Balloon* widget)
	//{
	//	m_rc->SetProjectionMatrix(Math::mat4::CreateIdentity());
	//	float x = -1 + 2*widget->GetX();
	//	float y = -1 + 2*widget->GetY();
	//	float w = widget->GetWidth()*widget->GetScale();
	//	float h = widget->GetHeight()*widget->GetScale();
	//	m_rc->SetWorldMatrix(Math::mat4::CreateTranslate(x, y, 0) * Math::mat4::CreateScaling(2*w, 2*h, 1));
	//	m_rc->SetDiffuseColor(widget->BackColor());
	//	m_rc->SetTextColor(widget->TextColor());
	//	m_tc->SetTexture1(widget->GetBackgroundTexture());
	//	m_rc->RenderDiffuseTexture(widget->GetBackgroundTexture() != 0);
	//	m_tc->SetTexture0(widget->GetTextTexture());
	//	m_rc->Begin();
	//	m_tc->Bind();
	//	m_quad->Bind(m_rc->GetSupportedint());
	//	m_quad->Render();
	//	m_quad->Unbind();
	//	m_tc->Unbind();
	//	m_rc->End();

	//	unsigned children_count = widget->GetChildrenCount();
	//	for (int i = 0; i < (int)children_count; ++i)
	//	{
	//		const Widget* child = widget->GetChild(i);
	//		if (child->IsVisible())
	//			child->Render(this);
	//	}
	//}
}
