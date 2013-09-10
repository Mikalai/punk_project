//#include "vs_pfl_diffuse_simple_shadow.h"
//#include "../gl_shader_type.h"
//#include "../../../../../system/environment.h"
//#include "../../rc_dynamic.h"


//namespace Gpu
//{
//    namespace OpenGL
//    {
//        VsPerVertexLightingDiffuseShadowSimple::VsPerVertexLightingDiffuseShadowSimple()
//            : Shader(ShaderType::Vertex)
//        {
//            CookFromFile(System::Environment::Instance()->GetShaderFolder()
//                         + GetShaderFile(ShaderCollection::VsPerVertexDiffuseLightingShadowSimple));
//        }

//        void VsPerVertexLightingDiffuseShadowSimple::InitUniforms()
//        {
////            uViewModel = m_rc->GetUniformLocation("uViewModel");
////            uProj = m_rc->GetUniformLocation("uProj");
//            uWorld = m_rc->GetUniformLocation("uWorld");
//            uProjViewWorld = m_rc->GetUniformLocation("uProjViewWorld");
//            //uNormalMatrix = m_rc->GetUniformLocation("uNormalMatrix");
//            //uDiffuseColor = m_rc->GetUniformLocation("uDiffuseColor");
////            uLightsCount = m_rc->GetUniformLocation("uLightsCount");
////            for (int i = 0; i != MAX_LIGHTS; ++i)
////            {
////                {
////                    std::stringstream stream;
////                    stream << "uLight[" << i << "].ambient_color";
////                    uLight[i].ambient_color = m_rc->GetUniformLocation(stream.str().c_str());
////                }

////                {
////                    std::stringstream stream;
////                    stream << "uLight[" << i << "].attenuation_constant";
////                    uLight[i].attenuation_constant = m_rc->GetUniformLocation(stream.str().c_str());
////                }

////                {
////                    std::stringstream stream;
////                    stream << "uLight[" << i << "].attenuation_linear";
////                    uLight[i].attenuation_linear = m_rc->GetUniformLocation(stream.str().c_str());
////                }

////                {
////                    std::stringstream stream;
////                    stream << "uLight[" << i << "].attenuation_model";
////                    uLight[i].attenuation_model = m_rc->GetUniformLocation(stream.str().c_str());
////                }

////                {
////                    std::stringstream stream;
////                    stream << "uLight[" << i << "].attenuation_quadric";
////                    uLight[i].attenuation_quadric = m_rc->GetUniformLocation(stream.str().c_str());
////                }

////                {
////                    std::stringstream stream;
////                    stream << "uLight[" << i << "].diffuse_color";
////                    uLight[i].diffuse_color = m_rc->GetUniformLocation(stream.str().c_str());
////                }

////                {
////                    std::stringstream stream;
////                    stream << "uLight[" << i << "].direction";
////                    uLight[i].direction = m_rc->GetUniformLocation(stream.str().c_str());
////                }

////                {
////                    std::stringstream stream;
////                    stream << "uLight[" << i << "].position";
////                    uLight[i].position = m_rc->GetUniformLocation(stream.str().c_str());
////                }

////                {
////                    std::stringstream stream;
////                    stream << "uLight[" << i << "].spot";
////                    uLight[i].spot = m_rc->GetUniformLocation(stream.str().c_str());
////                }

////                {
////                    std::stringstream stream;
////                    stream << "uLight[" << i << "].type";
////                    uLight[i].type = m_rc->GetUniformLocation(stream.str().c_str());
////                }
////            }
//        }

//        void VsPerVertexLightingDiffuseShadowSimple::BindParameters(const CoreState& params)
//        {
//            const Math::mat4 view_model_matrix = params.view_state->m_view * params.batch_state->m_world;
//            const Math::mat3 normal_matrix = view_model_matrix.RotationPart().Transposed().Inversed();
//            const Math::mat4 m = params.view_state->m_projection * params.view_state->m_view * params.batch_state->m_world;
//            m_rc->SetUniformMatrix4f(uProjViewWorld, m);
//            m_rc->SetUniformMatrix4f(uWorld, params.batch_state->m_world);
////            m_rc->SetUniformMatrix4f(uViewModel, view_model_matrix);
//            //m_rc->SetUniformMatrix3f(uNormalMatrix, normal_matrix);
//  //          m_rc->SetUniformMatrix4f(uProj, params.view_state->m_projection);
//            //m_rc->SetUniformVector4f(uDiffuseColor, params.batch_state->m_material.m_diffuse_color);
////            m_rc->SetUniformInt(uLightsCount, params.light_state->m_used_lights);
////            for (int i = 0; i != params.light_state->m_used_lights; ++i)
////            {
////                m_rc->SetUniformVector4f(uLight[i].direction, params.light_state->m_lights[i].GetDirection());
////                m_rc->SetUniformVector4f(uLight[i].position, params.light_state->m_lights[i].GetPosition());
////                m_rc->SetUniformVector4f(uLight[i].diffuse_color, params.light_state->m_lights[i].GetDiffuseColor());
////                m_rc->SetUniformVector4f(uLight[i].ambient_color, params.light_state->m_lights[i].GetAmbientColor());
////                m_rc->SetUniformFloat(uLight[i].attenuation_constant, params.light_state->m_lights[i].GetLightConstantAttenuation());
////                m_rc->SetUniformFloat(uLight[i].attenuation_linear, params.light_state->m_lights[i].GetLightLinearAttenuation());
////                m_rc->SetUniformFloat(uLight[i].attenuation_quadric, params.light_state->m_lights[i].GetLightQuadricAttenuation());
////                m_rc->SetUniformFloat(uLight[i].spot, params.light_state->m_lights[i].GetSpotExponent());
////                m_rc->SetUniformInt(uLight[i].type, (int)params.light_state->m_lights[i].GetType());
////                m_rc->SetUniformInt(uLight[i].attenuation_model, (int)params.light_state->m_lights[i].GetLightAttenuation());
////            }
//        }

//        int64_t VsPerVertexLightingDiffuseShadowSimple::GetRequiredAttributesSet() const
//        {
//            return VertexComponent::Position::Value()
//                    | VertexComponent::Normal::Value()
//                    | VertexComponent::Texture0::Value();
//        }

//    }
//}
