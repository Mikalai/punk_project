#ifndef _H_SHADER_MANAGER
#define _H_SHADER_MANAGER

#include "../system/system.h"
#include "../driver/video/opengl/shader_program.h"
#include <map>

namespace Shaders
{
	class ShaderManager
	{
		std::map<System::string, ShaderProgram*> programs;
	public:
		ShaderManager();
		~ShaderManager();
		void LoadIniFile(const System::string& iniFilename);
		void LoadShaderProgram(const System::string& name, const System::string& vertexFilename, const System::string& fragmentFilename);
		ShaderProgram* GetProgram(const System::string& name);
	};
	extern ShaderManager g_ShaderManager;
}


#endif