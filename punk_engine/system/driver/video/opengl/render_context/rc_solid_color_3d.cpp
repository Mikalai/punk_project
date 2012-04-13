#include "rc_solid_color_3d.h"
#include "fs_solid_color.h"
#include "vs_transform_3d.h"

#include "render_context_impl.h"
#include "../../../../../math/mat4.h"
#include "../../../../../math/vec4.h"

namespace OpenGL
{
	struct RenderContextSolid3DImpl : public RenderContextImpl
	{
		GLuint m_proj_view_world_uniform;
		GLuint m_diffuse_color_uniform;
		Math::mat4 m_world;
		Math::mat4 m_view;
		Math::mat4 m_proj;
		Math::mat4 m_proj_view_world;
		Math::vec4 m_diffuse_color;
				
		virtual void InitAttributes()
		{}

		virtual void InitUniforms()
		{
			m_proj_view_world_uniform = glGetUniformLocation(m_program, "uProjViewWorld");
			CHECK_GL_ERROR(L"Unable to get uniform location");
			m_diffuse_color_uniform = glGetUniformLocation(m_program, "uDiffuseColor");
			CHECK_GL_ERROR(L"Unable to get uniform location");
		}

		virtual void BindUniforms()
		{
			m_proj_view_world = m_proj * m_view * m_world;
			SetUniformMatrix4f(m_proj_view_world_uniform, &m_proj_view_world[0]);
			SetUniformVector4f(m_diffuse_color_uniform, &m_diffuse_color[0]);

			//glEnable(GL_DEPTH_TEST);
		}

		RenderContextSolid3DImpl()
			: RenderContextImpl()
			, m_world()
			, m_view()
			, m_proj()
			, m_proj_view_world()
			, m_diffuse_color(1,0,0,1)
		{}

		RenderContextSolid3DImpl::RenderContextSolid3DImpl(const RenderContextSolid3DImpl& impl)
			: RenderContextImpl(impl)
			, m_world(impl.m_world)
			, m_view(impl.m_view)
			, m_proj(impl.m_proj)
			, m_proj_view_world(impl.m_proj_view_world)
			, m_diffuse_color(impl.m_diffuse_color)
			, m_proj_view_world_uniform(impl.m_proj_view_world_uniform)
			, m_diffuse_color_uniform(impl.m_diffuse_color_uniform)
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

	RenderContextSolid3D::RenderContextSolid3D()
		: RenderContext()		
	{
		impl_rc.reset(new RenderContextSolid3DImpl());

		std::auto_ptr<Shader> vertex(new ShaderTransform3D());
		std::auto_ptr<Shader> fragment(new ShaderSolidColor());
		SetVertexShader(vertex.release());
		SetFragmentShader(fragment.release());
		impl_rc->m_vertex_attributes = VERTEX_POSITION;
	}

	RenderContextSolid3D::RenderContextSolid3D(const RenderContextSolid3D& rc)
		: RenderContext(rc)
	{}

	RenderContextSolid3D& RenderContextSolid3D::operator= (const RenderContextSolid3D& rc)
	{
		RenderContext::operator = (rc);
		return *this;
	}

	void RenderContextSolid3D::SetDiffuseColor(const Math::Vector4<float>& c)
	{
		static_cast<RenderContextSolid3DImpl*>(impl_rc.get())->SetDiffuseColor(c);
	}

	void RenderContextSolid3D::SetProjectionMatrix(const Math::Matrix4x4<float>& m)
	{
		static_cast<RenderContextSolid3DImpl*>(impl_rc.get())->SetProjectionMatrix(m);
	}

	void RenderContextSolid3D::SetViewMatrix(const Math::Matrix4x4<float>& m)
	{
		static_cast<RenderContextSolid3DImpl*>(impl_rc.get())->SetViewMatrix(m);
	}

	void RenderContextSolid3D::SetWorldMatrix(const Math::Matrix4x4<float>& m)
	{
		static_cast<RenderContextSolid3DImpl*>(impl_rc.get())->SetWorldMatrix(m);
	}
}