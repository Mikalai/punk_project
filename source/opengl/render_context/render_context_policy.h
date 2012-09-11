#ifndef _H_PUNK_OPENGL_SHADER_POLICY
#define _H_PUNK_OPENGL_SHADER_POLICY

#include <iostream>
#include "dummy_render_context_policy.h"
#include "shaders/shaders.h"
#include "../extensions.h"
#include "../../math/mat4.h"
#include "../../math/vec4.h"

namespace OpenGL
{
	struct NoShader {};

	template<class VertexShader, class FragmentShader, class GeometryShader> class RenderContextPolicy;


	/**********************************************************************************************/
	/*			POSITION TEXTURE 3D
	/**********************************************************************************************/
	template<> class RenderContextPolicy<VertexShaderTransformTextured3D, FragmentShaderSolidTextured, NoShader> : public DummyRenderPolicy
	{	
		unsigned uProjViewWorld;
		unsigned uDiffuseColor;
		unsigned uDiffuseMap;

	public:

		struct PolicyParameters : public DummyParameters
		{
			Math::mat4 m_proj_view_world;
			Math::vec4 m_diffuse_color;
			int m_diffuse_texture;
		};

	public:

		RenderContextPolicy()
		{
			m_vertex_shader.reset(new VertexShaderTransformTextured3D);
			m_fragment_shader.reset(new FragmentShaderSolidTextured);
			Init();
		}

		virtual ~RenderContextPolicy()
		{
		}

		virtual void Init()
		{
			if (m_was_modified || !m_program)
			{
				DummyRenderPolicy::Init();
				InitUniforms();
			}
		}

		virtual void InitUniforms()
		{
			uProjViewWorld = GetUniformLocation("uProjViewWorld");
			uDiffuseColor = GetUniformLocation("uDiffuseColor");
			uDiffuseMap = GetUniformLocation("uDiffuseMap");
		}

		virtual void BindParameters(const DummyParameters& pparams)
		{			
			const PolicyParameters& params = static_cast<const PolicyParameters&>(pparams);
			SetUniformMatrix4f(uProjViewWorld, &(params.m_proj_view_world[0]));
			SetUniformVector4f(uDiffuseColor, &(params.m_diffuse_color[0]));
			SetUniformInt(uDiffuseMap, params.m_diffuse_texture);
		}
		
		virtual Utility::VertexAttributes GetRequiredAttributesSet() const 
		{
			return Utility::COMPONENT_POSITION|Utility::COMPONENT_TEXTURE;
		}

		virtual void Begin()
		{
			/*
				Begin();
				BindParameters()
				***
				render();
				***
				BindParameters()
				render();
				End();
			*/

			Init();
			DummyRenderPolicy::Begin();
		}

		virtual void End()
		{
			DummyRenderPolicy::End();			
		}		
	};

	/**********************************************************************************************/
	/*			POSITION SOLID 3D
	/**********************************************************************************************/
	template<> class RenderContextPolicy<VertexShaderSolid, FragmentShaderSolid, NoShader> : public DummyRenderPolicy
	{	
		unsigned uProjViewWorld;
		unsigned uDiffuseColor;

	public:

		struct PolicyParameters : public DummyParameters
		{
			Math::mat4 m_proj_view_world;
			Math::vec4 m_diffuse_color;
		};

	public:

		RenderContextPolicy()
		{
			m_vertex_shader.reset(new VertexShaderSolid);
			m_fragment_shader.reset(new FragmentShaderSolid);
			Init();
		}

		virtual ~RenderContextPolicy()
		{
		}

		virtual void Init()
		{
			if (m_was_modified || !m_program)
			{
				DummyRenderPolicy::Init();
				InitUniforms();
			}
		}

		virtual void InitUniforms()
		{
			uProjViewWorld = GetUniformLocation("uProjViewWorld");
			uDiffuseColor = GetUniformLocation("uDiffuseColor");
		}

		virtual void BindParameters(const DummyParameters& pparams)
		{			
			const PolicyParameters& params = static_cast<const PolicyParameters&>(pparams);
			SetUniformMatrix4f(uProjViewWorld, &(params.m_proj_view_world[0]));
			SetUniformVector4f(uDiffuseColor, &(params.m_diffuse_color[0]));
		}
		
		virtual Utility::VertexAttributes GetRequiredAttributesSet() const 
		{
			return Utility::COMPONENT_POSITION;
		}

		virtual void Begin()
		{
			Init();
			DummyRenderPolicy::Begin();
		}

		virtual void End()
		{
			DummyRenderPolicy::End();			
		}		
	};

	/**********************************************************************************************/
	/*			BUMP MAPPING 3D
	/**********************************************************************************************/
	template<> class RenderContextPolicy<VertexShaderBump, FragmentShaderBump, NoShader> : public DummyRenderPolicy
	{	
		unsigned uWorld;
		unsigned uView;
		unsigned uProj;
		unsigned uNormalMatrix;
		unsigned uLightPosition;
		unsigned uAmbient;
		unsigned uSpecular;
		unsigned uDiffuse;
		unsigned uSpecularPower;
		unsigned uDiffuseMap;
		unsigned uNormalMap;

	public:

		struct PolicyParameters : public DummyParameters
		{
			Math::mat4 m_world;
			Math::mat4 m_view;
			Math::mat4 m_proj;
			Math::mat3 m_normal_matrix;
			Math::vec3 m_light_position;
			Math::vec4 m_ambient;
			Math::vec4 m_specular;
			Math::vec4 m_diffuse;
			float m_specular_power;
			int m_diffuse_texture;
			int m_normal_texture;
		};

	public:

		RenderContextPolicy()
		{
			m_vertex_shader.reset(new VertexShaderBump);
			m_fragment_shader.reset(new FragmentShaderBump);
			Init();
		}

		void Init()
		{
			if (m_was_modified || !m_program)
			{
				DummyRenderPolicy::Init();
				InitUniforms();
			}			
		}

		void InitUniforms()
		{
			uWorld = GetUniformLocation("uWorld");
			uView = GetUniformLocation("uView");
			uProj = GetUniformLocation("uProj");
			uNormalMatrix = GetUniformLocation("uNormalMatrix");
			uLightPosition = GetUniformLocation("uLightPosition");
			uAmbient = GetUniformLocation("uAmbient");
			uSpecular = GetUniformLocation("uSpecular");
			uDiffuse = GetUniformLocation("uDiffuse");
			uSpecularPower = GetUniformLocation("uSpecularPower");
			uDiffuseMap = GetUniformLocation("uDiffuseMap");
			uNormalMap = GetUniformLocation("uNormalMap");
		}

		void BindParameters(const DummyParameters& pparams)
		{						
			const PolicyParameters& params = static_cast<const PolicyParameters&>(pparams);
			SetUniformMatrix4f(uWorld, &params.m_world[0]);
			SetUniformMatrix4f(uView, &params.m_view[0]);
			SetUniformMatrix4f(uProj, &params.m_proj[0]);
			SetUniformMatrix3f(uNormalMatrix, &params.m_normal_matrix[0]);
			SetUniformVector3f(uLightPosition, &params.m_light_position[0]);
			SetUniformVector4f(uAmbient, &params.m_ambient[0]);
			SetUniformVector4f(uSpecular, &params.m_specular[0]);
			SetUniformVector4f(uDiffuse, &params.m_diffuse[0]);
			SetUniformFloat(uSpecularPower, params.m_specular_power);
			SetUniformInt(uDiffuseMap, params.m_diffuse_texture);
			SetUniformInt(uNormalMap, params.m_normal_texture);			
		}
		
		Utility::VertexAttributes GetRequiredAttributesSet() const 
		{
			return Utility::COMPONENT_POSITION|Utility::COMPONENT_TEXTURE|Utility::COMPONENT_BITANGENT|Utility::COMPONENT_TANGENT|Utility::COMPONENT_NORMAL;
		}

		virtual void Begin()
		{
			Init();
			DummyRenderPolicy::Begin();

			glEnable(GL_DEPTH_TEST);
			CHECK_GL_ERROR(L"Unable to enable depth test");
			glDepthFunc(GL_LESS);
			CHECK_GL_ERROR(L"Unable to set less depth function");
			glDepthMask(GL_TRUE);
			CHECK_GL_ERROR(L"Unable to enable depth mask");
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			CHECK_GL_ERROR(L"Unable to set polygon mode");
			/*glEnable(GL_BLEND);
			CHECK_GL_ERROR(L"Unable to enable blend");
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			CHECK_GL_ERROR(L"Unable to set blend func");
			glEnable(GL_CULL_FACE);
			CHECK_GL_ERROR(L"Unable to enable cull facing");
			glCullFace(GL_FRONT);
			CHECK_GL_ERROR(L"Unable to set cull face mode");*/
		}

		virtual void End()
		{
			DummyRenderPolicy::End();			

			//glEnable(GL_DEPTH_TEST);			
			//glDepthFunc(GL_LESS);
			//glDepthMask(GL_TRUE);
			//glEnable(GL_BLEND);
			//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);			
		}	
	};

	/**********************************************************************************************/
	/*			GRASS RENDER 3D
	/**********************************************************************************************/
	template<> class RenderContextPolicy<VertexShaderGrass, FragmentShaderGrass, NoShader> : public DummyRenderPolicy
	{	
		unsigned uProjView;
		unsigned uHeightMap;
		unsigned uPosition;
		unsigned uTime;
		unsigned uWindStrength;
		unsigned uWindDirection;
		unsigned uDiffuseColor;
		unsigned uDiffuseMap;

	public:

		struct PolicyParameters : public DummyParameters
		{
			Math::vec3 m_position;
			Math::mat4 m_proj_view;
			Math::vec4 m_diffuse_color;
			Math::vec3 m_wind_direction;
			float m_time;
			float m_wind_strength;
			int m_diffuse_texture;
			int m_height_map_texture;
		};

	public:

		RenderContextPolicy()
		{
			m_vertex_shader.reset(new VertexShaderGrass);
			m_fragment_shader.reset(new FragmentShaderGrass);
			Init();
		}

		void Init()
		{
			if (m_was_modified || !m_program)
			{
				DummyRenderPolicy::Init();
				InitUniforms();
			}
		}

		void InitUniforms()
		{
			uProjView = GetUniformLocation("uProjView");
			uHeightMap = GetUniformLocation("uHeightMap");
			uPosition = GetUniformLocation("uPosition");
			uTime = GetUniformLocation("uTime");
			uWindStrength = GetUniformLocation("uWindStrength");
			uWindDirection = GetUniformLocation("uWindDirection");
			uDiffuseColor = GetUniformLocation("uDiffuseColor");
			uDiffuseMap = GetUniformLocation("uDiffuseMap");
		}

		void BindParameters(const DummyParameters& pparams)
		{	
			const PolicyParameters& params = static_cast<const PolicyParameters&>(pparams);
			SetUniformMatrix4f(uProjView, &params.m_proj_view[0]);
			SetUniformVector4f(uDiffuseColor, &params.m_diffuse_color[0]);
			SetUniformVector3f(uPosition, &params.m_position[0]);
			SetUniformFloat(uTime, params.m_time);
			SetUniformFloat(uWindStrength, params.m_wind_strength);
			SetUniformVector3f(uWindDirection, &params.m_wind_direction[0]);
			SetUniformInt(uDiffuseMap, 0);
			SetUniformInt(uHeightMap, 1);	
		}
		
		Utility::VertexAttributes GetRequiredAttributesSet() const 
		{
			return Utility::COMPONENT_POSITION|Utility::COMPONENT_TEXTURE;
		}

		virtual void Begin()
		{
			Init();
			DummyRenderPolicy::Begin();
		}

		virtual void End()
		{
			DummyRenderPolicy::End();			
		}			
	};

	/**********************************************************************************************/
	/*			GUI RENDER 2D
	/**********************************************************************************************/
	template<> class RenderContextPolicy<VertexShaderGUI, FragmentShaderGUI, NoShader> : public DummyRenderPolicy
	{	
		unsigned uProjViewWorld;
		unsigned uDiffuseColor;
		unsigned uTextColor;
		unsigned uNoDiffuseTexture;
		unsigned uDiffuseMap;
		unsigned uTextMap;

	public:

		struct PolicyParameters : public DummyParameters
		{
			Math::mat4 m_proj_view_world;
			Math::vec4 m_diffuse_color;
			Math::vec4 m_text_color;
			Math::vec4 m_no_diffuse_texture;
			int m_diffuse_texture;
			int m_text_texture;
		};

	public:

		RenderContextPolicy()
		{
			m_vertex_shader.reset(new VertexShaderGUI);
			m_fragment_shader.reset(new FragmentShaderGUI);
			Init();
		}

		void Init()
		{
			if (m_was_modified || !m_program)
			{
				DummyRenderPolicy::Init();
				InitUniforms();
			}
		}

		void InitUniforms()
		{
			uProjViewWorld = GetUniformLocation("uProjViewWorld");
			uDiffuseColor = GetUniformLocation("uDiffuseColor");
			uTextColor = GetUniformLocation("uTextColor");
			uNoDiffuseTexture = GetUniformLocation("uNoDiffuseTexture");
			uDiffuseMap = GetUniformLocation("uDiffuseMap");
			uTextMap = GetUniformLocation("uTextMap");
		}

		void BindParameters(const DummyParameters& pparams)
		{									
			const PolicyParameters& params = static_cast<const PolicyParameters&>(pparams);
			SetUniformMatrix4f(uProjViewWorld, &params.m_proj_view_world[0]);
			SetUniformVector4f(uDiffuseColor, &params.m_diffuse_color[0]);
			SetUniformVector4f(uTextColor, &params.m_text_color[0]);
			SetUniformVector4f(uNoDiffuseTexture, &params.m_no_diffuse_texture[0]);
			SetUniformInt(uDiffuseMap, params.m_diffuse_texture);
			SetUniformInt(uTextMap, params.m_text_texture);
		}
		
		Utility::VertexAttributes GetRequiredAttributesSet() const 
		{
			return Utility::COMPONENT_POSITION|Utility::COMPONENT_TEXTURE;
		}

		virtual void Begin()
		{
			Init();
			DummyRenderPolicy::Begin();
		}

		virtual void End()
		{
			DummyRenderPolicy::End();			
		}		
	};

	/**********************************************************************************************/
	/*			TERRAIN RENDER 3D
	/**********************************************************************************************/
	template<> class RenderContextPolicy<VertexShaderTerrain, FragmentShaderTerrain, NoShader> : public DummyRenderPolicy
	{	
		unsigned uWorld;
		unsigned uView;
		unsigned uProjection;
		unsigned uProjViewWorld;
		unsigned uNormalTransform;
		unsigned ui;
		unsigned uj;
		unsigned uHeightMapUniform;
		unsigned uScale;
		unsigned uPosition;
		unsigned uLevel;
		unsigned uNormalMapUniform;
		unsigned uDiffuseMapUniform1;
		unsigned uDiffuseMapUniform2;
		unsigned uDiffuseColor;
		unsigned uLightDirection;

	public:

		struct PolicyParameters : public DummyParameters
		{
			Math::mat4 m_world;
			Math::mat4 m_view;
			Math::mat4 m_proj;
			Math::mat4 m_proj_view_world;
			Math::mat3 m_normal_tranform;
			Math::vec4 m_diffuse_color;
			Math::vec2 m_position;
			Math::vec3 m_light_position;
			Math::vec3 m_light_direction;
			float m_vert_scale;
			float m_level;
			unsigned m_i;
			unsigned m_j;
			int m_height_map_texture;
			int m_diffuse_map_1_texture;
			int m_diffuse_map_2_texture;
		};

	public:

		RenderContextPolicy()
		{
			m_vertex_shader.reset(new VertexShaderGUI);
			m_fragment_shader.reset(new FragmentShaderGUI);
			Init();
		}

		void Init()
		{
			if (m_was_modified || !m_program)
			{
				DummyRenderPolicy::Init();
				InitUniforms();
			}
		}

		void InitUniforms()
		{
			uWorld = GetUniformLocation("uWorld");
			uView = GetUniformLocation("uView");
			uProjection = GetUniformLocation("uProjection");
			uProjViewWorld = GetUniformLocation("uProjViewWorld");
			uNormalTransform = GetUniformLocation("uNormalTransform");
			ui = GetUniformLocation("ui");
			uj = GetUniformLocation("uj");
			uHeightMapUniform = GetUniformLocation("uHeightMapUniform");
			uScale = GetUniformLocation("uScale");
			uPosition = GetUniformLocation("uPosition");
			uLevel = GetUniformLocation("uLevel");
			uNormalMapUniform = GetUniformLocation("uNormalMapUniform");
			uDiffuseMapUniform1 = GetUniformLocation("uDiffuseMapUniform1");
			uDiffuseMapUniform2 = GetUniformLocation("uDiffuseMapUniform2");
			uDiffuseColor = GetUniformLocation("uDiffuseColor");
			uLightDirection = GetUniformLocation("uLightDirection");
		}

		void BindParameters(const DummyParameters& pparams)
		{										
			const PolicyParameters& params = static_cast<const PolicyParameters&>(pparams);
			SetUniformMatrix4f(uProjViewWorld, &params.m_proj_view_world[0]);
			SetUniformMatrix4f(uWorld, &params.m_world[0]);
			SetUniformMatrix4f(uView, &params.m_view[0]);
			SetUniformMatrix4f(uProjection, &params.m_proj[0]);
			SetUniformMatrix3f(uNormalTransform, &params.m_normal_tranform[0]);
			SetUniformVector3f(uLightDirection, &params.m_light_direction[0]);
			SetUniformVector4f(uDiffuseColor, &params.m_diffuse_color[0]);
			SetUniformVector2f(uPosition, &params.m_position[0]);
			SetUniformInt(uHeightMapUniform, params.m_height_map_texture);
			SetUniformInt(uDiffuseMapUniform1, params.m_diffuse_map_1_texture);
			SetUniformInt(uDiffuseMapUniform2, params.m_diffuse_map_2_texture);
			SetUniformFloat(uLevel, float(params.m_level));
			SetUniformInt(ui, params.m_i);
			SetUniformInt(uj, params.m_j);
			SetUniformFloat(uScale, params.m_vert_scale);			
		}
		
		Utility::VertexAttributes GetRequiredAttributesSet() const 
		{
			return Utility::COMPONENT_POSITION|Utility::COMPONENT_TEXTURE|Utility::COMPONENT_NORMAL|Utility::COMPONENT_FLAG;
		}

		virtual void Begin()
		{
			Init();
			DummyRenderPolicy::Begin();
		}

		virtual void End()
		{
			DummyRenderPolicy::End();			
		}	
	};

	
	/**********************************************************************************************/
	/*			SKINNING 3D
	/**********************************************************************************************/
	template<> class RenderContextPolicy<VertexShaderSkinning, FragmentShaderSkinning, NoShader> : public DummyRenderPolicy
	{	
		static const int MAX_BONES = 64;

		unsigned uWorld;
		unsigned uView;
		unsigned uProj;
		unsigned uMeshMatrix;
		unsigned uMeshMatrixInversed;
		unsigned uNormalMatrix;
		unsigned uProjViewWorld;
		unsigned uViewWorld;
		unsigned uLightPosition;
		unsigned uBones[64];
		unsigned uAmbient;
		unsigned uSpecular;
		unsigned uDiffuse;
		unsigned uSpecularPower;
		unsigned uDiffuseMap;
		unsigned uNormalMap;

	public:

		struct PolicyParameters : public DummyParameters
		{
			Math::mat4 m_world;
			Math::mat4 m_view;
			Math::mat4 m_proj;
			Math::mat4 m_mesh_matrix;
			Math::mat4 m_mesh_matrix_inversed;
			Math::mat3 m_normal_matrix;
			Math::mat4 m_proj_view_world;
			Math::mat4 m_view_world;
			Math::vec3 m_light_position;
			Math::mat4 m_bone[MAX_BONES];
			Math::vec4 m_ambient;
			Math::vec4 m_specular;
			Math::vec4 m_diffuse;			
			float m_specular_power;
			unsigned m_diffuse_texture;
			unsigned m_normal_texture;
		};

	public:

		RenderContextPolicy()
		{
			m_vertex_shader.reset(new VertexShaderSkinning);
			m_fragment_shader.reset(new FragmentShaderSkinning);
			Init();
		}

		void Init()
		{
			if (m_was_modified || !m_program)
			{
				DummyRenderPolicy::Init();
				InitUniforms();
			}			
		}

		void InitUniforms()
		{
			uWorld = GetUniformLocation("uWorld");
			uView = GetUniformLocation("uView");
			uProj = GetUniformLocation("uProj");
			uMeshMatrix = GetUniformLocation("uMeshMatrix");
			uMeshMatrixInversed = GetUniformLocation("uMeshMatrixInversed");
			uNormalMatrix = GetUniformLocation("uNormalMatrix");
			uProjViewWorld = GetUniformLocation("uProjViewWorld");
			uViewWorld = GetUniformLocation("uViewWorld");
			uLightPosition = GetUniformLocation("uLightPosition");
			for (int i = 0; i < MAX_BONES; ++i)
			{
				char buf[128];
				sprintf_s<128>(buf, "uBones[%d]", i);
				uBones[i] = GetUniformLocation(buf);
			}
			uAmbient = GetUniformLocation("uAmbient");
			uSpecular = GetUniformLocation("uSpecular");
			uDiffuse = GetUniformLocation("uDiffuse");
			uSpecularPower = GetUniformLocation("uSpecularPower");
			uDiffuseMap = GetUniformLocation("uDiffuseMap");
			uNormalMap = GetUniformLocation("uNormalMap");
		}

		void BindParameters(const DummyParameters& pparams)
		{						
			const PolicyParameters& params = static_cast<const PolicyParameters&>(pparams);
			SetUniformMatrix4f(uWorld, &params.m_world[0]);
			SetUniformMatrix4f(uView, &params.m_view[0]);
			SetUniformMatrix4f(uWorld, &params.m_proj[0]);
			SetUniformMatrix4f(uMeshMatrix, &params.m_mesh_matrix[0]);
			SetUniformMatrix4f(uMeshMatrixInversed, &params.m_mesh_matrix_inversed[0]);
			SetUniformMatrix3f(uNormalMatrix, &params.m_normal_matrix[0]);
			SetUniformMatrix4f(uProjViewWorld, &params.m_proj_view_world[0]);
			SetUniformMatrix4f(uViewWorld, &params.m_view_world[0]);
			SetUniformVector3f(uLightPosition, &params.m_light_position[0]);
			for (int i = 0; i < MAX_BONES; ++i)
				SetUniformMatrix4f(uBones[i], &params.m_bone[i][0]);
			SetUniformVector4f(uAmbient, &params.m_ambient[0]);
			SetUniformVector4f(uSpecular, &params.m_specular[0]);
			SetUniformVector4f(uDiffuse, &params.m_diffuse[0]);
			SetUniformFloat(uSpecularPower, params.m_specular_power);
			SetUniformInt(uDiffuseMap, params.m_diffuse_texture);
			SetUniformInt(uNormalMap, params.m_normal_texture);
		}
		
		Utility::VertexAttributes GetRequiredAttributesSet() const 
		{
			return Utility::COMPONENT_POSITION|Utility::COMPONENT_TEXTURE|Utility::COMPONENT_BITANGENT|Utility::COMPONENT_TANGENT|Utility::COMPONENT_NORMAL|Utility::COMPONENT_BONE_WEIGHT|Utility::COMPONENT_BONE_ID;
		}

		virtual void Begin()
		{
			Init();
			DummyRenderPolicy::Begin();

			glEnable(GL_DEPTH_TEST);
			CHECK_GL_ERROR(L"Unable to enable depth test");
			glDepthFunc(GL_LESS);
			CHECK_GL_ERROR(L"Unable to set less depth function");
			glDepthMask(GL_TRUE);
			CHECK_GL_ERROR(L"Unable to enable depth mask");
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			CHECK_GL_ERROR(L"Unable to set polygon mode");
			/*glEnable(GL_BLEND);
			CHECK_GL_ERROR(L"Unable to enable blend");
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			CHECK_GL_ERROR(L"Unable to set blend func");
			glEnable(GL_CULL_FACE);
			CHECK_GL_ERROR(L"Unable to enable cull facing");
			glCullFace(GL_FRONT);
			CHECK_GL_ERROR(L"Unable to set cull face mode");*/
		}

		virtual void End()
		{
			DummyRenderPolicy::End();			

			//glEnable(GL_DEPTH_TEST);			
			//glDepthFunc(GL_LESS);
			//glDepthMask(GL_TRUE);
			//glEnable(GL_BLEND);
			//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);			
		}	
	};
}

#endif