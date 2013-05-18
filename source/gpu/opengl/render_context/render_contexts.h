#ifndef _H_PUNK_OPENGL_RENDER_CONTEXT_LOGIC
#define _H_PUNK_OPENGL_RENDER_CONTEXT_LOGIC

#include <memory>
#include "shaders/shaders.h"
#include "../../../config.h"
#include "rc_bump_mapping.h"
#include "rc_grass.h"
#include "rc_gui.h"
#include "rc_particle_system.h"
#include "rc_skinning.h"
#include "rc_solid_textured_3d.h"
#include "rc_terrain.h"
#include "rc_painter.h"
#include "rc_per_vertex_lighting.h"
#include "rc_per_fragment_lighting.h"
#include "rc_pvtdl.h"
#include "rc_pftdl.h"
#include "rc_dynamic.h"

namespace GPU
{
	namespace OpenGL
	{

#ifdef USE_BUMP_MAPPNG_RC
		class PUNK_ENGINE RenderContextBumpMapping final : public RenderContextPolicy<VertexShaderBump, FragmentShaderBump, NoShader> {};
#endif

#ifdef USE_TERRAIN_RC
		class PUNK_ENGINE RenderContextTerrain final : public RenderContextPolicy<VertexShaderTerrain, FragmentShaderTerrain, NoShader> {};
#endif

#ifdef USE_GUI_RC
		class PUNK_ENGINE RenderContextGUI final : public RenderContextPolicy<VertexShaderGUI, FragmentShaderGUI, NoShader> {};
#endif

#ifdef USE_SOLID_TEXTURE_3D_RC
		class PUNK_ENGINE RenderContextSolidTexture3D final
				: public RenderContextPolicy<
				ShaderCollection::VertexSolidTextured,
				ShaderCollection::FragmentSolidTextured,
				ShaderCollection::No> {};
#endif	//	USE_SOLID_TEXTURE_3D_RC

//#ifdef USE_LIGHT_PER_VERTEX_DIFFUSE
//		class PUNK_ENGINE RenderContextPerVertexDiffuseLight final
//				: public RenderContextPolicy<
//				ShaderCollection::VertexLightPerVertexDiffuse,
//				ShaderCollection::FragmentLightPerVertexDiffuse,
//				ShaderCollection::No> {};
//#endif	//	USE_LIGHT_PER_VERTEX_DIFFUSE

//#ifdef USE_RC_PVRTDL
//		class PUNK_ENGINE RenderContextPerVertexTextureDiffuseLight final
//				: public RenderContextPolicy<
//				ShaderCollection::VertexLightPerVertexTextureDiffuse,
//				ShaderCollection::FragmentLightPerVertexTextureDiffuse,
//				ShaderCollection::No> {};
//#endif	//

#ifdef USE_RC_PFRTDL
		class PUNK_ENGINE RenderContextPerFragmentTextureDiffuseLight final
				: public RenderContextPolicy<
				ShaderCollection::VertexLightPerFragmentTextureDiffuse,
				ShaderCollection::FragmentLightPerFragmentTextureDiffuse,
				ShaderCollection::No> {};
#endif	//

#ifdef USE_LIGHT_PER_FRAGMENT_DIFFUSE
		class PUNK_ENGINE RenderContextPerFragmentDiffuseLight final
				: public RenderContextPolicy<
				ShaderCollection::VertexLightPerFragmentDiffuse,
				ShaderCollection::FragmentLightPerFragmentDiffuse,
				ShaderCollection::No> {};
#endif	//	USE_LIGHT_PER_VERTEX_DIFFUSE

#ifdef USE_SKINNING_RC
		class PUNK_ENGINE RenderContextSkinning final : public RenderContextPolicy<VertexShaderSkinning, FragmentShaderSkinning, NoShader> {};
#endif

#ifdef USE_PAINTER_RC
		class PUNK_ENGINE RenderContextPainter final : public RenderContextPolicy<VertexShaderPainter, FragmentShaderPainter, NoShader> {};
#endif

	}
}

#endif
