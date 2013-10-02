#ifndef _H_PUNK_OPENGL_DRIVER_SHADER
#define _H_PUNK_OPENGL_DRIVER_SHADER

#include <memory>
#include "../../gl/module.h"
#include "../../error/module.h"
#include "gl_shader_type.h"
#include "../../../common/vertex_component.h"
#include "../../../common/config.h"

namespace System
{
	class string;
}

namespace Gpu
{
	class CoreState;

	namespace OpenGL
	{
		class DynamicRenderContext;

		class Shader
		{			
		public:
			explicit Shader(ShaderType type);			
			~Shader();

			void CookFromFile(const System::string& filename);
            void CookFromFileWithHeaders(const System::string& filename, int count, const char** names);
			void CookFromString(const char* filename, unsigned length);
            void CookFromStringWithHeaders(const char* data, unsigned length, int count, const char** names);

			unsigned GetIndex() const;

			void Connect(DynamicRenderContext* rc);
			virtual void InitUniforms() {}
            virtual void BindParameters(const CoreState&) {}
			virtual int64_t GetRequiredAttributesSet() const { return 0; }            

        protected:
			DynamicRenderContext* m_rc;
			GLuint m_shader_index;
			GLenum m_type;

			Shader(const Shader& shader) = delete;
			Shader& operator = (const Shader& shader) = delete;
		};

		struct NoShader {};
	}
}

#endif
