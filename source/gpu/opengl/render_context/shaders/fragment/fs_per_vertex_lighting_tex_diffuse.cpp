#include "fs_per_vertex_lighting_tex_diffuse.h"
#include "../gl_shader_type.h"
#include "../../../../../system/environment.h"
#include "../../rc_dynamic.h"

namespace Gpu
{
    namespace OpenGL
    {
        FsPerVertexLightingTextureDiffuse::FsPerVertexLightingTextureDiffuse()
            : Shader(ShaderType::Fragment)
        {
            CookFromFile(System::Environment::Instance()->GetShaderFolder()
                         + GetShaderFile(ShaderCollection::FragmentLightPerVertexTextureDiffuse));
        }

        void FsPerVertexLightingTextureDiffuse::InitUniforms()
        {            
            uDiffuseColor = m_rc->GetUniformLocation("uDiffuseColor");
            uDiffuseMap = m_rc->GetUniformLocation("uDiffuseMap");
        }

        void FsPerVertexLightingTextureDiffuse::BindParameters(const CoreState& params)
        {
            m_rc->SetUniformVector4f(uDiffuseColor, params.batch_state->m_material.m_diffuse_color);
            m_rc->SetUniformInt(uDiffuseMap, params.texture_state->m_diffuse_slot[0]);
        }

        int64_t FsPerVertexLightingTextureDiffuse::GetRequiredAttributesSet() const
        {
            return 0;
        }
    }
}
