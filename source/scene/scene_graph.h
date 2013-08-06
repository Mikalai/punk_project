#ifndef _H_PUNK_SCENE_MAIN_HEADER
#define _H_PUNK_SCENE_MAIN_HEADER

#include "node.h"

namespace Scene
{
    class PUNK_ENGINE_API SceneGraph : public Node
	{
	public:
        SceneGraph();
        SceneGraph(const SceneGraph&) = delete;
        SceneGraph& operator = (const SceneGraph&) = delete;
        virtual const System::string ToString() const;
		virtual ~SceneGraph();

    public:

        PUNK_OBJECT(SceneGraph)
	};
}

#endif	//	_H_PUNK_SCENE_MAIN_HEADER
