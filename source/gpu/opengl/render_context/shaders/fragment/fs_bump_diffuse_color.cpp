#include "fs_bump_diffuse_color.h"
#include "../gl_shader_type.h"
#include "../../../../../system/environment.h"
#include "../../../../../system/folder.h"
#include "../../rc_dynamic.h"

namespace Gpu
{
    namespace OpenGL
    {
        FsBumpMappingDiffuseColor::FsBumpMappingDiffuseColor()
            : Shader(ShaderType::Fragment)
        {
            System::Folder f;
            f.Open(System::Environment::Instance()->GetShaderFolder());
            const char* names[] = {"/light.glsl", "/material.glsl"};
            CookFromFileWithHeaders(GetShaderFile(ShaderCollection::FragmentBumpMappingDiffuseColor), 2, names);
        }

        void FsBumpMappingDiffuseColor::InitUniforms()
        {
            uMaterial = m_rc->GetUniformaMaterialLocation("uMaterial");
            uLight = m_rc->GetUniformLightLocation("uLight");
            uNormalMap = m_rc->GetUniformLocation("uNormalMap");
        }

        void FsBumpMappingDiffuseColor::BindParameters(const CoreState& params)
        {
            m_rc->SetUniformMaterial(uMaterial, params.batch_state->m_material);
            m_rc->SetUniformLight(uLight, params.light_state->m_lights[0]);
            m_rc->SetUniformInt(uNormalMap, params.texture_state->m_normal_map_slot);
        }

        int64_t FsBumpMappingDiffuseColor::GetRequiredAttributesSet() const
        {
            return 0;
        }
    }
}
