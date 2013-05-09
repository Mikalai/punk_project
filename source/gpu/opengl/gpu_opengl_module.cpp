#include "module.h"

namespace GPU
{
	namespace OpenGL
	{
		bool PUNK_ENGINE GPU_OPENGL_INIT(const Config& data)
		{
			(void)data;

#ifdef USE_SOLID_COLOR_RC
			AbstractRenderPolicy::add(RenderPolicySet::RC_SOLID_3D, new RenderContextSolid3D());
#endif

#ifdef USE_SOLID_VERTEX_COLOR_RC
			AbstractRenderPolicy::add(RenderPolicySet::RC_SOLID_VERTEX_COLOR, new RenderContextSolidVertexColor3D);
#endif	//	USE_SOLID_VERTEX_COLOR_RC

#ifdef USE_SOLID_TEXTURE_3D_RC
			AbstractRenderPolicy::add(RenderPolicySet::RC_SOLID_TEXTURED_3D, new RenderContextSolidTexture3D());
#endif	//	USE_SOLID_TEXTURE_3D_RC

#ifdef USE_LIGHT_PER_VERTEX_DIFFUSE
			AbstractRenderPolicy::add(RenderPolicySet::RC_LIGHT_PER_VERTEX_DIFFUSE, new RenderContextPerVertexDiffuseLight());
#endif	//	USE_LIGHT_PER_VERTEX_DIFFUSE

#ifdef USE_LIGHT_PER_FRAGMENT_DIFFUSE
			AbstractRenderPolicy::add(RenderPolicySet::RC_LIGHT_PER_FRAGMENT_DIFFUSE, new RenderContextPerFragmentDiffuseLight());
#endif	//	USE_LIGHT_PER_VERTEX_DIFFUSE

#ifdef USE_BUMP_MAPPING_RC
			AbstractRenderPolicy::add(RenderPolicySet::RC_BUMP_MAPING, new RenderContextBumpMapping());
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

		bool PUNK_ENGINE GPU_OPENGL_DESTROY()
		{
			for (auto it = AbstractRenderPolicy::_begin(); it != AbstractRenderPolicy::_end(); ++it)
				safe_delete(it->second);
			AbstractRenderPolicy::clear();
			return true;
		}
	}
}
