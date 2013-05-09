#ifdef USE_LIGHT_PER_VERTEX_DIFFUSE

#include "rc_per_vertex_lighting.h"
#include "../gl/module.h"
#include "../../common/vertex.h"

namespace GPU
{
	namespace OpenGL
	{
		RenderContextPolicy<
				ShaderCollection::VertexLightPerVertexDiffuse,
				ShaderCollection::FragmentLightPerVertexDiffuse,
				ShaderCollection::No>::RenderContextPolicy()
			: OpenGLRenderContext(ShaderCollection::VertexLightPerVertexDiffuse,
								  ShaderCollection::FragmentLightPerVertexDiffuse,
								  ShaderCollection::No)
		{
			Init();
		}

		void RenderContextPolicy<
		ShaderCollection::VertexLightPerVertexDiffuse,
		ShaderCollection::FragmentLightPerVertexDiffuse,
		ShaderCollection::No>::InitUniforms()
		{
			uProjViewWorld = GetUniformLocation("uProjViewWorld");
			uNormalMatrix = GetUniformLocation("uNormalMatrix");
			uViewWorld = GetUniformLocation("uViewWorld");
			uView = GetUniformLocation("uView");
			uDiffuseColor = GetUniformLocation("uDiffuseColor");

			for (int i = 0; i != MAX_LIGHTS; ++i)
			{
				{
					std::stringstream stream;
					stream << "uLightPosition[" << i << "]";
					uLightPosition[i] = GetUniformLocation(stream.str().c_str());
				}
				{
					std::stringstream stream;
					stream << "uLightDiffuse[" << i << "]";
					uLightDiffuse[i] = GetUniformLocation(stream.str().c_str());;
				}
				{
					std::stringstream stream;
					stream << "uConstantAttenuation[" << i << "]";
					uConstantAttenuation[i] = GetUniformLocation(stream.str().c_str());;
				}
				{
					std::stringstream stream;
					stream << "uLinearAttenuation[" << i << "]";
					uLinearAttenuation[i] = GetUniformLocation(stream.str().c_str());;
				}
				{
					std::stringstream stream;
					stream << "uQuadricAttenuation[" << i << "]";
					uQuadricAttenuation[i] = GetUniformLocation(stream.str().c_str());;
				}
				{
					std::stringstream stream;
					stream << "uMode[" << i << "]";
					uMode[i] = GetUniformLocation(stream.str().c_str());;
				}
			}
		}

		void RenderContextPolicy<
		ShaderCollection::VertexLightPerVertexDiffuse,
		ShaderCollection::FragmentLightPerVertexDiffuse,
		ShaderCollection::No>::BindParameters(const CoreState& params)
		{
			const Math::mat4 proj_view_world = params.m_projection * params.m_view * params.m_world;
			const Math::mat3 normal_matrix = (params.m_view * params.m_world).RotationPart().Transposed().Inversed();
			const Math::mat4 view_world = params.m_view * params.m_world;
			SetUniformMatrix4f(uProjViewWorld, &proj_view_world[0]);
			SetUniformMatrix3f(uNormalMatrix, &normal_matrix[0]);
			SetUniformMatrix4f(uViewWorld, &view_world[0]);
			SetUniformMatrix4f(uView, &params.m_view[0]);
			SetUniformVector4f(uDiffuseColor, &params.m_diffuse_color[0]);

			for (int i = 0; i != MAX_LIGHTS; ++i)
			{
				SetUniformVector4f(uLightPosition[i], &params.m_lights[i].GetPosition()[0]);
				SetUniformVector4f(uLightDiffuse[i], &params.m_lights[i].GetDiffuseColor()[0]);
				SetUniformFloat(uConstantAttenuation[i], params.m_lights[i].GetLightConstantAttenuation());
				SetUniformFloat(uLinearAttenuation[i], params.m_lights[i].GetLightLinearAttenuation());
				SetUniformFloat(uQuadricAttenuation[i], params.m_lights[i].GetLightQuadricAttenuation());
				switch (params.m_lights[i].GetLightAttenuation())
				{
				case LightAttenuation::Constant:
					SetUniformInt(uMode[i], 0);
					break;
				case LightAttenuation::Linear:
					SetUniformInt(uMode[i], 1);
					break;
				case LightAttenuation::Quadratic:
					SetUniformInt(uMode[i], 2);
					break;
				}
			}
			SetUpOpenGL(params);
		}

		int64_t RenderContextPolicy<
		ShaderCollection::VertexLightPerVertexDiffuse,
		ShaderCollection::FragmentLightPerVertexDiffuse,
		ShaderCollection::No>::GetRequiredAttributesSet() const
		{
			return Vertex<VertexComponent::Position, VertexComponent::Normal>::Value();
		}
	}
}

#endif	//	USE_LIGHT_PER_VERTEX_DIFFUSE
