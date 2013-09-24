#include <sstream>
#include "fs_per_vertex_lighting_diffuse_shadow_simple.h"
#include "../gl_shader_type.h"
#include "../../../../../system/environment.h"
#include "../../rc_dynamic.h"


namespace Gpu
{
    namespace OpenGL
    {
        FsPerVertexLightingDiffuseSimpleShadow::FsPerVertexLightingDiffuseSimpleShadow()
            : Shader(ShaderType::Fragment)
        {
            CookFromFile(System::Environment::Instance()->GetShaderFolder()
                         + GetShaderFile(ShaderCollection::FsPerVertexDiffuseLightingShadowSimple));
        }

        void FsPerVertexLightingDiffuseSimpleShadow::InitUniforms()
        {
            uShadowTextureArray = m_rc->GetUniformLocation("uShadowTextureArray");
            uFarDistance = m_rc->GetUniformLocation("uFarDistance");
            for (int i = 0; i != 4; ++i)
            {
                std::stringstream stream;
                stream << "uShadowMatrix[" << i << "]";
                uShadowMatrix[i] = m_rc->GetUniformLocation(stream.str().c_str());
            }
        }

        void FsPerVertexLightingDiffuseSimpleShadow::BindParameters(const CoreState& params)
        {
            m_rc->SetUniformInt(uShadowTextureArray, params.texture_state->m_texture_array_slot);
            m_rc->SetUniformVector4f(uFarDistance, params.light_state->m_lights[0].GetFarDistances());
            for (size_t i = 0; i != 4; ++i)
            {
                m_rc->SetUniformMatrix4f(uShadowMatrix[i], params.light_state->m_lights[0].GetShadowMatrix(i));
            }
        }

        int64_t FsPerVertexLightingDiffuseSimpleShadow::GetRequiredAttributesSet() const
        {
            return 0;
        }

    }
}
