#ifndef PUNK_SCENE_RENDER_H
#define PUNK_SCENE_RENDER_H

#include "config.h"
#include "../system/driver/video/driver.h"
#include "../scene/scene.h"
#include "../gui/gui.h"

namespace Render
{
	class LIB_RENDER SceneRender
	{
		OpenGL::Driver* m_driver;
	public:
		SceneRender();
		void SetVideoDriver(OpenGL::Driver* driver);
		void Renderer(const Scene::SceneGraph& graph);
		
		void WidgetRender(float px, float py, GUI::Widget* widget);
		void ButtonRender(float px, float py, GUI::Button* button);
	};

	
	class LIB_RENDER SceneRenderVisitor
	{
		SceneRender& render;

	public:
		struct Data
		{
			float x;
			float y;
			Data() : x(0), y(0) {}
		};
	public:
		SceneRenderVisitor(SceneRender& render);
		void operator () (System::Descriptor desc, Data& data);
	};

}

#endif