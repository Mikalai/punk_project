//#include "rc_particle_system.h"
//#include "fs_particle.h"
//#include "vs_particle.h"
//
//#include "render_context_impl.h"
//#include "../../../../../math/mat4.h"
//#include "../../../../../math/mat3.h"
//#include "../../../../../math/vec4.h"
//#include "../../../../../math/vec3.h"
//
//namespace OpenGL
//{
//	struct RenderContextParticleSystemImpl : public RenderContextImpl
//	{
//		static const int MAX_BONES = 64;
//
//		GLuint m_proj_uniform;
//		GLuint m_view_uniform;
//		GLuint m_world_uniform;
//		GLuint m_diffuse_map_uniform;		
//		GLuint m_use_gravity_uniform;
//		GLuint m_time_uniform;
//		GLuint m_proj_view_world_uniform;
//		
//
//		Math::mat4 m_view;
//		Math::mat4 m_proj;
//		Math::mat4 m_world;
//		int m_use_gravity;
//		float m_time;
//		
//		virtual void InitAttributes()
//		{
//
//		}
//
//		virtual void InitUniforms()
//		{
//			m_proj_view_world_uniform = glGetUniformLocation(m_program, "uProjViewWorld");
//			CHECK_GL_ERROR(L"Unable to get uniform location");
//			m_world_uniform = glGetUniformLocation(m_program, "uWorld");
//			CHECK_GL_ERROR(L"Unable to get uniform location");
//			m_proj_uniform = glGetUniformLocation(m_program, "uProj");
//			CHECK_GL_ERROR(L"Unable to get uniform location");
//			m_view_uniform = glGetUniformLocation(m_program, "uView");			
//			CHECK_GL_ERROR(L"Unable to get uniform location");
//			m_use_gravity_uniform = glGetUniformLocation(m_program, "uUseGravity");			
//			CHECK_GL_ERROR(L"Unable to get uniform location");
//			m_time_uniform = glGetUniformLocation(m_program, "uTime");			
//			CHECK_GL_ERROR(L"Unable to get uniform location");;
//		}
//
//		virtual void BindUniforms()
//		{
//			Math::mat4 m = m_proj * m_view * m_world;
//			SetUniformMatrix4f(m_proj_view_world_uniform, &m[0]);
//			SetUniformMatrix4f(m_proj_uniform, &m_proj[0]);
//			SetUniformMatrix4f(m_view_uniform, &m_view[0]);
//			SetUniformMatrix4f(m_world_uniform, &m_world[0]);
//			SetUniformInt(m_diffuse_map_uniform, 0);
//			SetUniformInt(m_use_gravity_uniform, m_use_gravity);
//			SetUniformFloat(m_time_uniform, m_time);
//
//			glEnable(GL_DEPTH_TEST);				
//			glEnable(GL_BLEND);
//			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_DST_ALPHA);
//		}
//
//		RenderContextParticleSystemImpl()
//			: RenderContextImpl()
//			, m_proj_view_world_uniform()
//			, m_proj_uniform()
//			, m_view_uniform()
//			, m_world_uniform()				
//			, m_diffuse_map_uniform()
//			, m_world()
//			, m_view()
//			, m_proj()
//			, m_time()
//			, m_time_uniform()
//			, m_use_gravity()
//			, m_use_gravity_uniform()
//		{}
//
//		RenderContextParticleSystemImpl::RenderContextParticleSystemImpl(const RenderContextParticleSystemImpl& impl)
//			: RenderContextImpl(impl)
//			, m_proj_view_world_uniform(impl.m_proj_view_world_uniform)
//			, m_proj_uniform(impl.m_proj_uniform)
//			, m_view_uniform(impl.m_view_uniform)
//			, m_world_uniform(impl.m_world_uniform)
//			, m_use_gravity_uniform(impl.m_use_gravity_uniform)
//			, m_use_gravity(impl.m_use_gravity)
//			, m_time(impl.m_time)
//			, m_time_uniform(impl.m_time_uniform)
//			, m_diffuse_map_uniform(impl.m_diffuse_map_uniform)
//			, m_world(impl.m_world)
//			, m_view(impl.m_view)
//			, m_proj(impl.m_proj)
//		{}
//
//		virtual void Begin()
//		{
//			RenderContextImpl::Begin();
//			glEnable(GL_DEPTH_TEST);
//			glDepthFunc(GL_LESS);
//			glDepthMask(GL_TRUE);
//			glEnable(GL_BLEND);
//			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//			glPointSize(5);
//			glPointParameteri(GL_POINT_SPRITE_COORD_ORIGIN, GL_LOWER_LEFT);
//		}
//
//		virtual void End()
//		{
//			RenderContextImpl::End();
//			glEnable(GL_DEPTH_TEST);			
//			glDepthFunc(GL_LESS);
//			glDepthMask(GL_TRUE);
//			glEnable(GL_BLEND);
//			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//		}
//
//		void SetViewMatrix(const Math::Matrix4x4<float>& m)
//		{
//			m_view = m;
//		}
//
//		void SetWorldMatrix(const Math::Matrix4x4<float>& m)
//		{
//			m_world = m;			
//		}
//
//		void SetProjectionMatrix(const Math::Matrix4x4<float>& m)
//		{
//			m_proj = m;
//		}
//
//		void SetTime(float time)
//		{
//			m_time = time;
//		}
//
//		void UseGravity(int use)
//		{
//			m_use_gravity = use;
//		}
//	};
//
//	RenderContextParticle::RenderContextParticle()
//		: RenderContext()		
//	{
//		impl_rc.reset(new RenderContextParticleSystemImpl());
//
//		std::auto_ptr<Shader> vertex(new VertexShaderParticle());
//		std::auto_ptr<Shader> fragment(new FragmentShaderParticle());
//		SetVertexShader(vertex.release());
//		SetFragmentShader(fragment.release());
//		impl_rc->m_vertex_attributes = 
//			VERTEX_POSITION			//	position [X, Y, Z, START_TIME]
//			| VERTEX_NORMAL			//	velocity [VX, VY, VZ, LIFE_TIME]
//			| VERTEX_TEXTURE_0;		//	texture coordinates [U, V]
//	}
//
//	RenderContextParticle::RenderContextParticle(const RenderContextParticle& rc)
//		: RenderContext(rc)
//	{}
//
//	RenderContextParticle& RenderContextParticle::operator= (const RenderContextParticle& rc)
//	{
//		RenderContext::operator = (rc);
//		return *this;
//	}
//
//	void RenderContextParticle::SetProjectionMatrix(const Math::Matrix4x4<float>& m)
//	{
//		static_cast<RenderContextParticleSystemImpl*>(impl_rc.get())->SetProjectionMatrix(m);
//	}
//
//	void RenderContextParticle::SetViewMatrix(const Math::Matrix4x4<float>& m)
//	{
//		static_cast<RenderContextParticleSystemImpl*>(impl_rc.get())->SetViewMatrix(m);
//	}
//
//	void RenderContextParticle::SetWorldMatrix(const Math::Matrix4x4<float>& m)
//	{
//		static_cast<RenderContextParticleSystemImpl*>(impl_rc.get())->SetWorldMatrix(m);
//	}
//
//	void RenderContextParticle::SetTime(float time)
//	{
//		static_cast<RenderContextParticleSystemImpl*>(impl_rc.get())->SetTime(time);
//	}
//
//	void RenderContextParticle::UseGravity(bool v)
//	{
//		static_cast<RenderContextParticleSystemImpl*>(impl_rc.get())->UseGravity((int)v);
//	}
//}