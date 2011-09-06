#include "shader_manager.h"
#include "../common/logger.h"
#include "../driver/video/opengl/glsl_program.h"
#include <algorithm>
#include <string>
namespace Shaders
{
	ShaderManager g_ShaderManager;

	ShaderManager::ShaderManager()
	{		
	}

	ShaderManager::~ShaderManager()
	{
		Common::Logger::GetLogger()->WriteDebugMessage(L"Delete shader manager" + LOG_LOCATION_STRING);
		for (std::map<System::string, ShaderProgram*>::iterator it = programs.begin(); it != programs.end(); it++)
		{
			delete it->second;
		}
		programs.clear();
	}

	ShaderProgram* ShaderManager::GetProgram(const System::string& name)
	{
		return programs[name];
	}

	void ShaderManager::LoadIniFile(const System::string& iniFileName)
	{
		Common::Logger::GetLogger()->WriteMessage(System::string::Format(L"Shader manager ini file is %s", System::string(iniFileName).Data()));

		System::Buffer buffer;
		System::BinaryFile::Load(iniFileName, buffer);

		while (!buffer.IsEnd())
		{
			System::string name = buffer.ReadWord();
			System::string vert = buffer.ReadWord();
			System::string frag = buffer.ReadWord();
			LoadShaderProgram(name, vert, frag);
		}
	}

	void ShaderManager::LoadShaderProgram(const System::string& name, const System::string& vFilename, const System::string& fFilename)
	{	
		Common::Logger::GetLogger()->WriteMessage(System::string::Format(L"Shader manager loads program %s: vert: %s frag: %s", name.Data(), vFilename.Data(), fFilename.Data()));
		ShaderProgram* p = programs[name];
		if (!p)
		{
			ShaderProgram* p = new Driver::GLSLProgram();
			p->CreateFromFile(vFilename, fFilename);
			programs[name] = p;
		}
	}
}