#include "scene_graph.h"
#include "scene_events.h"
#include <algorithm>

namespace Scene
{
	typedef std::map<System::Descriptor, System::Descriptor> HashTable;
	HashTable g_hash_map;	// contains information about all parents connection


	SceneGraph::SceneGraph()
	{
		m_parent = System::Descriptor::Null();
	}

	SceneGraph::~SceneGraph()
	{
	}

	void SceneGraph::AddInstance(System::Descriptor parent, System::Descriptor instance)
	{
		m_scene[parent].push_back(instance);
		m_hash[instance] = parent;
	}

	void SceneGraph::OnInstanceChangedParent(System::Event* event)
	{
		Scene::ParentChangedEvent* e = static_cast<Scene::ParentChangedEvent*>(event);
		
		//
		//	remove instance from parent
		//
		if (e->old_parent != System::Descriptor::Null())
		{
			Collection& col = m_scene.at(e->old_parent);
			Collection::iterator i = std::find(col.begin(), col.end(), e->instance);
			if (i != col.end())
				col.erase(i);
		}

		//
		//	add to new parent
		//
		if (e->new_parent != System::Descriptor::Null())
		{
			Collection& col = m_scene.at(e->new_parent);
			col.push_back(e->instance);
		}
	}

	void SceneGraph::OnNewInstanceAppeared(System::Event* event)
	{
	}
}