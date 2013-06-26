#include "module.h"

namespace GPU
{
    namespace OpenGL
    {
        bool PUNK_ENGINE_API GPU_OPENGL_INIT(const Config& data)
        {
            (void)data;

#ifdef USE_SOLID_COLOR_RC
            {
                DynamicRenderContext* rc = new DynamicRenderContext();
                rc->SetShaders(new VertexShaderSolid, new FragmentShaderSolid, nullptr);
                AbstractRenderPolicy::add(RenderPolicySet::Solid3D, rc);
            }
#endif

#ifdef USE_SOLID_VERTEX_COLOR_RC
            {
                DynamicRenderContext* rc = new DynamicRenderContext();
                rc->SetShaders(new VertexShaderSolidVertexColor, new FragmentShaderSolidVertexColor, nullptr);
                AbstractRenderPolicy::add(RenderPolicySet::SolidVertexColor, rc);
            }
#endif	//	USE_SOLID_VERTEX_COLOR_RC

#ifdef USE_SOLID_TEXTURE_3D_RC
            AbstractRenderPolicy::add(RenderPolicySet::SolidTextured3D, new RenderContextSolidTexture3D());
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
#endif

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
