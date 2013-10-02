#include "module.h"
#include "../../system/binary_file.h"
#include "../../system/folder.h"
#include "../../system/environment.h"

namespace Gpu
{
    namespace OpenGL
    {
        void InitVfs(VideoDriverImpl* impl)
        {
            auto vfs = impl->GetVirtualFileSystem();
            {
                System::Folder f;
                f.Open(System::Environment::Instance()->GetShaderFolder());
                System::Buffer buffer;
                System::BinaryFile::Load("light.glsl", buffer); //  TODO: Do something better
                vfs->RegisterNamedString("/light.glsl", (char*)buffer.StartPointer(), buffer.GetSize());
                System::BinaryFile::Load("material.glsl", buffer);
                vfs->RegisterNamedString("/material.glsl", (char*)buffer.StartPointer(), buffer.GetSize());
            }
        }

        bool PUNK_ENGINE_API InitOpenGL(VideoDriverImpl* impl)
        {
            InitVfs(impl);

#ifdef USE_SOLID_COLOR_RC
            {
                DynamicRenderContext* rc = new DynamicRenderContext();
                rc->SetShaders(new VsSolid, new FsSolid, nullptr);
                AbstractRenderPolicy::add(RenderPolicySet::Solid3D, rc);
            }
            {
                DynamicRenderContext* rc = new DynamicRenderContext();
                rc->SetShaders(new VsDepth, new FsDepth, nullptr);
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
                AbstractRenderPolicy::add(RenderPolicySet::SolidTextured2D, rc);
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
            {
                DynamicRenderContext* rc = new DynamicRenderContext();
                rc->SetShaders(new VsPerFragmentLightingDiffuse, new FsPerFragmentLightingDiffuse, nullptr);
                AbstractRenderPolicy::add(RenderPolicySet::LightPerFragmentDiffuse, rc);
            }
            //AbstractRenderPolicy::add(RenderPolicySet::LightPerFragmentDiffuse, new RenderContextPerFragmentDiffuseLight());
#endif	//	USE_LIGHT_PER_VERTEX_DIFFUSE

#ifdef USE_RC_PVRTDL
            {
                DynamicRenderContext* rc = new DynamicRenderContext();
                rc->SetShaders(new VsPerVertexLightingTextureDiffuse, new FsPerVertexLightingTextureDiffuse, nullptr);
                AbstractRenderPolicy::add(RenderPolicySet::LightPerVertexTextureDiffuse, rc);
            }
#endif

#ifdef USE_RC_PFRTDL
            {
                DynamicRenderContext* rc = new DynamicRenderContext();
                rc->SetShaders(new VsPerFragmentLightingTextureDiffuse, new FsPerFragmentLightingTextureDiffuse, nullptr);
                AbstractRenderPolicy::add(RenderPolicySet::LightPerFragmentTextureDiffuse, rc);
            }
#endif

#ifdef USE_BUMP_MAPPING_RC
            {
                DynamicRenderContext* rc = new DynamicRenderContext();
                rc->SetShaders(new VsBumpMappingTextureDiffuse, new FsBumpMappingTextureDiffuse, nullptr);
                AbstractRenderPolicy::add(RenderPolicySet::BumpMappingTextureDiffuse, rc);
            }
#   ifdef USE_SHADOW_MAPS
//            {
//                DynamicRenderContext* rc = new DynamicRenderContext();
//                rc->SetShaders(new VsBumpShadowMap, new FsBumpShadowMap, nullptr);
//                AbstractRenderPolicy::add(RenderPolicySet::BumpMappingShadowingSingle, rc);
//            }
#   endif  //   USE_SHADOW_MAPS
#endif

#ifdef USE_SKINNING_RC
            {
#   ifdef USE_BUMP_MAPPING_RC
                DynamicRenderContext* rc = new DynamicRenderContext();
                rc->SetShaders(new VsSkinningBump, new FsBumpMappingTextureDiffuse, nullptr);
                AbstractRenderPolicy::add(RenderPolicySet::BumpMappingTextureDiffuseSkinning, rc);
#   endif   //  USE_BUMP_MAPPING_RC                               
            }
            {
                DynamicRenderContext* rc = new DynamicRenderContext();
                rc->SetShaders(new VsSkinningDepth, new FsDepth, nullptr);
                AbstractRenderPolicy::add(RenderPolicySet::DepthRenderSkinning, rc);
            }
#endif  //  USE_SKINNING_RC

            {
                DynamicRenderContext* rc = new DynamicRenderContext();
                rc->SetShaders(new VsTexture3D, new FsTextSolid, nullptr);
                AbstractRenderPolicy::add(RenderPolicySet::TextSolidColor, rc);
            }

            {
                DynamicRenderContext* rc = new DynamicRenderContext();
                rc->SetShaders(new VsPerVertexLightingDiffuseShadowSimple, new FsPerVertexLightingDiffuseSimpleShadow, nullptr);
                AbstractRenderPolicy::add(RenderPolicySet::LightPerVertexTextureDiffuseShadowingSimple, rc);
            }

            {
                DynamicRenderContext* rc = new DynamicRenderContext();
                rc->SetShaders(new VsTexture3D, new FsSolidTextured2DArray, nullptr);
                AbstractRenderPolicy::add(RenderPolicySet::SolidTextured2DArray, rc);
            }

            {
                DynamicRenderContext* rc = new DynamicRenderContext();
                rc->SetShaders(new VsPerVertexLightingDiffuseShadowSimple, new FsPerVertexLightingDiffuseSimpleShadow, nullptr);
                AbstractRenderPolicy::add(RenderPolicySet::LightPerVertexDiffuseShadowingSimple, rc);
            }

            {
                DynamicRenderContext* rc = new DynamicRenderContext();
                rc->SetShaders(new VsPerFragmentLightingDiffuseSpecular, new FsPerFragmentLightingDiffuseSpecular, nullptr);
                AbstractRenderPolicy::add(RenderPolicySet::LightPerFragmentDiffuseSpecular, rc);
            }

            {
                DynamicRenderContext* rc = new DynamicRenderContext();
                rc->SetShaders(new VsPerFragmentLightingTextureDiffuseSpecular, new FsPerFragmentLightingTextureDiffuseSpecular, nullptr);
                AbstractRenderPolicy::add(RenderPolicySet::LightPerFragmentTextureDiffuseSpecular, rc);
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

        bool PUNK_ENGINE_API DestroyOpenGL()
        {
            for (auto it = AbstractRenderPolicy::_begin(); it != AbstractRenderPolicy::_end(); ++it)
                safe_delete(it->second);
            AbstractRenderPolicy::clear();
            return true;
        }
    }
}
