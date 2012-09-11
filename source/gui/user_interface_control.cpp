#include "user_interface_control.h"
#include "../system/system.h"
#include "widget.h"
#include <map>

namespace GUI
{
	struct UserInterface::UserInterfaceImpl
	{
		typedef std::map<System::Descriptor, std::tr1::shared_ptr<Widget>> WidgetCollection;
		WidgetCollection widgets;
		Widget* m_current;
		Widget* m_focused;
	};

	UserInterface::UserInterface() : m_scene_graph(0), m_active(0)
	{
	}

	void UserInterface::SetSceneGraph(Scene::SceneGraph* sg)
	{
		m_scene_graph = sg;
	}

	System::Descriptor UserInterface::CreateLayer()
	{
		if (!m_scene_graph)
			throw System::SystemError(L"SceneGraph not set");

		System::Resource<Widget>* rw = new System::Resource<Widget>();	
		System::Descriptor desc = System::ResourceManager::Instance()->ManageResource<System::RESOURCE_WIDGET>(rw);
		m_scene_graph->Add(System::Descriptor::Root(), desc);
		m_layers.push_back(desc);
		m_active = desc;
		return desc;
	}

	void UserInterface::SetActiveLayer(System::Descriptor desc)
	{
		if (std::find(m_layers.begin(), m_layers.end(), desc) == m_layers.end())
			throw System::SystemError(L"Unknown layer in UserInterface");
		m_active = desc;
	}

	void UserInterface::AddElement(System::Descriptor parent, System::Descriptor desc)
	{
		if (!m_scene_graph)
			throw System::SystemError(L"SceneGraph not set");

		if (parent == System::Descriptor::Root())
		{
			if (m_active == System::Descriptor::Root())
				throw System::SystemError(L"No layer in UI to add elements");
			m_scene_graph->Add(m_active, desc);
		}
		else
		{
			m_scene_graph->Add(parent, desc);
		}		
	}
}