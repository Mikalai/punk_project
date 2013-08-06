#include "module.h"

namespace Gpu
{
    namespace OpenGL
    {
        bool PUNK_ENGINE_API GPU_OPENGL_INIT(const Config& data)
        {
            (void)data;

#ifdef USE_SOLID_COLOR_RC
            {
                DynamicRenderContext* rc = new DynamicRenderContext();
                rc->SetShaders(new VsSolid, new FsShaderSolid, nullptr);
                AbstractRenderPolicy::add(RenderPolicySet::Solid3D, rc);
            }
            {
                DynamicRenderContext* rc = new DynamicRenderContext();
                rc->SetShaders(new VsSolid, new FsDepth, nullptr);
                AbstractRenderPolicy::add(RenderPolicySet::DepthRender, rc);
            }
#endif

#ifdef USE_SOLID_VERTEX_COLOR_RC
            {
                DynamicRenderContext* rc = new DynamicRenderContext();
                rc->SetShaders(new VsSolidVertexColor, new FsSolidVertexColor, nullptr);
                AbstractRenderPolicy::add(RenderPolicySet::SolidVertexColor, rc);
            }
#endif	//	USE_SOLID_VERTEX_COLOR_RC

#ifdef USE_SOLID_TEXTURE_3D_RC
            {
                DynamicRenderContext* rc = new DynamicRenderContext();
                rc->SetShaders(new VsTexture3D, new FsSolidTextured3D, nullptr);
                AbstractRenderPolicy::add(RenderPolicySet::SolidTextured3D, rc);
            }
#endif	//	USE_SOLID_TEXTURE_3D_RC

#ifdef USE_LIGHT_PER_VERTEX_DIFFUSE
            {
                DynamicRenderContext* rc = new DynamicRenderContext();
                rc->SetShaders(new VsPerVertexLightingDiffuse(), new FsPerVertexLightingDiffuse(), nullptr);
                AbstractRenderPolicy::add(RenderPolicySet::LightPerVertexDiffuse, rc);
            }
#endif	//	USE_LIGHT_PER_VERTEX_DIFFUSE

#ifdef USE_LIGHT_PER_FRAGMENT_DIFFUSE
            AbstractRenderPolicy::add(RenderPolicySet::LightPerFragmentDiffuse, new RenderContextPerFragmentDiffuseLight());
#endif	//	USE_LIGHT_PER_VERTEX_DIFFUSE

#ifdef USE_RC_PVRTDL
            {
                DynamicRenderContext* rc = new DynamicRenderContext();
                rc->SetShaders(new VsPerVertexLightingTextureDiffuse, new FsPerVertexLightingTextureDiffuse, nullptr);
                AbstractRenderPolicy::add(RenderPolicySet::LightPerVertexTextureDiffuse, rc);
            }
#endif

#ifdef USE_RC_PFRTDL
            AbstractRenderPolicy::add(RenderPolicySet::LightPerFragmentTextureDiffuse, new RenderContextPerFragmentTextureDiffuseLight());
#endif

#ifdef USE_BUMP_MAPPING_RC
            {
                DynamicRenderContext* rc = new DynamicRenderContext();
                rc->SetShaders(new VsBumpMapping, new FsBumpMapping, nullptr);
                AbstractRenderPolicy::add(RenderPolicySet::BumpMapping, rc);
            }
#   ifdef USE_SHADOW_MAPS
            {
                DynamicRenderContext* rc = new DynamicRenderContext();
                rc->SetShaders(new VsBumpShadowMap, new FsBumpShadowMap, nullptr);
                AbstractRenderPolicy::add(RenderPolicySet::BumpMappingShadowing, rc);
            }
#   endif  //   USE_SHADOW_MAPS
#endif

#ifdef USE_SKINNING_RC
            {
#   ifdef USE_BUMP_MAPPING_RC
                DynamicRenderContext* rc = new DynamicRenderContext();
                rc->SetShaders(new VsSkinning, new FsBumpMapping, nullptr);
                AbstractRenderPolicy::add(RenderPolicySet::BumpMappingSkinning, rc);
#   endif   //  USE_BUMP_MAPPING_RC                               
            }
            {
                DynamicRenderContext* rc = new DynamicRenderContext();
                rc->SetShaders(new VsSkinning, new FsDepth, nullptr);
                AbstractRenderPolicy::add(RenderPolicySet::DepthRenderSkinning, rc);
            }
#endif  //  USE_SKINNING_RC

            {
                DynamicRenderContext* rc = new DynamicRenderContext();
                rc->SetShaders(new VsTexture3D, new FsTextSolid, nullptr);
                AbstractRenderPolicy::add(RenderPolicySet::TextSolidColor, rc);
            }
#ifdef USE_GUI_RC
            AbstractRenderPolicy::add(RenderPolicySet::RC_GUI, new RenderContextGUI());
#endif

#ifdef USE_SKINNIG_RC
            AbstractRenderPolicy::add(RenderPolicySet::RC_SKINNING, new RenderContextSkinning());
#endif

#ifdef USE_TERRAIN_RC
            AbstractRenderPolicy::add(RenderPolicySet::RC_TERRAIN, new RenderContextTerrain());
#endif

#ifdef USE_PAINTER_RC
            AbstractRenderPolicy::add(RenderPolicySet::RC_PAINTER, new RenderContextPainter());
#endif

            AbstractRenderPolicy::validate();
            return true;
        }

        bool PUNK_ENGINE_API GPU_OPENGL_DESTROY()
        {
            for (auto it = AbstractRenderPolicy::_begin(); it != AbstractRenderPolicy::_end(); ++it)
                safe_delete(it->second);
            AbstractRenderPolicy::clear();
            return true;
        }
    }
}
