#ifndef _H_PUNK_SHADER_2
#define _H_PUNK_SHADER_2

#include <memory>
#include "../config.h"
#include "shader.h"

namespace OpenGL
{
	template<class T>
	struct ShaderConfig
	{
		static const System::string GetVertexShaderFile() { return L""; }
		static const System::string GetFragmentShaderFile() { return L""; }
		static const System::string GetGeometryShaderFile() { return L""; }
		static void Bind(GLuint m_program);
	};

	template<template<class U> class Config>
	class RenderContext2
	{
		std::auto_ptr<Shader*> m_vertex_shader;
		std::auto_ptr<Shader*> m_fragment_shader;
		std::auto_ptr<Shader*> m_geometry_shader;
		GLuint m_program;
	public:


	};
}

#endif