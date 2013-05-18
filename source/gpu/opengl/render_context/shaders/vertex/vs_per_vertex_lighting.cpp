#include "vs_per_vertex_lighting.h"
#include "../shader_type.h"
#include "../../../../../system/environment.h"
#include "../../rc_dynamic.h"

namespace GPU
{
	namespace OpenGL
	{
        VsPerVertexLighting::VsPerVertexLighting()
			: Shader(ShaderType::Vertex)
		{
			CookFromFile(System::Environment::Instance()->GetShaderFolder()
                         + GetShaderFile(ShaderCollection::VertexLightPerVertexDiffuse));
		}

        void VsPerVertexLighting::InitUniforms()
		{
            uNormalMatrix = m_rc->GetUniformLocation("uNormalMatrix");
            uView = m_rc->GetUniformLocation("uView");
            uWorld = m_rc->GetUniformLocation("uWorld");
            uProj = m_rc->GetUniformLocation("uProj");
            uLightPosition = m_rc->GetUniformLocation("uLightPosition");
            uDiffuse = m_rc->GetUniformLocation("uDiffuse");
		}

        void VsPerVertexLighting::BindParameters(const CoreState& params)
		{
            auto m = (params.m_view * params.m_world).Inversed().Transposed().RotationPart();
            m_rc->SetUniformMatrix4f(uNormalMatrix, m);
            m_rc->SetUniformMatrix4f(uView, params.m_view);
            m_rc->SetUniformMatrix4f(uWorld, params.m_world);
            m_rc->SetUniformMatrix4f(uProj, params.m_projection);
            m_rc->SetUniformVector4f(uLightPosition, params.m_lights[0].GetPosition());
            m_rc->SetUniformVector4f(uDiffuse, params.m_lights[0].GetDiffuseColor());
		}

        int64_t VsPerVertexLighting::GetRequiredAttributesSet() const
		{
			return VertexComponent::Position::Value();
		}
	}
}
