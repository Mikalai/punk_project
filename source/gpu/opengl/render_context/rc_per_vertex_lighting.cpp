//#ifdef USE_LIGHT_PER_VERTEX_DIFFUSE

//#include "rc_per_vertex_lighting.h"
//#include "../gl/module.h"
//#include "../../common/vertex.h"

//namespace Gpu
//{
//	namespace OpenGL
//	{
//		RenderContextPolicy<
//				ShaderCollection::VertexLightPerVertexDiffuse,
//				ShaderCollection::FragmentLightPerVertexDiffuse,
//				ShaderCollection::No>::RenderContextPolicy()
//			: OpenGLRenderContext(ShaderCollection::VertexLightPerVertexDiffuse,
//								  ShaderCollection::FragmentLightPerVertexDiffuse,
//								  ShaderCollection::No)
//		{
//			Init();
//		}

//		void RenderContextPolicy<
//		ShaderCollection::VertexLightPerVertexDiffuse,
//		ShaderCollection::FragmentLightPerVertexDiffuse,
//		ShaderCollection::No>::InitUniforms()
//		{
//			uProjViewWorld = GetUniformLocation("uProjViewWorld");
//			uNormalMatrix = GetUniformLocation("uNormalMatrix");
//			uViewWorld = GetUniformLocation("uViewWorld");
//			uView = GetUniformLocation("uView");
//			uDiffuseColor = GetUniformLocation("uDiffuseColor");

//			for (int i = 0; i != MAX_LIGHTS; ++i)
//			{
//				{
//					std::stringstream stream;
//					stream << "uLightPosition[" << i << "]";
//					uLightPosition[i] = GetUniformLocation(stream.str().c_str());
//				}
//				{
//					std::stringstream stream;
//					stream << "uLightDiffuse[" << i << "]";
//					uLightDiffuse[i] = GetUniformLocation(stream.str().c_str());;
//				}
//				{
//					std::stringstream stream;
//					stream << "uConstantAttenuation[" << i << "]";
//					uConstantAttenuation[i] = GetUniformLocation(stream.str().c_str());;
//				}
//				{
//					std::stringstream stream;
//					stream << "uLinearAttenuation[" << i << "]";
//					uLinearAttenuation[i] = GetUniformLocation(stream.str().c_str());;
//				}
//				{
//					std::stringstream stream;
//					stream << "uQuadricAttenuation[" << i << "]";
//					uQuadricAttenuation[i] = GetUniformLocation(stream.str().c_str());;
//				}
//				{
//					std::stringstream stream;
//					stream << "uMode[" << i << "]";
//					uMode[i] = GetUniformLocation(stream.str().c_str());;
//				}
//				{
//					std::stringstream stream;
//					stream << "uSpotExponent[" << i << "]";
//					uSpotExponent[i] = GetUniformLocation(stream.str().c_str());;
//				}
//				{
//					std::stringstream stream;
//					stream << "uType[" << i << "]";
//					uType[i] = GetUniformLocation(stream.str().c_str());;
//				}
//				{
//					std::stringstream stream;
//					stream << "uLightDirection[" << i << "]";
//					uLightDirection[i] = GetUniformLocation(stream.str().c_str());;
//				}
//			}
//		}

//		void RenderContextPolicy<
//		ShaderCollection::VertexLightPerVertexDiffuse,
//		ShaderCollection::FragmentLightPerVertexDiffuse,
//		ShaderCollection::No>::BindParameters(const CoreState& params)
//		{
//			const Math::mat4 proj_view_world = params.view_state->m_projection * params.view_state->m_view * params.batch_state->m_world;
//			const Math::mat3 normal_matrix = (params.view_state->m_view * params.batch_state->m_world).RotationPart().Transposed().Inversed();
//			const Math::mat4 view_world = params.view_state->m_view * params.batch_state->m_world;
//			SetUniformMatrix4f(uProjViewWorld, &proj_view_world[0]);
//			SetUniformMatrix3f(uNormalMatrix, &normal_matrix[0]);
//			SetUniformMatrix4f(uViewWorld, &view_world[0]);
//			SetUniformMatrix4f(uView, &params.view_state->m_view[0]);
//			SetUniformVector4f(uDiffuseColor, &params.batch_state->m_material.m_diffuse_color[0]);

//			for (int i = 0; i != MAX_LIGHTS; ++i)
//			{
//				SetUniformVector4f(uLightPosition[i], &params.light_state->m_lights[i].GetPosition()[0]);
//				SetUniformVector4f(uLightDiffuse[i], &params.light_state->m_lights[i].GetDiffuseColor()[0]);
//				SetUniformVector4f(uLightDirection[i], &params.light_state->m_lights[i].GetDirection()[0]);
//				SetUniformFloat(uConstantAttenuation[i], params.light_state->m_lights[i].GetLightConstantAttenuation());
//				SetUniformFloat(uLinearAttenuation[i], params.light_state->m_lights[i].GetLightLinearAttenuation());
//				SetUniformFloat(uQuadricAttenuation[i], params.light_state->m_lights[i].GetLightQuadricAttenuation());
//				SetUniformFloat(uSpotExponent[i], params.light_state->m_lights[i].GetSpotExponent());

//				switch (params.light_state->m_lights[i].GetLightAttenuation())
//				{
//				case LightAttenuation::Constant:
//					SetUniformInt(uMode[i], 0);
//					break;
//				case LightAttenuation::Linear:
//					SetUniformInt(uMode[i], 1);
//					break;
//				case LightAttenuation::Quadratic:
//					SetUniformInt(uMode[i], 2);
//					break;
//				}

//				switch (params.light_state->m_lights[i].GetType())
//				{
//				case LightType::Point:
//					SetUniformInt(uType[i], 0);
//					break;
//				case LightType::Spot:
//					SetUniformInt(uType[i], 1);
//					break;
//				}
//			}
//			SetUpOpenGL(params);
//		}

//		int64_t RenderContextPolicy<
//		ShaderCollection::VertexLightPerVertexDiffuse,
//		ShaderCollection::FragmentLightPerVertexDiffuse,
//		ShaderCollection::No>::GetRequiredAttributesSet() const
//		{
//			return Vertex<VertexComponent::Position, VertexComponent::Normal>::Value();
//		}
//	}
//}

//#endif	//	USE_LIGHT_PER_VERTEX_DIFFUSE
