#ifndef _H_PUNK_OPENGL_DUMMY_RENDER_CONTEXT
#define _H_PUNK_OPENGL_DUMMY_RENDER_CONTEXT

#include "../../common/abstract_render_context_policy.h"
#include "shaders/shader_type.h"
#include "../../../math/vec4.h"
#include "../../../math/mat4.h"

namespace GPU
{
	namespace OpenGL
	{
        class Shader;

        class OpenGLRenderContext : public AbstractRenderPolicy
		{
		public:
			OpenGLRenderContext();
            OpenGLRenderContext(ShaderCollection VS, ShaderCollection FS, ShaderCollection GS);
			virtual void Begin() override;
			virtual void End() override;
			virtual void Init() override;
			virtual ~OpenGLRenderContext();

			bool SetUniformVector4f(const char * name, const float* value);
            bool SetUniformVector4f(const char * name, const Math::vec4& value);
            bool SetUniformVector4f( int index, const float* value );
            bool SetUniformVector4f( int index, const Math::vec4& value );
			bool SetUniformVector3f(const char * name, const float* value );
            bool SetUniformVector3f(const char * name, const Math::vec3& value);
			bool SetUniformVector3f(int index, const float* value);
            bool SetUniformVector3f(int index, const Math::vec3& value);
			bool SetUniformVector2f(const char * name, const float* value );
            bool SetUniformVector2f(const char * name, const Math::vec2& value );
			bool SetUniformVector2f(int index, const float* value );
            bool SetUniformVector2f(int index, const Math::vec2& value );
			bool SetUniformFloat(const char * name, float value);
			bool SetUniformFloat(int index, float value);
			bool SetUniformInt(const char * name, int value);
			bool SetUniformInt(int index, int value);
			bool SetUniformMatrix2f(const char * name, const float* value);
            bool SetUniformMatrix2f(const char * name, const Math::mat2& value);
			bool SetUniformMatrix2f( int index, const float* value);
            bool SetUniformMatrix2f( int index, const Math::mat2& value);
			bool SetUniformMatrix3f(const char * name, const float* value);
            bool SetUniformMatrix3f(const char * name, const Math::mat3& value);
            bool SetUniformMatrix3f( int index, const float* value);
            bool SetUniformMatrix3f( int index, const Math::mat3& value);
			bool SetUniformMatrix4f(const char * name, const float* value);
            bool SetUniformMatrix4f(const char * name, const Math::mat4& value);
			bool SetUniformMatrix4f( int index, const float* value);
            bool SetUniformMatrix4f( int index, const Math::mat4& value);
			bool SetUniformArrayMatrix4f(int index, int count, const float* value);
            bool SetUniformArrayMatrix4f(int index, int count, const Math::mat4* value);
			int  GetUniformLocation(const char * name);
			void GetUniformVector(const char * name, float* out);
			bool SetTexture(const char * name, int texUnit);
			bool SetTexture(int index, int texUnit);
			bool BindAttributeTo(int index, const char * name);
			bool SetAttribute(const char * name, const float* value);
			bool SetAttribute(int index, const float* value);
			int IndexForAttrName(const char * name);
			void GetAttribute(const char * name, float* out);
			void GetAttribute(int index, float* out);			
			void SetUpOpenGL(const CoreState& state);

		protected:
			Shader* m_vertex_shader;
			Shader* m_fragment_shader;
			Shader* m_geometry_shader;

			unsigned m_program;
		};

        template<ShaderCollection VS, ShaderCollection FS, ShaderCollection GS> class RenderContextPolicy;
	}
}

#endif	//	_H_PUNK_OPENGL_DUMMY_RENDER_CONTEXT
