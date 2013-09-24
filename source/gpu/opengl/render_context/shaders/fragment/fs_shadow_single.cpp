#include <sstream>
#include "fs_shadow_single.h"
#include "../gl_shader_type.h"
#include "../../../../../system/environment.h"
#include "../../rc_dynamic.h"


namespace Gpu
{
    namespace OpenGL
    {
        FsShadowSingle::FsShadowSingle()
            : Shader(ShaderType::Fragment)
        {
            CookFromFile(System::Environment::Instance()->GetShaderFolder()
                         + GetShaderFile(ShaderCollection::FragmentShadowSingle));
        }

        void FsShadowSingle::InitUniforms()
        {
           // uDiffuseMap = m_rc->GetUniformLocation("uDiffuseMap");
            //uFar = m_rc->GetUniformLocation("uFar");
            //uNear = m_rc->GetUniformLocation("uNear");

            uShadowTextureArray = m_rc->GetUniformLocation("uShadowTextureArray");
            uFarDistance = m_rc->GetUniformLocation("uFarDistance");
            for (int i = 0; i != 4; ++i)
            {
                std::stringstream stream;
                stream << "uShadowMatrix[" << i << "]";
                uShadowMatrix[i] = m_rc->GetUniformLocation(stream.str().c_str());
            }

//            uFog.color = m_rc->GetUniformLocation("uFog.color");
//            uFog.density = m_rc->GetUniformLocation("uFog.density");
//            uFog.end = m_rc->GetUniformLocation("uFog.end");
//            uFog.scale = m_rc->GetUniformLocation("uFog.scale");
//            uFog.start = m_rc->GetUniformLocation("uFog.start");
        }

        void FsShadowSingle::BindParameters(const CoreState& params)
        {
            //m_rc->SetUniformInt(uDiffuseMap, params.texture_state->m_diffuse_slot[0]);
            //m_rc->SetUniformVector4f(uFarDistance, params.view_state->m_far_distances);
//            Math::PerspectiveDecoder d(params.view_state->m_projection);
//            m_rc->SetUniformFloat(uFar, d.GetFarZ());
//            m_rc->SetUniformFloat(uNear, d.GetNearZ());

            m_rc->SetUniformInt(uShadowTextureArray, params.texture_state->m_texture_array_slot);
            m_rc->SetUniformVector4f(uFarDistance, params.light_state->m_lights[0].GetFarDistances());
            for (size_t i = 0; i != 4; ++i)
            {                
                m_rc->SetUniformMatrix4f(uShadowMatrix[i], params.light_state->m_lights[0].GetShadowMatrix(i));
            }            

//            m_rc->SetUniformVector4f(uFog.color, params.render_state->m_fog.GetColor());
//            m_rc->SetUniformFloat(uFog.density, params.render_state->m_fog.GetDensity());
//            m_rc->SetUniformFloat(uFog.end, params.render_state->m_fog.GetEnd());
//            m_rc->SetUniformFloat(uFog.scale, params.render_state->m_fog.GetScale());
//            m_rc->SetUniformFloat(uFog.start, params.render_state->m_fog.GetStart());
        }

        int64_t FsShadowSingle::GetRequiredAttributesSet() const
        {
            return 0;
        }

    }
}
