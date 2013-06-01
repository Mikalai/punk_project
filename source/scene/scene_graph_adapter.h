#ifndef _H_PUNK_SCENE_GRAPH_ADAPTER
#define _H_PUNK_SCENE_GRAPH_ADAPTER

namespace Scene
{
	class SceneGraph;
	class Node;

	class SceneGraphAdapter
	{
	public:
		virtual void OnEnterSceneGraph(SceneGraph* graph, Node* node) = 0;
		virtual void OnLeaveSceneGraph(SceneGraph* graph) = 0;
		virtual void OnEnterVisibility() = 0;
		virtual void OnLostVisibility() = 0;
	};

}

#endif	//	_H_PUNK_SCENE_GRAPH_ADAPTER