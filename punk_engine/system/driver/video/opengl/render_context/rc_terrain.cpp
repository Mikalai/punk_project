#include "rc_terrain.h"
#include "fs_terrain.h"
#include "vs_terrain.h"

#include "render_context_impl.h"
#include "../../../../../math/mat4.h"
#include "../../../../../math/mat3.h"
#include "../../../../../math/vec4.h"

namespace OpenGL
{
	struct RenderContextTerrainImpl : public RenderContextImpl
	{
		GLuint m_proj_view_world_uniform;
		GLuint m_diffuse_color_uniform;
		GLuint m_diffuse_map_1_uniform;		
		GLuint m_diffuse_map_2_uniform;		
		GLint m_normal_transform_uniform;
		GLint m_view_uniform;
		GLint m_world_uniform;
		GLint m_projection_uniform;
		GLint m_light_direction_uniform;
		GLint m_light_position_uniform;
		GLint m_height_map_uniform;
		GLint m_normal_map_uniform;		
		GLint m_position_uniform;
		GLint m_level_uniform;
		GLint m_i_uniform;
		GLint m_j_uniform;	
		GLint m_vert_scale_uniform;
		Math::mat4 m_world;
		Math::mat4 m_view;
		Math::mat4 m_proj;
		Math::mat4 m_proj_view_world;
		Math::mat3 m_normal_tranform;
		Math::vec4 m_diffuse_color;
		Math::vec2 m_position;
		Math::vec3 m_light_position;
		Math::vec3 m_light_direction;
		float m_vert_scale;

		float m_level;
		unsigned m_i, m_j;

		virtual void InitAttributes()
		{

		}

		virtual void Begin()
		{
			RenderContextImpl::Begin();
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LESS);
			glDepthMask(GL_TRUE);			
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glDisable(GL_CULL_FACE);
		}

		virtual void End()
		{
			RenderContextImpl::End();
		}


		virtual void InitUniforms()
		{
			m_proj_view_world_uniform = GetUniformLocation("uProjViewWorld");
			m_normal_map_uniform = GetUniformLocation("uNormalTransform");
			m_light_direction_uniform = GetUniformLocation("uLightDirection");
			m_diffuse_color_uniform = GetUniformLocation("uDiffuseColor");
			m_view_uniform = GetUniformLocation("uView");
			m_world_uniform = GetUniformLocation("uWorld");
			m_projection_uniform = GetUniformLocation("uProjection");
			m_height_map_uniform = GetUniformLocation("uHeightMapUniform");
			m_normal_map_uniform = GetUniformLocation("uNormalMapUniform");
			m_diffuse_map_1_uniform = GetUniformLocation("uDiffuseMapUniform1");
			m_diffuse_map_2_uniform = GetUniformLocation("uDiffuseMapUniform2");
			m_position_uniform = GetUniformLocation("uPosition");
			m_level_uniform = GetUniformLocation("uLevel");
			m_i_uniform = GetUniformLocation("ui");
			m_j_uniform = GetUniformLocation("uj");
			m_vert_scale_uniform = GetUniformLocation("uVertScale");

		}

		virtual void BindUniforms()
		{
			m_proj_view_world = m_proj * m_view* m_world;
			SetUniformMatrix4f(m_proj_view_world_uniform, &m_proj_view_world[0]);
			SetUniformMatrix4f(m_world_uniform, &m_world[0]);
			SetUniformMatrix4f(m_view_uniform, &m_view[0]);
			SetUniformMatrix4f(m_projection_uniform, &m_proj[0]);
			//	SetUniformMatrix3f(m_normal_transform_uniform, m_normal_tranform);
			SetUniformVector3f(m_light_direction_uniform, m_light_direction);
			SetUniformVector4f(m_diffuse_color_uniform, Math::vec4(1,1,1,1));
			SetUniformVector2f(m_position_uniform, m_position);
			SetUniformInt(m_height_map_uniform, 2);
			SetUniformInt(m_diffuse_map_1_uniform, 0);
			SetUniformInt(m_diffuse_map_2_uniform, 1);
			SetUniformFloat(m_level_uniform, float(m_level));
			SetUniformInt(m_i_uniform, m_i);
			SetUniformInt(m_j_uniform, m_j);
			SetUniformFloat(m_vert_scale_uniform, m_vert_scale);
			//			SetUniformVector3f(m_light_direction_uniform, Math::mat4::CreateRotation(1,0,0, 0) * Math::vec3(1, 0, 0).ToHomogeneous());
		}

		RenderContextTerrainImpl()
			: RenderContextImpl()
			, m_proj_view_world_uniform()
			, m_diffuse_color_uniform()
			, m_diffuse_map_1_uniform()		
			, m_diffuse_map_2_uniform()		
			, m_normal_transform_uniform()
			, m_view_uniform()
			, m_world_uniform()
			, m_projection_uniform()
			, m_light_direction_uniform()
			, m_light_position_uniform()
			, m_height_map_uniform()
			, m_normal_map_uniform()		
			, m_position_uniform()
			, m_level_uniform()
			, m_i_uniform()
			, m_j_uniform()												
			, m_world()
			, m_view()
			, m_proj()
			, m_proj_view_world()
			, m_normal_tranform()
			, m_diffuse_color()
			, m_position()
			, m_level()
			, m_i()
			, m_j()
		{}

		RenderContextTerrainImpl::RenderContextTerrainImpl(const RenderContextTerrainImpl& impl)
			: RenderContextImpl(impl)
			, m_proj_view_world_uniform(impl.m_projection_uniform)
			, m_diffuse_color_uniform(impl.m_diffuse_color_uniform)
			, m_diffuse_map_1_uniform(impl.m_diffuse_map_1_uniform)		
			, m_diffuse_map_2_uniform(impl.m_diffuse_map_2_uniform)		
			, m_normal_transform_uniform(impl.m_normal_transform_uniform)
			, m_view_uniform(impl.m_view_uniform)
			, m_world_uniform(impl.m_world_uniform)
			, m_projection_uniform(impl.m_projection_uniform)
			, m_light_direction_uniform(impl.m_light_direction_uniform)
			, m_light_position_uniform(impl.m_light_position_uniform)
			, m_height_map_uniform(impl.m_height_map_uniform)
			, m_normal_map_uniform(impl.m_normal_map_uniform)		
			, m_position_uniform(impl.m_position_uniform)
			, m_level_uniform(impl.m_level_uniform)
			, m_i_uniform(impl.m_i_uniform)
			, m_j_uniform(impl.m_j_uniform)													
			, m_world(impl.m_world)
			, m_view(impl.m_view)
			, m_proj(impl.m_proj)
			, m_proj_view_world(impl.m_proj_view_world)
			, m_normal_tranform(impl.m_normal_tranform)
			, m_diffuse_color(impl.m_diffuse_color)
			, m_position(impl.m_position)
			, m_level(impl.m_level)
			, m_i(impl.m_i)
			, m_j(impl.m_j)
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

		void SetNormalTransform(const Math::Matrix3x3<float>& m)
		{
			m_normal_tranform = m;
		}

		void SetLightDirection(const Math::vec3& d)
		{
			m_light_direction = d;
		}

		void SetPosition(const Math::vec2& pos)
		{
			m_position = pos;
		}

		void SetLevel(float level)
		{
			m_level = level;
		}

		void SetI(int i)
		{
			m_i = i;
		}

		void SetJ(int j)
		{
			m_j = j;
		}

		void SetVerticalScale(float value)
		{
			m_vert_scale = value;
		}
	};

	RenderContextTerrain::RenderContextTerrain()
		: RenderContext()		
	{
		impl_rc.reset(new RenderContextTerrainImpl());

		std::auto_ptr<Shader> vertex(new ShaderTerrainVertex());
		std::auto_ptr<Shader> fragment(new ShaderTerrainFragment());
		SetVertexShader(vertex.release());
		SetFragmentShader(fragment.release());
		impl_rc->m_vertex_attributes = VERTEX_POSITION|VERTEX_TEXTURE_0|VERTEX_FLAGS|VERTEX_NORMAL;
	}

	RenderContextTerrain::RenderContextTerrain(const RenderContextTerrain& rc)
		: RenderContext(rc)
	{}

	RenderContextTerrain& RenderContextTerrain::operator= (const RenderContextTerrain& rc)
	{
		RenderContext::operator = (rc);
		return *this;
	}

	void RenderContextTerrain::SetDiffuseColor(const Math::Vector4<float>& c)
	{
		static_cast<RenderContextTerrainImpl*>(impl_rc.get())->SetDiffuseColor(c);
	}

	void RenderContextTerrain::SetProjectionMatrix(const Math::Matrix4x4<float>& m)
	{
		static_cast<RenderContextTerrainImpl*>(impl_rc.get())->SetProjectionMatrix(m);
	}

	void RenderContextTerrain::SetNormalTransform(const Math::Matrix3x3<float>& m)
	{
		static_cast<RenderContextTerrainImpl*>(impl_rc.get())->SetNormalTransform(m);
	}

	void RenderContextTerrain::SetPosition(const Math::Vector2<float>& v)
	{
		static_cast<RenderContextTerrainImpl*>(impl_rc.get())->SetPosition(v);
	}

	void RenderContextTerrain::SetViewMatrix(const Math::Matrix4x4<float>& m)
	{
		static_cast<RenderContextTerrainImpl*>(impl_rc.get())->SetViewMatrix(m);
	}

	void RenderContextTerrain::SetWorldMatrix(const Math::Matrix4x4<float>& m)
	{
		static_cast<RenderContextTerrainImpl*>(impl_rc.get())->SetWorldMatrix(m);
	}

	void RenderContextTerrain::SetLevel(float level)
	{
		static_cast<RenderContextTerrainImpl*>(impl_rc.get())->SetLevel(level);
	}

	void RenderContextTerrain::SetI(int i)
	{
		static_cast<RenderContextTerrainImpl*>(impl_rc.get())->SetI(i);
	}

	void RenderContextTerrain::SetJ(int j)
	{
		static_cast<RenderContextTerrainImpl*>(impl_rc.get())->SetJ(j);
	}

	void RenderContextTerrain::SetLightDirection(const Math::Vector3<float>& d)
	{
		static_cast<RenderContextTerrainImpl*>(impl_rc.get())->SetLightDirection(d);
	}

	void RenderContextTerrain::SetVerticalScale(float value)
	{
		static_cast<RenderContextTerrainImpl*>(impl_rc.get())->SetVerticalScale(value);
	}
}