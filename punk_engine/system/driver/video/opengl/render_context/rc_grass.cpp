#include "rc_grass.h"
#include "fs_grass.h"
#include "vs_grass.h"

#include "render_context_impl.h"
#include "../../../../../math/mat4.h"
#include "../../../../../math/vec4.h"

namespace OpenGL
{
	struct RenderContextGrassImpl : public RenderContextImpl
	{
		GLuint m_proj_view_uniform;
		GLuint m_diffuse_color_uniform;
		GLuint m_diffuse_map_uniform;
		GLuint m_height_map_uniform;
		GLuint m_position_uniform;
		GLuint m_time_uniform;
		GLuint m_wind_direction_uniform;
		GLuint m_wind_strength_uniform;
		Math::vec3 m_position;
		Math::mat4 m_view;
		Math::mat4 m_proj;
		Math::mat4 m_proj_view;
		Math::vec4 m_diffuse_color;
		Math::vec3 m_wind_direction;
		float m_time;
		float m_wind_strength;

		virtual void InitAttributes()
		{

		}

		virtual void InitUniforms()
		{
			m_proj_view_uniform = glGetUniformLocation(m_program, "uProjView");
			CHECK_GL_ERROR(L"Unable to get uniform location");
			m_diffuse_color_uniform = glGetUniformLocation(m_program, "uDiffuseColor");
			CHECK_GL_ERROR(L"Unable to get uniform location");
			m_diffuse_map_uniform = glGetUniformLocation(m_program, "uDiffuseMap");
			CHECK_GL_ERROR(L"Unable to get uniform location");
			m_height_map_uniform = glGetUniformLocation(m_program, "uHeightMap");
			CHECK_GL_ERROR(L"Unable to get uniform location");
			m_position_uniform = glGetUniformLocation(m_program, "uPosition");
			CHECK_GL_ERROR(L"Unable to get uniform location");
			m_time_uniform = glGetUniformLocation(m_program, "uTime");
			CHECK_GL_ERROR(L"Unable to get uniform location");
			m_wind_direction_uniform = glGetUniformLocation(m_program, "uWindDirection");
			CHECK_GL_ERROR(L"Unable to get uniform location");
			m_wind_strength_uniform = glGetUniformLocation(m_program, "uWindStrength");
			CHECK_GL_ERROR(L"Unable to get uniform location");
		}

		virtual void BindUniforms()
		{
			m_proj_view = m_proj * m_view;
			SetUniformMatrix4f(m_proj_view_uniform, &m_proj_view[0]);
			SetUniformVector4f(m_diffuse_color_uniform, &m_diffuse_color[0]);
			SetUniformVector3f(m_position_uniform, &m_position[0]);
			SetUniformFloat(m_time_uniform, m_time);
			SetUniformFloat(m_wind_strength_uniform, m_wind_strength);
			SetUniformVector3f(m_wind_direction_uniform, &m_wind_direction[0]);
			SetUniformInt(m_diffuse_map_uniform, 0);
			SetUniformInt(m_height_map_uniform, 1);
		}

		virtual void Begin()
		{
			RenderContextImpl::Begin();
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LESS);
			glDepthMask(GL_TRUE);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}

		virtual void End()
		{
			RenderContextImpl::End();
			glEnable(GL_DEPTH_TEST);			
			glDepthFunc(GL_LESS);
			glDepthMask(GL_TRUE);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}

		RenderContextGrassImpl()
			: RenderContextImpl()
			, m_view()
			, m_proj()
			, m_proj_view()
			, m_diffuse_color(1,0,0,1)
			, m_position()
			, m_position_uniform(0)
			, m_height_map_uniform(0)
			, m_diffuse_map_uniform(0)
			, m_diffuse_color_uniform(0)
			, m_proj_view_uniform(0)
		{}

		RenderContextGrassImpl::RenderContextGrassImpl(const RenderContextGrassImpl& impl)
			: RenderContextImpl(impl)
			, m_view(impl.m_view)
			, m_proj(impl.m_proj)
			, m_proj_view(impl.m_proj_view)
			, m_diffuse_color(impl.m_diffuse_color)
			, m_proj_view_uniform(impl.m_proj_view_uniform)
			, m_diffuse_color_uniform(impl.m_diffuse_color_uniform)
			, m_diffuse_map_uniform(impl.m_diffuse_map_uniform)
			, m_height_map_uniform(impl.m_height_map_uniform)
			, m_position(impl.m_position)
			, m_position_uniform(impl.m_position_uniform)
		{}

		void SetViewMatrix(const Math::Matrix4x4<float>& m)
		{
			m_view = m;
		}

		void SetProjectionMatrix(const Math::Matrix4x4<float>& m)
		{
			m_proj = m;
		}

		void SetDiffuseColor(const Math::Vector4<float>& v)
		{
			m_diffuse_color = v;
		}

		void SetPosition(const Math::Vector3<float>& p)
		{
			m_position = p;
		}

		void SetTime(float time)
		{
			m_time = time;
		}

		void SetWindStrength(float value)
		{
			m_wind_strength = value;
		}

		void SetWindDirection(const Math::Vector3<float>& v)
		{
			m_wind_direction = v;
		}
	};

	RenderContextGrass::RenderContextGrass()
		: RenderContext()		
	{
		impl_rc.reset(new RenderContextGrassImpl());

		std::auto_ptr<Shader> vertex(new VertexShaderGrass());
		std::auto_ptr<Shader> fragment(new FragmentShaderGrass());
		SetVertexShader(vertex.release());
		SetFragmentShader(fragment.release());
		impl_rc->m_vertex_attributes = VERTEX_POSITION|VERTEX_TEXTURE_0;
	}

	RenderContextGrass::RenderContextGrass(const RenderContextGrass& rc)
		: RenderContext(rc)
	{}

	RenderContextGrass& RenderContextGrass::operator= (const RenderContextGrass& rc)
	{
		RenderContext::operator = (rc);
		return *this;
	}

	void RenderContextGrass::SetDiffuseColor(const Math::Vector4<float>& c)
	{
		static_cast<RenderContextGrassImpl*>(impl_rc.get())->SetDiffuseColor(c);
	}

	void RenderContextGrass::SetProjectionMatrix(const Math::Matrix4x4<float>& m)
	{
		static_cast<RenderContextGrassImpl*>(impl_rc.get())->SetProjectionMatrix(m);
	}

	void RenderContextGrass::SetViewMatrix(const Math::Matrix4x4<float>& m)
	{
		static_cast<RenderContextGrassImpl*>(impl_rc.get())->SetViewMatrix(m);
	}

	void RenderContextGrass::SetPosition(const Math::Vector3<float>& m)
	{
		static_cast<RenderContextGrassImpl*>(impl_rc.get())->SetPosition(m);
	}

	void RenderContextGrass::SetTime(float time)
	{
		static_cast<RenderContextGrassImpl*>(impl_rc.get())->SetTime(time);
	}

	void RenderContextGrass::SetWindStrength(float value)
	{
		static_cast<RenderContextGrassImpl*>(impl_rc.get())->SetWindStrength(value);
	}
	void RenderContextGrass::SetWindDirection(const Math::Vector3<float>& value)
	{
		static_cast<RenderContextGrassImpl*>(impl_rc.get())->SetWindDirection(value);
	}
}