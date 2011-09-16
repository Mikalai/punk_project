//
// Class to encapsulate GLSL m_program and shader objects and working with them
//
// Author: Alex V. Boreskoff <alexboreskoff@mtu-net.ru>, <steps3d@narod.ru>
//

#ifndef __GLSL_PROGRAM__
#define __GLSL_PROGRAM__

//#include "os.h"
#include "shader_program.h"
#include "../../../string.h"

namespace OpenGL
{
	/*
	static const int BlenFuncTable[] =
	{
	GL_FUNC_ADD,
	GL_FUNC_SUBTRACT,
	GL_FUNC_REVERSE_SUBTRACT,
	GL_MIN,
	GL_MAX
	};

	static const int BlendTable[] =
	{
	GL_ZERO,
	GL_ONE,
	GL_SRC_COLOR,
	GL_ONE_MINUS_SRC_COLOR,
	GL_DST_COLOR,
	GL_ONE_MINUS_DST_COLOR,
	GL_SRC_ALPHA,
	GL_ONE_MINUS_SRC_ALPHA,
	GL_DST_ALPHA,
	GL_ONE_MINUS_DST_ALPHA,
	GL_CONSTANT_COLOR,
	GL_ONE_MINUS_CONSTANT_COLOR,
	GL_CONSTANT_ALPHA,
	GL_ONE_MINUS_CONSTANT_ALPHA
	};

	*/
	class GLSLProgram : public ::ShaderProgram
	{
	public:

		struct RenderState
		{
			/*		GLboolean blend;
			GLenum blendSrcRGB;
			GLenum blendSrcAlpha;
			GLenum blendDstRGB;
			GLenum blendDstAlpha;
			GLenum blendEquationRgb;
			GLenum blendEquationAlpha;
			GLfloat blendColor[4];*/
			RenderState()
			{
				/*blend = GL_FALSE;
				blendSrcRGB = GL_ONE;
				blendSrcAlpha = GL_ONE;
				blendSrcRGB = GL_ZERO;
				blendSrcAlpha = GL_ZERO;
				blendEquationRgb = GL_FUNC_ADD;
				blendEquationAlpha = GL_FUNC_ADD;
				blendColor[0] = blendColor[1] = blendColor[2] = blendColor[3] = 0;*/
			}
		};
		struct Pass
		{
			RenderState state;
			unsigned m_program;
			unsigned m_vertexShader;
			unsigned m_fragmentShader;
			Pass() : m_program(0), m_vertexShader(0), m_fragmentShader(0) {}
		};

		Pass* m_pass;
		int m_numPasses;
		int m_currentPass;
		bool m_ok;

		GLSLProgram  ();
		~GLSLProgram ();
		static void Init();
		virtual void CreateFromFile( const System::string& vertexFileName, const System::string& fragmentFileName );
		virtual void CreateFromMemory( const System::Buffer& vertexSource, const System::Buffer& fragmentSource);
		virtual void CreateFromRFX(const System::string& fileName, const System::string& effectGroup, const System::string& effectName);
		virtual void Clear();
		virtual int GetPassCount() const;
		virtual void Bind(int passNumber = 0);
		virtual void Unbind();
		bool SetUniformVector4f( const char * name, const float* value);
		bool SetUniformVector4f( int loc, const float* value);
		bool SetUniformVector3f( const char * name, const float* value);
		bool SetUniformVector3f( int loc, const float* value);
		bool SetUniformVector2f( const char * name, const float* value);
		bool SetUniformVector2f( int loc, const float* value);
		bool SetUniformFloat( const char * name, float value);
		bool SetUniformFloat( int loc, float value);
		bool SetUniformMatrix4f( const char * name, const float* value);
		bool SetUniformMatrix4f( int loc, const float* value);
		bool SetUniformArrayMatrix4f( int loc, int count, const float* value);
		bool SetUniformMatrix3f( const char * name, const float*  value);
		bool SetUniformMatrix3f( int loc, const float*  value);		
		bool SetUniformInt( const char * name, int value);
		bool SetUniformInt( int loc, int value);
		void GetUniformVector( const char * name, float* out);
		void GetUniformVector( int loc, float* out);
		int GetUniformLocation( const char * name);
		int GetAttribLocation(const char* attrib);
		bool SetAttribute( const char * name, const float* value);
		bool SetAttribute( int index, const float* value);
		void GetAttribute( const char * name, float* out);
		void GetAttribute( int index, float* out);
		int IndexForAttrName( const char * name);
		bool BindAttributeTo( int no, const char * name);
		bool SetTexture( const char * name, int texUnit);
		bool SetTexture( int loc, int texUnit);

		static  System::string  Version();
		static int MaxVertexUniformComponents();
		static int MaxVertexAttribs();
		static int MaxFragmentTextureUnits();
		static int MaxVertexTextureUnits();
		static int MaxCombinedTextureUnits();
		static int MaxVaryingFloats();
		static int MaxFragmentUniformComponents();
		static int MaxTextureCoords();

		void AllocatePass();
		void CreatePass(const System::Buffer& vertexSrc, const System::Buffer& fragmentSrc, Pass& pass);
	protected:
		bool LoadShader( unsigned shader, const System::Buffer& buffer);
	};

	namespace Shaders
	{
		extern GLSLProgram g_TextureBumpProgram;
		extern GLSLProgram g_ShowNormalProgram;
		extern GLSLProgram g_ShowTangentProgram;
		extern GLSLProgram g_ShowBinormalProgram;
	}
}

#endif
