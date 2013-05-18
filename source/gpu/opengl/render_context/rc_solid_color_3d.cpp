#ifdef USE_SOLID_COLOR_RC

#include "rc_solid_color_3d.h"
#include "gl_render_context.h"
#include "../gl/module.h"
#include "../../common/vertex.h"
#include "shaders/vertex/vs_solid_color.h"
#include "shaders/fragment/fs_solid_color.h"

namespace GPU
{
	namespace OpenGL
	{
        RenderContextPolicy<ShaderCollection::VertexSolidColor, ShaderCollection::FragmentSolidColor, ShaderCollection::No>::RenderContextPolicy()
            : OpenGLRenderContext(ShaderCollection::VertexSolidColor, ShaderCollection::FragmentSolidColor, ShaderCollection::No)
		{
			Init();
		}

        RenderContextPolicy<ShaderCollection::VertexSolidColor, ShaderCollection::FragmentSolidColor, ShaderCollection::No>::~RenderContextPolicy()
		{
		}

        void RenderContextPolicy<ShaderCollection::VertexSolidColor, ShaderCollection::FragmentSolidColor, ShaderCollection::No>::Init()
		{
			if (m_was_modified || !m_program)
			{
				OpenGLRenderContext::Init();
				InitUniforms();
			}
		}

        void RenderContextPolicy<ShaderCollection::VertexSolidColor, ShaderCollection::FragmentSolidColor, ShaderCollection::No>::InitUniforms()
		{
			uProjViewWorld = GetUniformLocation("uProjViewWorld");
			uDiffuseColor = GetUniformLocation("uDiffuseColor");
		}

        void RenderContextPolicy<ShaderCollection::VertexSolidColor, ShaderCollection::FragmentSolidColor, ShaderCollection::No>::BindParameters(const CoreState& params)
		{			
			const Math::mat4 proj_view_world = params.m_projection * params.m_view * params.m_world;
			SetUniformMatrix4f(uProjViewWorld, &proj_view_world[0]);
			SetUniformVector4f(uDiffuseColor, &(params.m_diffuse_color[0]));
			SetUpOpenGL(params);
		}

        int64_t RenderContextPolicy<ShaderCollection::VertexSolidColor, ShaderCollection::FragmentSolidColor, ShaderCollection::No>::GetRequiredAttributesSet() const
		{
			return Vertex<VertexComponent::Position>::Value();
		}

        void RenderContextPolicy<ShaderCollection::VertexSolidColor, ShaderCollection::FragmentSolidColor, ShaderCollection::No>::Begin()
		{
			Init();
			OpenGLRenderContext::Begin();
		}

        void RenderContextPolicy<ShaderCollection::VertexSolidColor, ShaderCollection::FragmentSolidColor, ShaderCollection::No>::End()
		{
			OpenGLRenderContext::End();			
		}		
	}
}

#endif  //  USE_SOLID_COLOR_3D_RC
