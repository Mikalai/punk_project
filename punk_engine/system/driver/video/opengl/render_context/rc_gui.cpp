#include "rc_gui.h"
#include "fs_gui.h"
#include "vs_gui.h"

#include "render_context_impl.h"
#include "../../../../../math/mat4.h"
#include "../../../../../math/vec4.h"

namespace OpenGL
{
	struct RenderContextGUIImpl : public RenderContextImpl
	{
		GLuint m_proj_view_world_uniform;
		GLuint m_diffuse_color_uniform;
		GLuint m_diffuse_map_uniform;
		GLuint m_text_map_uniform;

		Math::mat4 m_world;
		Math::mat4 m_view;
		Math::mat4 m_proj;
		Math::mat4 m_proj_view_world;
		Math::vec4 m_diffuse_color;
				
		virtual void InitAttributes()
		{

		}

		virtual void InitUniforms()
		{
			m_proj_view_world_uniform = glGetUniformLocation(m_program, "uProjViewWorld");
			CHECK_GL_ERROR(L"Unable to get uniform location");
			m_diffuse_color_uniform = glGetUniformLocation(m_program, "uDiffuseColor");
			CHECK_GL_ERROR(L"Unable to get uniform location");
			m_diffuse_map_uniform = glGetUniformLocation(m_program, "uDiffuseMap");
			CHECK_GL_ERROR(L"Unable to get uniform location");
			m_text_map_uniform = glGetUniformLocation(m_program, "uTextMap");
			CHECK_GL_ERROR(L"Unable to get uniform location");
		}

		virtual void BindUniforms()
		{
			m_proj_view_world = m_proj * m_view * m_world;
			SetUniformMatrix4f(m_proj_view_world_uniform, &m_proj_view_world[0]);
			SetUniformVector4f(m_diffuse_color_uniform, &m_diffuse_color[0]);
			SetUniformInt(m_diffuse_map_uniform, 1);
			SetUniformInt(m_text_map_uniform, 0);
			glDisable(GL_DEPTH_TEST);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}

		RenderContextGUIImpl()
			: RenderContextImpl()
			, m_world()
			, m_view()
			, m_proj()
			, m_proj_view_world()
			, m_diffuse_color(1,0,0,1)
			, m_diffuse_map_uniform(0)
			, m_diffuse_color_uniform(0)
			, m_proj_view_world_uniform(0)
		{}

		RenderContextGUIImpl::RenderContextGUIImpl(const RenderContextGUIImpl& impl)
			: RenderContextImpl(impl)
			, m_world(impl.m_world)
			, m_view(impl.m_view)
			, m_proj(impl.m_proj)
			, m_proj_view_world(impl.m_proj_view_world)
			, m_diffuse_color(impl.m_diffuse_color)
			, m_proj_view_world_uniform(impl.m_proj_view_world_uniform)
			, m_diffuse_color_uniform(impl.m_diffuse_color_uniform)
			, m_diffuse_map_uniform(impl.m_diffuse_map_uniform)
		{}

		void SetViewMatrix(const Math::Matrix4x4<float>& m)
		{
			m_view = m;
		}

		void SetWorldMatrix(const Math::Matrix4x4<float>& m)
		{
			m_world = m;
		}

		void SetProjectionMatrix(const Math::Matrix4x4<float>& m)
		{
			m_proj = m;
		}

		void SetDiffuseColor(const Math::Vector4<float>& v)
		{
			m_diffuse_color = v;
		}
	};

	RenderContextGUI::RenderContextGUI()
		: RenderContext()		
	{
		impl_rc.reset(new RenderContextGUIImpl());

		std::auto_ptr<Shader> vertex(new VertexShaderGUI());
		std::auto_ptr<Shader> fragment(new FragmentShaderGUI());
		SetVertexShader(vertex.release());
		SetFragmentShader(fragment.release());
		impl_rc->m_vertex_attributes = VERTEX_POSITION|VERTEX_TEXTURE_0;
	}

	RenderContextGUI::RenderContextGUI(const RenderContextGUI& rc)
		: RenderContext(rc)
	{}

	RenderContextGUI& RenderContextGUI::operator= (const RenderContextGUI& rc)
	{
		RenderContext::operator = (rc);
		return *this;
	}

	void RenderContextGUI::SetDiffuseColor(const Math::Vector4<float>& c)
	{
		static_cast<RenderContextGUIImpl*>(impl_rc.get())->SetDiffuseColor(c);
	}

	void RenderContextGUI::SetProjectionMatrix(const Math::Matrix4x4<float>& m)
	{
		static_cast<RenderContextGUIImpl*>(impl_rc.get())->SetProjectionMatrix(m);
	}

	void RenderContextGUI::SetViewMatrix(const Math::Matrix4x4<float>& m)
	{
		static_cast<RenderContextGUIImpl*>(impl_rc.get())->SetViewMatrix(m);
	}

	void RenderContextGUI::SetWorldMatrix(const Math::Matrix4x4<float>& m)
	{
		static_cast<RenderContextGUIImpl*>(impl_rc.get())->SetWorldMatrix(m);
	}
}