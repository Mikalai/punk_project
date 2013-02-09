#include "module.h"

namespace GPU
{
	namespace OpenGL
	{
		bool PUNK_ENGINE GPU_OPENGL_INIT(const Config& data)
		{
			AbstractRenderPolicy::add(RenderPolicySet::RC_BUMP_MAPING, System::Proxy<AbstractRenderPolicy>(new RenderContextBumpMapping()));
			AbstractRenderPolicy::add(RenderPolicySet::RC_GUI, System::Proxy<AbstractRenderPolicy>(new RenderContextGUI()));
			AbstractRenderPolicy::add(RenderPolicySet::RC_SKINNING, System::Proxy<AbstractRenderPolicy>(new RenderContextSkinning()));
			AbstractRenderPolicy::add(RenderPolicySet::RC_SOLD_3D, System::Proxy<AbstractRenderPolicy>(new RenderContextSolid3D()));
			AbstractRenderPolicy::add(RenderPolicySet::RC_TERRAIN, System::Proxy<AbstractRenderPolicy>(new RenderContextTerrain()));
			AbstractRenderPolicy::add(RenderPolicySet::RC_TEXTURED_3D, System::Proxy<AbstractRenderPolicy>(new RenderContextSolidTexture3D()));
			AbstractRenderPolicy::validate();
			return true;
		}
	}
}