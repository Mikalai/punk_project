#ifndef PUNK_SCENE_RENDER_H
#define PUNK_SCENE_RENDER_H

#include "../scene/scene.h"

namespace Render
{
	class SceneRenderVisitor
	{
	public:
		void operator () (System::Descriptor desc);
	};

	class SceneRender
	{
	public:
		void Render(const Scene::SceneGraph& graph);
	};
}

#endif