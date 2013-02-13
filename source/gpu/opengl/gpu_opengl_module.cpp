#include "module.h"

namespace GPU
{
	namespace OpenGL
	{
		bool PUNK_ENGINE GPU_OPENGL_INIT(const Config& data)
		{
			AbstractRenderPolicy::add(RenderPolicySet::RC_BUMP_MAPING, new RenderContextBumpMapping());
			AbstractRenderPolicy::add(RenderPolicySet::RC_GUI, new RenderContextGUI());
			AbstractRenderPolicy::add(RenderPolicySet::RC_SKINNING, new RenderContextSkinning());
			AbstractRenderPolicy::add(RenderPolicySet::RC_SOLD_3D, new RenderContextSolid3D());
			AbstractRenderPolicy::add(RenderPolicySet::RC_TERRAIN, new RenderContextTerrain());
			AbstractRenderPolicy::add(RenderPolicySet::RC_TEXTURED_3D, new RenderContextSolidTexture3D());
			AbstractRenderPolicy::validate();
			return true;
		}

		bool PUNK_ENGINE GPU_OPENGL_DESTROY()
		{
			for (auto it = AbstractRenderPolicy::_begin(); it != AbstractRenderPolicy::_end(); ++it)
				safe_delete(it->second);
			AbstractRenderPolicy::clear();
			CubeObject::Destroy();
			QuadObject::Destroy();
			SphereObject::Destroy();			
			return true;
		}
	}
}