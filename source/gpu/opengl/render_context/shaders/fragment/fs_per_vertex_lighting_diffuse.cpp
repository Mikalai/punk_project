#include "fs_per_vertex_lighting_diffuse.h"
#include "../shader_type.h"
#include "../../../../../system/environment.h"
#include "../../rc_dynamic.h"

namespace GPU
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
            m_rc->SetUniformVector4f(uDiffuseColor, params.m_diffuse_color);
        }

        int64_t FsPerVertexLightingDiffuse::GetRequiredAttributesSet() const
        {
            return 0;
        }
    }
}
