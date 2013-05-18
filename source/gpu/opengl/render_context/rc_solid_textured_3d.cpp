#ifdef USE_SOLID_TEXTURE_3D_RC

#include "rc_solid_textured_3d.h"
#include "gl_render_context.h"
#include "../gl/module.h"
#include "../../common/vertex.h"

namespace GPU
{
	namespace OpenGL
	{

		RenderContextPolicy<
				ShaderCollection::VertexSolidTextured,
				ShaderCollection::FragmentSolidTextured,
				ShaderCollection::No>::RenderContextPolicy()
			: OpenGLRenderContext(ShaderCollection::VertexSolidTextured,
									ShaderCollection::FragmentSolidTextured,
									ShaderCollection::No)

		{
			Init();
		}

		RenderContextPolicy<
				ShaderCollection::VertexSolidTextured,
				ShaderCollection::FragmentSolidTextured,
				ShaderCollection::No>::~RenderContextPolicy()
		{
		}

		void RenderContextPolicy<
				ShaderCollection::VertexSolidTextured,
				ShaderCollection::FragmentSolidTextured,
				ShaderCollection::No>::InitUniforms()
		{
			uProjViewWorld = GetUniformLocation("uProjViewWorld");
			uDiffuseMap = GetUniformLocation("uDiffuseMap");
			uTextureMatrix = GetUniformLocation("uTextureMatrix");
			uDiffuseColor = GetUniformLocation("uDiffuseColor");
		}

		void RenderContextPolicy<
				ShaderCollection::VertexSolidTextured,
				ShaderCollection::FragmentSolidTextured,
				ShaderCollection::No>::BindParameters(const CoreState& params)
		{									
			const Math::mat4 proj_view_world = params.m_projection * params.m_view * params.m_world;
			SetUniformMatrix4f(uProjViewWorld, &(proj_view_world[0]));
			SetUniformInt(uDiffuseMap, 0);
			SetUniformMatrix4f(uTextureMatrix, &params.m_texture_matrix[0]);
			SetUniformVector4f(uDiffuseColor, &params.m_diffuse_color[0]);

			SetUpOpenGL(params);
		}

		int64_t RenderContextPolicy<
				ShaderCollection::VertexSolidTextured,
				ShaderCollection::FragmentSolidTextured,
				ShaderCollection::No>::GetRequiredAttributesSet() const
		{
			return Vertex<VertexComponent::Position, VertexComponent::Texture0>::Value();
		}	
	}
}

#endif  //    USE_SOLID_TEXTURE_RC
