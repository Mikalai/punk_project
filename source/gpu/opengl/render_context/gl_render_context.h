#ifndef _H_PUNK_OPENGL_DUMMY_RENDER_CONTEXT
#define _H_PUNK_OPENGL_DUMMY_RENDER_CONTEXT

#include "../../common/abstract_render_context_policy.h"
#include "shaders/shader_type.h"

namespace GPU
{
	namespace OpenGL
	{
        class Shader;

        class OpenGLRenderContext : public AbstractRenderPolicy
		{
		public:
            OpenGLRenderContext(ShaderCollection VS, ShaderCollection FS, ShaderCollection GS);
			virtual void Begin() override;
			virtual void End() override;
			virtual void Init() override;
			virtual ~OpenGLRenderContext();

		protected:
			bool SetUniformVector4f(const char * name, const float* value);
			bool SetUniformVector4f( int loc, const float* value );
			bool SetUniformVector3f(const char * name, const float* value );
			bool SetUniformVector3f(int loc, const float* value);
			bool SetUniformVector2f(const char * name, const float* value );
			bool SetUniformVector2f(int loc, const float* value );
			bool SetUniformFloat(const char * name, float value);
			bool SetUniformFloat(int loc, float value);
			bool SetUniformInt(const char * name, int value);
			bool SetUniformInt(int loc, int value);
			bool SetUniformMatrix2f(const char * name, const float* value);
			bool SetUniformMatrix2f( int loc, const float* value);
			bool SetUniformMatrix3f(const char * name, const float* value);
			bool SetUniformMatrix3f( int loc, const float* value);
			bool SetUniformMatrix4f(const char * name, const float* value);
			bool SetUniformMatrix4f( int loc, const float* value);
			bool SetUniformArrayMatrix4f(int loc, int count, const float* value);
			int  GetUniformLocation(const char * name);
			void GetUniformVector(const char * name, float* out);
			bool SetTexture(const char * name, int texUnit);
			bool SetTexture(int loc, int texUnit);
			bool BindAttributeTo(int loc, const char * name);
			bool SetAttribute(const char * name, const float* value);
			bool SetAttribute(int index, const float* value);
			int IndexForAttrName(const char * name);
			void GetAttribute(const char * name, float* out);
			void GetAttribute(int index, float* out);			
			void SetUpOpenGL(const CoreState& state);

		protected:
            std::unique_ptr<Shader> m_vertex_shader;
            std::unique_ptr<Shader> m_fragment_shader;
            std::unique_ptr<Shader> m_geometry_shader;

			unsigned m_program;
		};

        template<ShaderCollection VS, ShaderCollection FS, ShaderCollection GS> class RenderContextPolicy;
	}
}

#endif	//	_H_PUNK_OPENGL_DUMMY_RENDER_CONTEXT
