#ifndef _H_PUNK_OPENGL_RENDER_CONTEXT_LOGIC
#define _H_PUNK_OPENGL_RENDER_CONTEXT_LOGIC

#include "../../config.h"
#include <memory>
#include "render_context_policy.h"
#include "shaders\shaders.h"

namespace OpenGL
{
	class PUNK_ENGINE RenderContextSolidTexture3D : public RenderContextPolicy<VertexShaderTransformTextured3D, FragmentShaderSolidTextured, NoShader> {};
	class PUNK_ENGINE RenderContextBumpMapping : public RenderContextPolicy<VertexShaderBump, FragmentShaderBump, NoShader> {};
	class PUNK_ENGINE RenderContextTerrain : public RenderContextPolicy<VertexShaderTerrain, FragmentShaderTerrain, NoShader> {};
	class PUNK_ENGINE RenderContextGUI : public RenderContextPolicy<VertexShaderGUI, FragmentShaderGUI, NoShader> {};
	class PUNK_ENGINE RenderContextSolid3D : public RenderContextPolicy<VertexShaderSolid, FragmentShaderSolid, NoShader> {};
	class PUNK_ENGINE RenderContextSkinning : public RenderContextPolicy<VertexShaderSkinning, FragmentShaderSkinning, NoShader> {};

	/*class Shader;

	struct RenderContextImpl;

	class  PUNK_ENGINE RenderContext
	{		
	protected:
		std::auto_ptr<RenderContextImpl> impl_rc;
	public:
		RenderContext();
		RenderContext(const RenderContext& rc);
		RenderContext& operator = (const RenderContext& rc);
		virtual ~RenderContext();

		void SetVertexShader(Shader* shader);
		void SetFragmentShader(Shader* shader);
		void SetGeometryShader(Shader* shader);
	
		VertexAttributes GetSupportedVertexAttributes() const;

		void Init();
		void Begin();
		void End();

		RenderContext* Push();
		RenderContext* Pop();

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

		void EnableDepthTest(bool flag);
	};*/
}

#endif