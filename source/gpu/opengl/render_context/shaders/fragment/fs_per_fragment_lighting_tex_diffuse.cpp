#include <sstream>
#include "fs_per_fragment_lighting_tex_diffuse.h"
#include "../gl_shader_type.h"
#include "../../../../../system/environment.h"
#include "../../rc_dynamic.h"

namespace Gpu
{
    namespace OpenGL
    {
        FsPerFragmentLightingTextureDiffuse::FsPerFragmentLightingTextureDiffuse()
            : Shader(ShaderType::Fragment)
        {
            CookFromFile(System::Environment::Instance()->GetShaderFolder()
                         + System::string(GetShaderFile(ShaderCollection::FragmentLightPerFragmentTextureDiffuse)));
        }

        void FsPerFragmentLightingTextureDiffuse::InitUniforms()
        {
            uView = m_rc->GetUniformLocation("uView");
            uDiffuseColor = m_rc->GetUniformLocation("uDiffuseColor");
            uDiffuseMap = m_rc->GetUniformLocation("uDiffuseMap");            
            for (int i = 0; i != MAX_LIGHTS; ++i)
            {
                std::stringstream stream;
                stream << "uLight[" << i << "]";
                uLight[i] = m_rc->GetUniformLightLocation(stream.str().c_str());
            }
        }

        void FsPerFragmentLightingTextureDiffuse::BindParameters(const CoreState& params)
        {
            m_rc->SetUniformVector4f(uDiffuseColor, params.batch_state->m_material.m_diffuse_color);            
            m_rc->SetUniformInt(uDiffuseMap, params.texture_state->m_diffuse_slot[0]);

            for (unsigned i = 0; i != params.light_state->m_used_lights; ++i)
            {
                m_rc->SetUniformLight(uLight[i], params.light_state->m_lights[i]);
            }
        }

        int64_t FsPerFragmentLightingTextureDiffuse::GetRequiredAttributesSet() const
        {
            return 0;
        }
    }
}
