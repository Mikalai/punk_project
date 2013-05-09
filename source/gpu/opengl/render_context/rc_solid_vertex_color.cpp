#ifdef USE_SOLID_VERTEX_COLOR_RC

#include "rc_solid_vertex_color.h"
#include "gl_render_context.h"
#include "../gl/module.h"
#include "../../common/vertex.h"

namespace GPU
{
	namespace OpenGL
	{
		RenderContextPolicy<
				ShaderCollection::VertexSolidVertexColor,
				ShaderCollection::FragmentSolidVertexColor,
				ShaderCollection::No>::RenderContextPolicy()
			: OpenGLRenderContext(ShaderCollection::VertexSolidVertexColor,
								  ShaderCollection::FragmentSolidVertexColor,
								  ShaderCollection::No)
		{
			Init();
		}

		void RenderContextPolicy<
				ShaderCollection::VertexSolidVertexColor,
				ShaderCollection::FragmentSolidVertexColor,
				ShaderCollection::No>::InitUniforms()
		{
			uProjViewWorld = GetUniformLocation("uProjViewWorld");
		}

		void RenderContextPolicy<
				ShaderCollection::VertexSolidVertexColor,
				ShaderCollection::FragmentSolidVertexColor,
				ShaderCollection::No>::BindParameters(const CoreState& params)
		{
			const Math::mat4 proj_view_world = params.m_projection * params.m_view * params.m_world;
			SetUniformMatrix4f(uProjViewWorld, &proj_view_world[0]);

			SetUpOpenGL(params);
		}

		int64_t RenderContextPolicy<
				ShaderCollection::VertexSolidVertexColor,
				ShaderCollection::FragmentSolidVertexColor,
				ShaderCollection::No>::GetRequiredAttributesSet() const
		{
			return Vertex<VertexComponent::Position, VertexComponent::Color>::Value();
		}
	}
}

#endif  //  USE_SOLID_VERTEX_COLOR_RC
