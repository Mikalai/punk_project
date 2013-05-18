#include "rc_dynamic.h"
#include "shaders/shader.h"

namespace GPU
{
	namespace OpenGL
	{
		DynamicRenderContext::DynamicRenderContext()
		{}

		void DynamicRenderContext::SetShaders(Shader *vs, Shader *fs, Shader *gs)
		{
			if (m_vertex_shader = vs)
				m_vertex_shader->Connect(this);
			if (m_fragment_shader = fs)
				m_fragment_shader->Connect(this);
			if (m_geometry_shader = gs)
				m_geometry_shader->Connect(this);
			Init();
		}

		void DynamicRenderContext::InitUniforms()
		{
			m_vertex_shader->InitUniforms();
			m_fragment_shader->InitUniforms();
			if (m_geometry_shader)
				m_geometry_shader->InitUniforms();
		}

		void DynamicRenderContext::BindParameters(const CoreState& params)
		{
			m_vertex_shader->BindParameters(params);
			m_fragment_shader->BindParameters(params);
			if (m_geometry_shader)
				m_geometry_shader->BindParameters(params);
			SetUpOpenGL(params);
		}

		int64_t DynamicRenderContext::GetRequiredAttributesSet() const
		{
			int64_t result = 0;
			result |= m_vertex_shader->GetRequiredAttributesSet();
			result |= m_fragment_shader->GetRequiredAttributesSet();
			if (m_geometry_shader)
				result |= m_geometry_shader->GetRequiredAttributesSet();
			return result;
		}
	}
}
