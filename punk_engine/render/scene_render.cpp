#include "../system/system.h"
#include "scene_render.h"

namespace Render
{
	void SceneRenderVisitor::operator() (System::Descriptor desc)
	{
		switch(desc.Type())
		{
		case System::RESOURCE_GUI:
			System::Logger::GetInstance()->WriteMessage(System::string::Format(L"Rendering a something like a widget with instance number %d", desc.Number()));
			//RenderGUIElement(System::ResourceManager::Get
			break;
		}
	}

	void SceneRender::Renderer(const Scene::SceneGraph& graph)
	{

	}
}