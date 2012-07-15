//
// Class to encapsulate GLSL m_program and shader objects and working with them
//
// Author: Alex V. Boreskoff <alexboreskoff@mtu-net.ru>, <steps3d@narod.ru>
//

#include "../../../system.h"
#include "glsl_program.h"
#include "driver.h"

namespace OpenGL
{
	static const char* UniformStrings[] = 
	{
		"uWorl",
		"uView", 
		"uProj", 
		"uProjViewWorld",
		"uDiffuseColor",
		"uRadius",
		"uDiffuseMap"
	};

	/*	namespace Shaders
	{
	GLSLProgram g_TextureBumpProgram;
	GLSLProgram g_ShowNormalProgram;
	GLSLProgram g_ShowTangentProgram;
	GLSLProgram g_ShowBinormalProgram;
	}
	/**/

	void GLSLProgram::BindUniform()
	{
		for (int i = 0; i < sizeof(UniformStrings)/sizeof(char*); i++)
		{
			m_uniform_location[i] = GetUniformLocation(UniformStrings[i]);
		}
	}

	void GLSLProgram::Init()
	{                
		/*	if (::Driver::Video::GetDriver()->ShaderVersion >= 300)
		{                    
		/*                    Shaders::g_TextureBumpProgram.CreateFromRFX("data/shaders/StandardShaders.rfx", "Effects", "TexturedBump");
		Shaders::g_ShowNormalProgram.CreateFromString(Shaders::ShowNormal::vertex, ShowNormal::fragment);
		Shaders::g_ShowBinormalProgram.CreateFromString(ShowBinormal::vertex, ShowBinormal::fragment);
		Shaders::g_ShowTangentProgram.CreateFromString(ShowTangent::vertex, ShowTangent::fragment);*/
		/*	}
		if (::Driver::Video::GetDriver()->ShaderVersion == 120)
		{
		//g_TextureBumpProgram.CreateFromFile("data/shaders/BumpVertexShader_120", "data/shaders/BumpFragmentShader_120");
		}/**/
	}

	int GLSLProgram::GetPassCount() const
	{
		return m_numPasses;
	}

	GLSLProgram::GLSLProgram()
	{
		m_pass = 0;
		m_ok = false;
		m_currentPass = 0;				
	}

	GLSLProgram::~GLSLProgram()
	{
		Clear();
	}


	void GLSLProgram::AllocatePass()
	{
		if (m_numPasses == 0)
		{
			m_numPasses++;
			m_pass = new Pass[m_numPasses];
		}
		else
		{
			Pass* old = new Pass[m_numPasses];
			memcpy(old, m_pass, sizeof(Pass)*m_numPasses);
			delete[] m_pass;
			m_pass = new Pass[m_numPasses+1];
			memcpy(m_pass, old, sizeof(Pass)*m_numPasses);
			delete[] old;
			m_numPasses++;
		}
	}

	void GLSLProgram::CreateFromRFX(const System::string& filename, const System::string& effectGroup, const System::string& effectName)
	{
		/*    FILE* f = 0;
		f = fopen(filename, "rb");
		fseek(f, 0, SEEK_END);
		int size = ftell(f);
		fseek(f, 0, SEEK_SET);
		char* data = new char[size];
		fread(data, sizeof(char), size, f);
		char* shaders = strstr(data, "<RENDER_MONKEY>");
		TiXmlDocument doc("doucment");
		doc.Parse(shaders);
		TiXmlElement* RenderMonkeyNode = doc.FirstChildElement();
		while (RenderMonkeyNode)
		{
		if (RenderMonkeyNode->ValueTStr() == "RENDER_MONKEY")
		{
		TiXmlElement* EffectWorkspaceNode = RenderMonkeyNode->FirstChildElement();
		while (EffectWorkspaceNode)
		{
		if (EffectWorkspaceNode->ValueTStr() == "RmEffectWorkspace")
		{
		TiXmlElement* EffectGroupNode = EffectWorkspaceNode->FirstChildElement();
		while(EffectGroupNode)
		{
		if (EffectGroupNode->ValueTStr() == "RmEffectGroup")
		{
		TiXmlAttribute* EffectGroupAttribute = EffectGroupNode->FirstAttribute();
		while (EffectGroupAttribute)
		{
		if (strcmp(EffectGroupAttribute->Name(), "NAME") == 0 && strcmp(EffectGroupAttribute->Value(), effectGroup) == 0)
		{
		TiXmlElement* OpenGLEffectNode = EffectGroupNode->FirstChildElement();
		while (OpenGLEffectNode)
		{
		TiXmlAttribute* OpenGLEffectAttribute = OpenGLEffectNode->FirstAttribute();
		while (OpenGLEffectAttribute)
		{
		if (OpenGLEffectAttribute->NameTStr() == "NAME" && strcmp(OpenGLEffectAttribute->Value(), effectName) == 0)
		{
		TiXmlElement* PassNode = OpenGLEffectNode->FirstChildElement();
		while (PassNode)
		{
		GLSLProgram::RenderState state;
		if (PassNode->ValueTStr() == "RmGLPass")
		{
		const char* vertexShader = 0;
		const char* fragmentShader = 0;
		TiXmlElement* GLShaderNode = PassNode->FirstChildElement();
		while (GLShaderNode)
		{
		if (GLShaderNode->ValueTStr() == "RmRenderStateBlock")
		{
		TiXmlElement* RenderStateNode = GLShaderNode->FirstChildElement();
		while (RenderStateNode)
		{
		TiXmlAttribute* GLStateAttr = RenderStateNode->FirstAttribute();
		const char* name;
		int stateId;
		int stateValue;
		while (GLStateAttr)
		{
		if (GLStateAttr->NameTStr() == "NAME")
		{
		name = GLStateAttr->Value();
		}
		if (GLStateAttr->NameTStr() == "STATE")
		{
		stateId = GLStateAttr->IntValue();
		}
		if (GLStateAttr->NameTStr() == "VALUE")
		{
		stateValue = GLStateAttr->IntValue();
		}
		GLStateAttr = GLStateAttr->Next();
		}
		switch(stateId)
		{
		case 51:	//BlendDstAlpha
		state.blendDstAlpha = BlendTable[stateValue-1];
		break;
		case 50:	//BlendSrcAlpha
		state.blendSrcAlpha = BlendTable[stateValue-1];
		break;
		case 48:	//BlendSrcRgb
		state.blendSrcRGB = BlendTable[stateValue-1];
		break;
		case 46:	//BlendEnable;
		state.blend = stateValue;
		break;
		case 49:	//BlendDstRgb
		state.blendDstRGB = BlendTable[stateValue-1];
		break;
		case 52:	//BlendEquation
		state.blendEquationAlpha = state.blendEquationRgb = BlenFuncTable[stateValue-1];
		break;
		case 47:	//BlendColor
		state.blendColor[0] = float(stateValue&0xFF000000)/255.0f;
		state.blendColor[1] = float(stateValue&0x00FF0000)/255.0f;
		state.blendColor[2] = float(stateValue&0x0000FF00)/255.0f;
		state.blendColor[3] = float(stateValue&0x000000FF)/255.0f;
		break;
		}
		RenderStateNode = RenderStateNode->NextSiblingElement();
		}
		}
		if (GLShaderNode->ValueTStr() == "RmGLShader")
		{
		TiXmlAttribute* GLShaderAttr = GLShaderNode->FirstAttribute();
		while (GLShaderAttr)
		{
		if (GLShaderAttr->NameTStr() == "NAME" && strcmp(GLShaderAttr->Value(), "Vertex Program") == 0)
		{
		TiXmlElement* ShaderCodeNode = GLShaderNode->FirstChildElement();
		vertexShader = ShaderCodeNode->FirstChild()->Value();
		}
		if (GLShaderAttr->NameTStr() == "NAME" && strcmp(GLShaderAttr->Value(), "Fragment Program") == 0)
		{
		TiXmlElement* ShaderCodeNode = GLShaderNode->FirstChildElement();
		fragmentShader = ShaderCodeNode->FirstChild()->Value();
		}
		GLShaderAttr = GLShaderAttr->Next();
		}
		}
		GLShaderNode = GLShaderNode->NextSiblingElement();
		}
		AllocatePass();
		CreatePass(vertexShader, fragmentShader, m_pass[m_numPasses-1]);
		m_pass[m_numPasses-1].state = state;
		}
		PassNode = PassNode->NextSiblingElement();
		}
		}
		OpenGLEffectAttribute = OpenGLEffectAttribute->Next();
		}
		OpenGLEffectNode = OpenGLEffectNode->NextSiblingElement();
		}
		}
		EffectGroupAttribute = EffectGroupAttribute->Next();
		}
		}
		EffectGroupNode = EffectGroupNode->NextSiblingElement();
		}
		}
		EffectWorkspaceNode = EffectWorkspaceNode->NextSiblingElement();
		}
		}
		RenderMonkeyNode = RenderMonkeyNode->NextSiblingElement();
		}
		doc.Clear();*/
	}

	void GLSLProgram::CreatePass(const System::Buffer& vertexSrc, const System::Buffer& fragmentSrc, Pass& pass)
	{
		GLuint program = 0;
		GLuint vertexShader = 0;
		GLuint fragmentShader = 0;

		// check whether we should create m_program object
		if (program == 0 )
			program = glCreateProgram();

		// create a vertex shader object and a fragment shader object
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		if (!LoadShader(fragmentShader, fragmentSrc))
			throw System::SystemError(L"Can't create fragment shader" + LOG_LOCATION_STRING);


		printf("%s\n", vertexSrc);
		if (!LoadShader(vertexShader, vertexSrc))
			throw System::SystemError(L"Can't create vertex shader" + LOG_LOCATION_STRING);

		// attach shaders to m_program object
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);

		// link the m_program object and print out the info m_log
		glBindAttribLocation(m_pass[0].m_program, 0, "rm_Vertex");
		glBindAttribLocation(m_pass[0].m_program, 1, "rm_Normal");
		glBindAttribLocation(m_pass[0].m_program, 2, "rm_Texcoord0");
		glBindAttribLocation(m_pass[0].m_program, 3, "rm_Flags");

		glLinkProgram(program);
		pass.m_program = program;
		pass.m_fragmentShader = fragmentShader;
		pass.m_vertexShader = vertexShader;

		BindUniform();
	}

	void GLSLProgram::CreateFromFile(const System::string& vertexFileName, const System::string& fragmentFileName, const System::string& geometryFileName)
	{
		System::Buffer vertexShaderData;
		System::Buffer fragmentShaderData;
		System::Buffer geometryShaderData;
		System::BinaryFile::Load(vertexFileName, vertexShaderData);
		System::BinaryFile::Load(fragmentFileName, fragmentShaderData); 

		if (geometryFileName != L"null")
		{
			System::BinaryFile::Load(geometryFileName, geometryShaderData);
		}

		m_numPasses = 1;
		if (m_pass)
			delete[] m_pass;
		m_pass = new Pass[m_numPasses];

		// check whether we should create m_program object
		if (m_pass[0].m_program == 0 )
			m_pass[0].m_program = glCreateProgram();

		// create a vertex shader object and a fragment shader object
		m_pass[0].m_vertexShader = glCreateShader(GL_VERTEX_SHADER);
		m_pass[0].m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		System::Logger::Instance()->WriteMessage(L"Loading vertex shader " + vertexFileName);

		if (!LoadShader(m_pass[0].m_vertexShader, vertexShaderData))
			throw System::SystemError(L"Can't create vertex shader");

		System::Logger::Instance()->WriteMessage(L"Loading fragment shader " + fragmentFileName);

		if (!LoadShader(m_pass[0].m_fragmentShader, fragmentShaderData))
			throw System::SystemError(L"Can't create fragment shader" + LOG_LOCATION_STRING);

		if (geometryShaderData.GetSize() != 0)
		{
			m_pass[0].m_geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
			if (!LoadShader(m_pass[0].m_geometryShader, geometryShaderData))
				throw System::SystemError(L"Can't create geometry shader" + LOG_LOCATION_STRING);
			glAttachShader(m_pass[0].m_program, m_pass[0].m_geometryShader);
		}


		// attach shaders to m_program object
		glAttachShader(m_pass[0].m_program, m_pass[0].m_vertexShader);
		glAttachShader(m_pass[0].m_program, m_pass[0].m_fragmentShader);

		// link the m_program object and print out the info m_log
		/*			glBindAttribLocation(m_pass[0].m_program, 0, "rm_Vertex");
		glBindAttribLocation(m_pass[0].m_program, 1, "rm_Normal");
		glBindAttribLocation(m_pass[0].m_program, 2, "rm_Texcoord0");
		glBindAttribLocation(m_pass[0].m_program, 3, "rm_Flags");
		*/
		glLinkProgram(m_pass[0].m_program);

		BindUniform();
		//  if ( !checkGlError () )     // check for errors
		//      return false;
	}

	void GLSLProgram::CreateFromMemory(const System::Buffer& vertexBufferData, const System::Buffer& fragmentBufferData, const System::Buffer& geometryBufferData)
	{
		m_ok = false;
		m_numPasses = 1;
		if (m_pass != 0)
			delete[] m_pass;
		m_pass = new Pass[m_numPasses];

		// check whether we should create m_program object
		if (m_pass[0].m_program == 0 )
			m_pass[0].m_program = glCreateProgram();

		// create a vertex shader object and a fragment shader object
		m_pass[0].m_vertexShader = glCreateShader(GL_VERTEX_SHADER);
		m_pass[0].m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		System::Logger::Instance()->WriteMessage(L"Loading vertex shader\n");

		if (!LoadShader(m_pass[0].m_vertexShader, vertexBufferData))
			throw System::SystemError(L"Can't create vertex shader" + LOG_LOCATION_STRING);

		System::Logger::Instance()->WriteMessage(L"Loading fragment shader");

		if (!LoadShader(m_pass[0].m_fragmentShader, fragmentBufferData))
			throw System::SystemError(L"Can't create fragment shader" + LOG_LOCATION_STRING);

		if (geometryBufferData.GetSize() != 0)
		{
			m_pass[0].m_geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
			if (!LoadShader(m_pass[0].m_geometryShader, geometryBufferData))
				throw System::SystemError(L"Can't create geometry shader" + LOG_LOCATION_STRING);
			glAttachShader(m_pass[0].m_program, m_pass[0].m_geometryShader);
		}

		// attach shaders to m_program object
		glAttachShader(m_pass[0].m_program, m_pass[0].m_vertexShader);
		glAttachShader(m_pass[0].m_program, m_pass[0].m_fragmentShader);

		System::Logger::Instance()->WriteMessage(L"Linking programs");

		// link the m_program object and print out the info m_log
		//	glBindAttribLocation(m_pass[0].m_program, 0, "rm_Vertex");
		//		glBindAttribLocation(m_pass[0].m_program, 1, "rm_Normal");
		//	glBindAttribLocation(m_pass[0].m_program, 2, "rm_Texcoord0");
		//glBindAttribLocation(m_pass[0].m_program, 3, "rm_Flags");

		glLinkProgram(m_pass[0].m_program);

		
		BindUniform();

		GLint status;
		glGetProgramiv(m_pass[0].m_program, GL_LINK_STATUS, &status);
		if (status == GL_TRUE)
		{
			glValidateProgram(m_pass[0].m_program);
			glGetProgramiv(m_pass[0].m_program, GL_VALIDATE_STATUS, &status);
			if (status == GL_TRUE)
				return;
		}

		throw System::SystemError(L"Can't create GLSL program" + LOG_LOCATION_STRING);
	}

	int GLSLProgram::GetLocation(int uniform)
	{
		return m_uniform_location[uniform];
	}

	void GLSLProgram::Bind(int passNumber)
	{
		//		CheckError();
		glUseProgram(m_pass[passNumber].m_program);
		m_currentPass = passNumber;
		int index;
		if ((index = GetUniformLocation("uDiffuseMap")) != -1)
			SetUniformInt(index, 0);
		if ((index = GetUniformLocation("uNormalMap")) != -1)
			SetUniformInt(index, 1);

		/*if (m_pass[m_currentPass].state.blend)
		{
		RenderState& state = m_pass[m_currentPass].state;
		CheckError();
		glEnable(GL_BLEND);
		CheckError();
		glBlendEquationSeparate(state.blendEquationRgb, state.blendEquationAlpha);
		CheckError();
		glBlendFuncSeparate(state.blendSrcRGB, state.blendDstRGB, state.blendSrcAlpha, state.blendDstAlpha);
		CheckError();
		GLfloat* v = state.blendColor;
		CheckError();
		glBlendColor(v[0], v[1], v[2], v[3]);
		CheckError();
		}
		else
		{
		glDisable(GL_BLEND);
		}*/
	}

	void GLSLProgram::Unbind()
	{
		glUseProgram(0);
	}

	bool GLSLProgram::LoadShader(GLuint shader, const System::Buffer& data)
	{
		char * body = (char*)data.StartPointer();
		int len = data.GetSize();

		GLint compileStatus;

		glShaderSource(shader, 1, (const char**)&body,  &len);

		// compile the particle vertex shader, and print out
		glCompileShader(shader);

		glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);
		if (compileStatus == GL_TRUE)
			return true;
		GLint logLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
		if (logLength > 65536)
		{
			GLchar* buffer = new GLchar[logLength];
			glGetShaderInfoLog(shader, logLength, NULL, buffer);
			System::Logger::Instance()->WriteError(System::string(buffer));
			//printf("GLSL: %s\n", buffer);
			delete[] buffer;
		}
		else
		{
			GLchar buffer[65536];
			glGetShaderInfoLog(shader, 65536, NULL, buffer);
			System::Logger::Instance()->WriteError(System::string(buffer));
			//printf("GLSL: %s\n", buffer);
		}
		return false;
	}

	void GLSLProgram::Clear()
	{
		for (int i = 0; i < m_numPasses; i++)
		{
			glDeleteProgram(m_pass[i].m_program);                   // it will also detach shaders
			glDeleteShader(m_pass[i].m_vertexShader);
			glDeleteShader(m_pass[i].m_fragmentShader);
		}
		delete[] m_pass; m_pass = 0;
		m_ok             = false;
	}

	bool GLSLProgram::SetUniformVector4f(const char * name, const float* value)
	{
		int loc = glGetUniformLocation(m_pass[m_currentPass].m_program, name);

		if ( loc < 0 )
			throw System::SystemError(L"Can't set uniform parameter: " + System::string(name) + LOG_LOCATION_STRING);

		glUniform4fv(loc, 1, value);

		return true;
	}

	bool GLSLProgram::SetUniformVector4f( int loc, const float* value )
	{
		glUniform4fv(loc, 1, value);
		return true;
	}

	bool GLSLProgram::SetUniformVector3f(const char * name, const float* value )
	{
		int loc = glGetUniformLocation(m_pass[m_currentPass].m_program, name);
		if (loc < 0)
			throw System::SystemError(L"Can't set uniform parameter: " + System::string(name) + LOG_LOCATION_STRING);
		glUniform3fv(loc, 1, value);
		return true;
	}

	bool GLSLProgram::SetUniformVector3f(int loc, const float* value)
	{
		glUniform3fv(loc, 1, value);
		return true;
	}

	bool GLSLProgram::SetUniformVector2f(const char * name, const float* value )
	{
		int loc = glGetUniformLocation(m_pass[m_currentPass].m_program, name);
		if ( loc < 0 )
			throw System::SystemError(L"Can't set uniform parameter: " + System::string(name) + LOG_LOCATION_STRING);
		glUniform2fv(loc, 1, value);
		return true;
	}

	bool GLSLProgram::SetUniformVector2f(int loc, const float* value )
	{
		glUniform2fv(loc, 1, value);
		return true;
	}

	bool GLSLProgram::SetUniformFloat(const char * name, float value)
	{
		int loc = glGetUniformLocation(m_pass[m_currentPass].m_program, name);
		if ( loc < 0 )
			throw System::SystemError(L"Can't set uniform parameter: " + System::string(name) + LOG_LOCATION_STRING);
		glUniform1f(loc, value);
		return true;
	}

	bool GLSLProgram::SetUniformFloat(int loc, float value)
	{
		glUniform1f ( loc, value );
		return true;
	}

	bool GLSLProgram::SetUniformInt(const char * name, int value)
	{
		int loc = glGetUniformLocation(m_pass[m_currentPass].m_program, name);
		if ( loc < 0 )
			throw System::SystemError(L"Can't set uniform parameter: " + System::string(name) + LOG_LOCATION_STRING);
		glUniform1i ( loc, value );
		return true;
	}

	bool GLSLProgram ::SetUniformInt(int loc, int value)
	{
		glUniform1i( loc, value);
		return true;
	}

	bool GLSLProgram::SetUniformMatrix3f(const char * name, const float* value)
	{
		int loc = glGetUniformLocation ( m_pass[m_currentPass].m_program, name );
		if ( loc < 0 )
			throw System::SystemError(L"Can't set uniform parameter: " + System::string(name) + LOG_LOCATION_STRING);
		glUniformMatrix3fv(loc, 1, GL_FALSE, value);
		return true;
	}

	bool GLSLProgram::SetUniformMatrix3f( int loc, const float* value)
	{
		glUniformMatrix3fv(loc, 1, GL_FALSE, value);
		return true;
	}

	bool GLSLProgram::SetUniformMatrix4f(const char * name, const float* value)
	{
		int loc = glGetUniformLocation ( m_pass[m_currentPass].m_program, name );
		if ( loc < 0 )
			throw System::SystemError(L"Can't set uniform parameter: " + System::string(name) + LOG_LOCATION_STRING);
		glUniformMatrix4fv(loc, 1, GL_FALSE, value);
		return true;
	}

	bool GLSLProgram::SetUniformMatrix4f( int loc, const float* value)
	{
		glUniformMatrix4fv(loc, 1, GL_FALSE, value);
		return true;
	}

	bool GLSLProgram::SetUniformArrayMatrix4f(int loc, int count, const float* value)
	{
		glUniformMatrix4fv(loc, count, GL_FALSE, value);
		return true;
	}


	GLint GLSLProgram::GetUniformLocation(const char * name)
	{
		GLint res = glGetUniformLocation(m_pass[m_currentPass].m_program, name);
		return res;
	}

	void GLSLProgram::GetUniformVector(const char * name, float* out)
	{
		int loc = glGetUniformLocation(m_pass[m_currentPass].m_program, name);
		if ( loc < 0 )
			throw System::SystemError(L"Can't get uniform parameter: " + System::string(name) + LOG_LOCATION_STRING);
		glGetUniformfv(m_pass[m_currentPass].m_program, loc, out);
	}

	bool GLSLProgram::SetTexture(const char * name, int texUnit)
	{
		int loc = glGetUniformLocation ( m_pass[m_currentPass].m_program, name );
	//	if ( loc == -1 )
		//	throw System::SystemError(L"Can't set texture: " + System::string(name) + LOG_LOCATION_STRING);
		glUniform1i(loc, texUnit);
		return true;
	}

	bool GLSLProgram::SetTexture(int loc, int texUnit)
	{
	//	if ( loc < 0 )
		//	throw System::SystemError(L"Can't set texture" + LOG_LOCATION_STRING);
		glUniform1i(loc, texUnit);
		return true;
	}

	bool GLSLProgram::BindAttributeTo(int loc, const char * name)
	{
		glBindAttribLocation(m_pass[m_currentPass].m_program, loc, name);
		return true;
	}

	bool GLSLProgram::SetAttribute(const char * name, const float* value)
	{
		int index = glGetAttribLocation(m_pass[m_currentPass].m_program, name);
		if ( index < 0 )
			throw System::SystemError(L"Can't set attribute: " + System::string(name) + LOG_LOCATION_STRING);
		glVertexAttrib4fv ( index, value );
		return true;
	}

	bool GLSLProgram::SetAttribute(int index, const float* value)
	{
		glVertexAttrib4fv(index, value);
		return true;
	}

	int GLSLProgram::IndexForAttrName(const char * name)
	{
		return glGetAttribLocation(m_pass[m_currentPass].m_program, name);
	}

	void GLSLProgram::GetAttribute(const char * name, float* out)
	{
		int index = glGetAttribLocation(m_pass[m_currentPass].m_program, name);
		if ( index < 0 )
			throw System::SystemError(L"Can't get attribute: " + System::string(name) + LOG_LOCATION_STRING);
		glGetVertexAttribfv ( index, GL_CURRENT_VERTEX_ATTRIB, out);
	}

	void GLSLProgram::GetAttribute(int index, float* out)
	{
		glGetVertexAttribfv ( index, GL_CURRENT_VERTEX_ATTRIB, out);
	}

	System::string GLSLProgram::Version()
	{
		const char * slVer = (const char *) glGetString ( GL_SHADING_LANGUAGE_VERSION );
		if ( glGetError() != GL_NO_ERROR )
			return L"1.051";
		return System::string(slVer);
	}

	int GLSLProgram::MaxVertexUniformComponents()
	{
		int maxVertexUniformComponents;
		glGetIntegerv ( GL_MAX_VERTEX_UNIFORM_COMPONENTS, &maxVertexUniformComponents );
		return maxVertexUniformComponents;
	}

	int GLSLProgram::MaxVertexAttribs()
	{
		int maxVertexAttribs;
		glGetIntegerv ( GL_MAX_VERTEX_ATTRIBS, &maxVertexAttribs);
		return maxVertexAttribs;
	}

	int GLSLProgram::MaxFragmentTextureUnits()
	{
		int maxFragmentTextureUnits;
		glGetIntegerv ( GL_MAX_TEXTURE_IMAGE_UNITS, &maxFragmentTextureUnits );
		return maxFragmentTextureUnits;
	}

	int GLSLProgram::MaxVertexTextureUnits()
	{
		int maxVertexTextureUnits;
		glGetIntegerv ( GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, &maxVertexTextureUnits );
		return maxVertexTextureUnits;
	}

	int GLSLProgram::MaxCombinedTextureUnits()
	{
		int maxCombinedTextureUnits;
		glGetIntegerv ( GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &maxCombinedTextureUnits );
		return maxCombinedTextureUnits;
	}

	int GLSLProgram::MaxVaryingFloats()
	{
		int maxVaryingFloats;
		glGetIntegerv ( GL_MAX_VARYING_FLOATS, &maxVaryingFloats );
		return maxVaryingFloats;
	}

	int GLSLProgram::MaxFragmentUniformComponents()
	{
		int maxFragmentUniformComponents;
		glGetIntegerv ( GL_MAX_FRAGMENT_UNIFORM_COMPONENTS, &maxFragmentUniformComponents );
		return maxFragmentUniformComponents;
	}

	int GLSLProgram::MaxTextureCoords()
	{
		return 0;
	}

	int GLSLProgram::GetAttribLocation(const char* attrib)
	{
		int location = (int)glGetAttribLocation(m_pass[m_currentPass].m_program, attrib);
		return location;
	}

}
