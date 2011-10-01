#ifndef _H_PUNK_SCENE_STORAGE
#define _H_PUNK_SCENE_STORAGE

#include "../system/system.h"
#include "scene_graph.h"

namespace Storage
{
	typedef System::Resource<Scene::SceneGraph> SceneGraphResource;
//	typedef System::ResourceManager<SceneGraphResource, System::RESOURCE_SCENE_GRAPH> SceneGraphManager;
}

#endif