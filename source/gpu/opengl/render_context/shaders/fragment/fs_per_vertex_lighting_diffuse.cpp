#include "fs_per_vertex_lighting_diffuse.h"
#include "../gl_shader_type.h"
#include "../../../../../system/environment.h"
#include "../../rc_dynamic.h"

namespace Gpu
{
    namespace OpenGL
    {
        FsPerVertexLightingDiffuse::FsPerVertexLightingDiffuse()
            : Shader(ShaderType::Fragment)
        {
            CookFromFile(System::Environment::Instance()->GetShaderFolder()
                         + GetShaderFile(ShaderCollection::FragmentLightPerVertexDiffuse));
        }

        void FsPerVertexLightingDiffuse::InitUniforms()
        {            
            uDiffuseColor = m_rc->GetUniformLocation("uDiffuseColor");
        }

        void FsPerVertexLightingDiffuse::BindParameters(const CoreState& params)
        {         
            m_rc->SetUniformVector4f(uDiffuseColor, params.batch_state->m_material.m_diffuse_color);
        }

        int64_t FsPerVertexLightingDiffuse::GetRequiredAttributesSet() const
        {
            return 0;
        }
    }
}
