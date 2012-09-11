#include "rc_bump_mapping.h"
#include "fs_bump.h"
#include "vs_bump.h"

#include "render_context_impl.h"
#include "../../../../../math/mat4.h"
#include "../../../../../math/mat3.h"
#include "../../../../../math/vec4.h"
#include "../../../../../math/vec3.h"

namespace OpenGL
{
	struct RenderContextBumpMappingImpl : public RenderContextImpl
	{
		GLuint m_proj_uniform;
		GLuint m_view_uniform;
		GLuint m_world_uniform;				
		GLuint m_normal_matrix_uniform;
		GLuint m_light_position_uniform;
		GLuint m_ambient_uniform;
		GLuint m_specular_uniform;
		GLuint m_diffuse_uniform;
		GLuint m_specular_power_uniform;
		GLuint m_diffuse_map_uniform;
		GLuint m_normal_map_uniform;

		Math::mat4 m_world;
		Math::mat4 m_view;
		Math::mat4 m_proj;
		Math::mat3 m_normal_matrix;
		Math::vec3 m_light_position;
		Math::vec4 m_ambient;
		Math::vec4 m_specular;
		Math::vec4 m_diffuse;
		float m_specular_power;

		virtual void InitAttributes()
		{

		}
		
		virtual void Begin()
		{
			RenderContextImpl::Begin();
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LESS);
			glDepthMask(GL_TRUE);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}

		virtual void End()
		{
			RenderContextImpl::End();
		}

		virtual void InitUniforms()
		{
			m_proj_uniform = glGetUniformLocation(m_program, "uProj");
			CHECK_GL_ERROR(L"Unable to get uniform location");
			m_view_uniform = glGetUniformLocation(m_program, "uView");			
			CHECK_GL_ERROR(L"Unable to get uniform location");
			m_world_uniform = glGetUniformLocation(m_program, "uWorld");
			CHECK_GL_ERROR(L"Unable to get uniform location");
			m_normal_matrix_uniform = glGetUniformLocation(m_program, "uNormalMatrix");
			CHECK_GL_ERROR(L"Unable to get uniform location");
			m_light_position_uniform = glGetUniformLocation(m_program, "uLightPosition");
			CHECK_GL_ERROR(L"Unable to get uniform location");
			m_ambient_uniform = glGetUniformLocation(m_program, "uAmbient");
			CHECK_GL_ERROR(L"Unable to get uniform location");
			m_specular_uniform = glGetUniformLocation(m_program, "uSpecular");
			CHECK_GL_ERROR(L"Unable to get uniform location");
			m_diffuse_uniform = glGetUniformLocation(m_program, "uDiffuse");
			CHECK_GL_ERROR(L"Unable to get uniform location");
			m_specular_power_uniform = glGetUniformLocation(m_program, "uSpecularPower");
			CHECK_GL_ERROR(L"Unable to get uniform location");
			m_diffuse_map_uniform = glGetUniformLocation(m_program, "uDiffuseMap");
			CHECK_GL_ERROR(L"Unable to get uniform location");
			m_normal_map_uniform = glGetUniformLocation(m_program, "uNormalMap");
			CHECK_GL_ERROR(L"Unable to get uniform location");
		}

		virtual void BindUniforms()
		{
			m_normal_matrix = (m_view*m_world).RotationPart().Inversed().Transposed();
			SetUniformMatrix4f(m_proj_uniform, &m_proj[0]);
			SetUniformMatrix4f(m_world_uniform, &m_world[0]);
			SetUniformMatrix4f(m_view_uniform, &m_view[0]);
			SetUniformMatrix3f(m_normal_matrix_uniform, &m_normal_matrix[0]);
			SetUniformVector3f(m_light_position_uniform, &m_light_position[0]);
			SetUniformVector4f(m_ambient_uniform, &m_ambient[0]);
			SetUniformVector4f(m_specular_uniform, &m_specular[0]);
			SetUniformVector4f(m_diffuse_uniform, &m_diffuse[0]);
			SetUniformFloat(m_specular_power_uniform, m_specular_power);
			SetUniformInt(m_diffuse_map_uniform, 0);
			SetUniformInt(m_normal_map_uniform, 1);
			glEnable(GL_DEPTH_TEST);			
		}

		RenderContextBumpMappingImpl()
			: RenderContextImpl()
			, m_proj_uniform()
			, m_view_uniform()
			, m_world_uniform()				
			, m_normal_matrix_uniform()
			, m_light_position_uniform()
			, m_ambient_uniform()
			, m_specular_uniform()
			, m_diffuse_uniform()
			, m_specular_power_uniform()
			, m_diffuse_map_uniform()
			, m_normal_map_uniform()
			, m_world()
			, m_view()
			, m_proj()
			, m_normal_matrix()
			, m_light_position()
			, m_ambient()
			, m_specular()
			, m_diffuse()
			, m_specular_power()
		{}

		RenderContextBumpMappingImpl::RenderContextBumpMappingImpl(const RenderContextBumpMappingImpl& impl)
			: RenderContextImpl(impl)
			, m_proj_uniform(impl.m_proj_uniform)
			, m_view_uniform(impl.m_view_uniform)
			, m_world_uniform(impl.m_world_uniform)
			, m_normal_matrix_uniform(impl.m_normal_matrix_uniform)
			, m_light_position_uniform(impl.m_light_position_uniform)
			, m_ambient_uniform(impl.m_ambient_uniform)
			, m_specular_uniform(impl.m_specular_uniform)
			, m_diffuse_uniform(impl.m_diffuse_uniform)
			, m_specular_power_uniform(impl.m_specular_power_uniform)
			, m_diffuse_map_uniform(impl.m_diffuse_map_uniform)
			, m_normal_map_uniform(impl.m_normal_map_uniform)
			, m_world(impl.m_world)
			, m_view(impl.m_view)
			, m_proj(impl.m_proj)
			, m_normal_matrix(impl.m_normal_matrix)
			, m_light_position(impl.m_light_position)
			, m_ambient(impl.m_ambient)
			, m_specular(impl.m_specular)
			, m_diffuse(impl.m_diffuse)
			, m_specular_power(impl.m_specular_power)
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
			m_diffuse = v;
		}

		void SetAmbientColor(const Math::Vector4<float>& v)
		{
			m_ambient = v;
		}

		void SetSpecularColor(const Math::Vector4<float>& v)
		{
			m_specular = v;
		}

		void SetSpecularPower(float v)
		{
			m_specular_power = v;
		}

		void SetNormalMatrix(const Math::Matrix3x3<float>& v)
		{
			m_normal_matrix = v;
		}

		void SetLightPosition(const Math::Vector3<float>& pos)
		{
			m_light_position = pos;
		};
	};

	RenderContextBumpMapping::RenderContextBumpMapping()
		: RenderContext()		
	{
		impl_rc.reset(new RenderContextBumpMappingImpl());

		std::auto_ptr<Shader> vertex(new VertexShaderBump());
		std::auto_ptr<Shader> fragment(new FragmentShaderBump());
		SetVertexShader(vertex.release());
		SetFragmentShader(fragment.release());
		impl_rc->m_vertex_attributes = VERTEX_POSITION|VERTEX_TEXTURE_0|VERTEX_NORMAL|VERTEX_TANGENT|VERTEX_BITANGENT;
	}

	RenderContextBumpMapping::RenderContextBumpMapping(const RenderContextBumpMapping& rc)
		: RenderContext(rc)
	{}

	RenderContextBumpMapping& RenderContextBumpMapping::operator= (const RenderContextBumpMapping& rc)
	{
		RenderContext::operator = (rc);
		return *this;
	}

	void RenderContextBumpMapping::SetDiffuseColor(const Math::Vector4<float>& c)
	{
		static_cast<RenderContextBumpMappingImpl*>(impl_rc.get())->SetDiffuseColor(c);
	}

	void RenderContextBumpMapping::SetProjectionMatrix(const Math::Matrix4x4<float>& m)
	{
		static_cast<RenderContextBumpMappingImpl*>(impl_rc.get())->SetProjectionMatrix(m);
	}

	void RenderContextBumpMapping::SetViewMatrix(const Math::Matrix4x4<float>& m)
	{
		static_cast<RenderContextBumpMappingImpl*>(impl_rc.get())->SetViewMatrix(m);
	}

	void RenderContextBumpMapping::SetWorldMatrix(const Math::Matrix4x4<float>& m)
	{
		static_cast<RenderContextBumpMappingImpl*>(impl_rc.get())->SetWorldMatrix(m);
	}

	void RenderContextBumpMapping::SetAmbientColor(const Math::Vector4<float>& v)
	{
		static_cast<RenderContextBumpMappingImpl*>(impl_rc.get())->SetAmbientColor(v);
	}

	void RenderContextBumpMapping::SetSpecularColor(const Math::Vector4<float>& v)
	{
		static_cast<RenderContextBumpMappingImpl*>(impl_rc.get())->SetSpecularColor(v);
	}

	void RenderContextBumpMapping::SetSpecularPower(float v)
	{
		static_cast<RenderContextBumpMappingImpl*>(impl_rc.get())->SetSpecularPower(v);
	}
	
	void RenderContextBumpMapping::SetLightPosition(const Math::Vector3<float>& pos)
	{
		static_cast<RenderContextBumpMappingImpl*>(impl_rc.get())->SetLightPosition(pos);
	};
}