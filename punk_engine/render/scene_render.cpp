#include "scene_render.h"

namespace Render
{
	void SceneRenderVisitor::operator() (System::Descriptor desc)
	{
		switch(desc.Type())
		{
		case System::RESOURCE_GUI:
			//RenderGUIElement(System::ResourceManager::Get
			break;
		}
	}

	void SceneRender::Render(const Scene::SceneGraph& graph)
	{

	}
}