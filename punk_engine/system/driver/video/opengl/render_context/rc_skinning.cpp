#include "rc_skinning.h"
#include "fs_skinning.h"
#include "vs_skinning.h"

#include "render_context_impl.h"
#include "../../../../../math/mat4.h"
#include "../../../../../math/mat3.h"
#include "../../../../../math/vec4.h"
#include "../../../../../math/vec3.h"

namespace OpenGL
{
	struct RenderContextSkinningImpl : public RenderContextImpl
	{
		static const int MAX_BONES = 64;

		GLuint m_proj_uniform;
		GLuint m_view_uniform;
		GLuint m_world_uniform;				
		GLuint m_mesh_matrix_uniform;		
		GLuint m_mesh_matrix_inversed_uniform;		
		GLuint m_normal_matrix_uniform;
		GLuint m_light_position_uniform;
		GLuint m_ambient_uniform;
		GLuint m_specular_uniform;
		GLuint m_diffuse_uniform;
		GLuint m_specular_power_uniform;
		GLuint m_diffuse_map_uniform;
		GLuint m_normal_map_uniform;
		GLuint m_bone_uniform[MAX_BONES];

		Math::mat4 m_world;
		Math::mat4 m_view;
		Math::mat4 m_proj;
		Math::mat4 m_mesh_matrix;
		Math::mat4 m_mesh_matrix_inversed;
		Math::mat3 m_normal_matrix;
		Math::vec3 m_light_position;
		Math::vec4 m_ambient;
		Math::vec4 m_specular;
		Math::vec4 m_diffuse;
		Math::mat4 m_bone[MAX_BONES];
		float m_specular_power;

		virtual void InitAttributes()
		{

		}

		virtual void InitUniforms()
		{
			m_proj_uniform = glGetUniformLocation(m_program, "uProj");
			CHECK_GL_ERROR(L"Unable to get uniform location");
			m_view_uniform = glGetUniformLocation(m_program, "uView");			
			CHECK_GL_ERROR(L"Unable to get uniform location");
			m_world_uniform = glGetUniformLocation(m_program, "uWorld");
			CHECK_GL_ERROR(L"Unable to get uniform location");
			m_mesh_matrix_uniform = glGetUniformLocation(m_program, "uMeshMatrix");
			CHECK_GL_ERROR(L"Unable to get uniform location");
			m_mesh_matrix_inversed_uniform = glGetUniformLocation(m_program, "uMeshMatrixInversed");
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

			for (int i = 0; i < MAX_BONES; ++i)
			{
				char buf[128];
				sprintf_s<128>(buf, "uBones[%d]", i);
				m_bone_uniform[i] = glGetUniformLocation(m_program, buf);
			}
		}

		virtual void BindUniforms()
		{
			m_normal_matrix = (m_view*m_world).RotationPart().Inversed().Transposed();
			SetUniformMatrix4f(m_proj_uniform, &m_proj[0]);
			SetUniformMatrix4f(m_world_uniform, &m_world[0]);
			SetUniformMatrix4f(m_view_uniform, &m_view[0]);
			SetUniformMatrix4f(m_mesh_matrix_uniform, &m_mesh_matrix[0]);			
			SetUniformMatrix4f(m_mesh_matrix_inversed_uniform, &m_mesh_matrix_inversed[0]);
			SetUniformMatrix3f(m_normal_matrix_uniform, &m_normal_matrix[0]);
			SetUniformVector3f(m_light_position_uniform, &m_light_position[0]);
			SetUniformVector4f(m_ambient_uniform, &m_ambient[0]);
			SetUniformVector4f(m_specular_uniform, &m_specular[0]);
			SetUniformVector4f(m_diffuse_uniform, &m_diffuse[0]);
			SetUniformFloat(m_specular_power_uniform, m_specular_power);
			SetUniformInt(m_diffuse_map_uniform, 0);
			SetUniformInt(m_normal_map_uniform, 1);
			for (int i = 0; i < MAX_BONES; ++i)
			{
				SetUniformMatrix4f(m_bone_uniform[i], &m_bone[i][0]);
			}
		}

		RenderContextSkinningImpl()
			: RenderContextImpl()
			, m_proj_uniform()
			, m_view_uniform()
			, m_world_uniform()		
			, m_mesh_matrix_uniform()
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
			, m_mesh_matrix()
			, m_normal_matrix()
			, m_light_position()
			, m_ambient()
			, m_specular()
			, m_diffuse()
			, m_specular_power()
		{}

		RenderContextSkinningImpl::RenderContextSkinningImpl(const RenderContextSkinningImpl& impl)
			: RenderContextImpl(impl)
			, m_proj_uniform(impl.m_proj_uniform)
			, m_view_uniform(impl.m_view_uniform)
			, m_world_uniform(impl.m_world_uniform)
			, m_mesh_matrix_uniform(impl.m_mesh_matrix_uniform)
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
			, m_mesh_matrix(impl.m_mesh_matrix)
			, m_normal_matrix(impl.m_normal_matrix)
			, m_light_position(impl.m_light_position)
			, m_ambient(impl.m_ambient)
			, m_specular(impl.m_specular)
			, m_diffuse(impl.m_diffuse)
			, m_specular_power(impl.m_specular_power)
		{}

		virtual void Begin()
		{
			RenderContextImpl::Begin();
			glEnable(GL_DEPTH_TEST);
			CHECK_GL_ERROR(L"Unable to enable depth test");
			glDepthFunc(GL_LESS);
			CHECK_GL_ERROR(L"Unable to set less depth function");
			glDepthMask(GL_TRUE);
			CHECK_GL_ERROR(L"Unable to enable depth mask");
			glEnable(GL_BLEND);
			CHECK_GL_ERROR(L"Unable to enable blend");
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			CHECK_GL_ERROR(L"Unable to set blend func");
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			CHECK_GL_ERROR(L"Unable to set polygon mode");
			glEnable(GL_CULL_FACE);
			CHECK_GL_ERROR(L"Unable to enable cull facing");
			glCullFace(GL_BACK);
			CHECK_GL_ERROR(L"Unable to set cull face mode");
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

		void SetMeshMatrix(const Math::Matrix4x4<float>& m)
		{
			m_mesh_matrix = m;
			m_mesh_matrix_inversed = m.Inversed();
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

		void SetBoneMatrix(int index, const Math::Matrix4x4<float>& m)
		{
			m_bone[index] = m;
		}
	};

	RenderContextSkinning::RenderContextSkinning()
		: RenderContext()		
	{
		impl_rc.reset(new RenderContextSkinningImpl());

		std::auto_ptr<Shader> vertex(new VertexShaderSkinning());
		std::auto_ptr<Shader> fragment(new FragmentVertexSkinning());
		SetVertexShader(vertex.release());
		SetFragmentShader(fragment.release());
		impl_rc->m_vertex_attributes = VERTEX_POSITION|VERTEX_TEXTURE_0|VERTEX_NORMAL|VERTEX_TANGENT|VERTEX_BITANGENT|VERTEX_BONE;
	}

	RenderContextSkinning::RenderContextSkinning(const RenderContextSkinning& rc)
		: RenderContext(rc)
	{}

	RenderContextSkinning& RenderContextSkinning::operator= (const RenderContextSkinning& rc)
	{
		RenderContext::operator = (rc);
		return *this;
	}

	void RenderContextSkinning::SetDiffuseColor(const Math::Vector4<float>& c)
	{
		static_cast<RenderContextSkinningImpl*>(impl_rc.get())->SetDiffuseColor(c);
	}

	void RenderContextSkinning::SetProjectionMatrix(const Math::Matrix4x4<float>& m)
	{
		static_cast<RenderContextSkinningImpl*>(impl_rc.get())->SetProjectionMatrix(m);
	}

	void RenderContextSkinning::SetMeshMatrix(const Math::Matrix4x4<float>& m)
	{
		static_cast<RenderContextSkinningImpl*>(impl_rc.get())->SetMeshMatrix(m);
	}

	void RenderContextSkinning::SetViewMatrix(const Math::Matrix4x4<float>& m)
	{
		static_cast<RenderContextSkinningImpl*>(impl_rc.get())->SetViewMatrix(m);
	}

	void RenderContextSkinning::SetWorldMatrix(const Math::Matrix4x4<float>& m)
	{
		static_cast<RenderContextSkinningImpl*>(impl_rc.get())->SetWorldMatrix(m);
	}

	void RenderContextSkinning::SetAmbientColor(const Math::Vector4<float>& v)
	{
		static_cast<RenderContextSkinningImpl*>(impl_rc.get())->SetAmbientColor(v);
	}

	void RenderContextSkinning::SetSpecularColor(const Math::Vector4<float>& v)
	{
		static_cast<RenderContextSkinningImpl*>(impl_rc.get())->SetSpecularColor(v);
	}

	void RenderContextSkinning::SetSpecularPower(float v)
	{
		static_cast<RenderContextSkinningImpl*>(impl_rc.get())->SetSpecularPower(v);
	}
	
	void RenderContextSkinning::SetLightPosition(const Math::Vector3<float>& pos)
	{
		static_cast<RenderContextSkinningImpl*>(impl_rc.get())->SetLightPosition(pos);
	};

	void RenderContextSkinning::SetBoneMatrix(int index, const Math::Matrix4x4<float>& pos)
	{
		static_cast<RenderContextSkinningImpl*>(impl_rc.get())->SetBoneMatrix(index, pos);
	};
}