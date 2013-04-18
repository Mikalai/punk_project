#ifndef _H_PUNK_OPENGL_RENDER_CONTEXT_LOGIC
#define _H_PUNK_OPENGL_RENDER_CONTEXT_LOGIC

#include <memory>
#include "../../../config.h"
#include "rc_bump_mapping.h"
#include "rc_grass.h"
#include "rc_gui.h"
#include "rc_particle_system.h"
#include "rc_skinning.h"
#include "rc_solid_color_3d.h"
#include "rc_solid_textured_3d.h"
#include "rc_terrain.h"
#include "rc_painter.h"

namespace GPU
{
	namespace OpenGL
	{
		class PUNK_ENGINE RenderContextSolidTexture3D final : public RenderContextPolicy<VertexShaderTransformTextured3D, FragmentShaderSolidTextured, NoShader> {};
		class PUNK_ENGINE RenderContextBumpMapping final : public RenderContextPolicy<VertexShaderBump, FragmentShaderBump, NoShader> {};
		class PUNK_ENGINE RenderContextTerrain final : public RenderContextPolicy<VertexShaderTerrain, FragmentShaderTerrain, NoShader> {};
		class PUNK_ENGINE RenderContextGUI final : public RenderContextPolicy<VertexShaderGUI, FragmentShaderGUI, NoShader> {};
		class PUNK_ENGINE RenderContextSolid3D final : public RenderContextPolicy<VertexShaderSolid, FragmentShaderSolid, NoShader> {};
		class PUNK_ENGINE RenderContextSkinning final : public RenderContextPolicy<VertexShaderSkinning, FragmentShaderSkinning, NoShader> {};
		class PUNK_ENGINE RenderContextPainter final : public RenderContextPolicy<VertexShaderPainter, FragmentShaderPainter, NoShader> {};
	}
}

#endif
