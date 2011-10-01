#ifndef PUNK_SCENE_RENDER_H
#define PUNK_SCENE_RENDER_H

#include "config.h"
#include "../scene/scene.h"

namespace Render
{
	class LIB_RENDER SceneRenderVisitor
	{
	public:

		void operator () (System::Descriptor desc);
	};

	class LIB_RENDER SceneRender
	{
	public:
		void Renderer(const Scene::SceneGraph& graph);
	};
}

#endif