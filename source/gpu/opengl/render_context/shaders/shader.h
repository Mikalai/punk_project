#ifndef _H_PUNK_OPENGL_DRIVER_SHADER
#define _H_PUNK_OPENGL_DRIVER_SHADER

#include <memory>

namespace System
{
	class string;
}

namespace GPU
{
	namespace OpenGL
	{

		struct ShaderImpl;

		class Shader
		{
		public:
			enum ShaderType { SHADER_BAD, SHADER_VERTEX, SHADER_FRAGMENT, SHADER_GEOMETRY };
		protected:	
			std::auto_ptr<ShaderImpl> impl_shader;
		public:
			explicit Shader(ShaderType type);
			Shader(const Shader& shader);
			Shader& operator = (const Shader& shader);
			~Shader();

			void CookFromFile(const System::string& filename);
			void CookFromString(const char* filename, unsigned length);

			unsigned GetIndex() const;
		};

		struct NoShader {};
	}
}

#endif