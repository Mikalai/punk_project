#ifndef _H_PUNK_SCENE_MAIN_HEADER
#define _H_PUNK_SCENE_MAIN_HEADER

#include "node.h"

namespace Virtual { class Light; }
namespace Utility { class AsyncParser; }

namespace Scene
{
    class PUNK_ENGINE_API SceneGraph : public Node
	{
	public:
        SceneGraph();
        SceneGraph(const SceneGraph&) = delete;
        SceneGraph& operator = (const SceneGraph&) = delete;        
		virtual ~SceneGraph();

        virtual const System::string ToString() const override;

        Utility::AsyncParser* AsyncParser();

        const std::vector<Node*>& GetLights() { return m_lights; }

        void Update();

        Node* GetNearestLight(const Math::vec3& point) const;

    private:

        void UpdateTransform();
        void UpdateLights();

        Utility::AsyncParser* m_parser;
        std::vector<Node*> m_lights;

    public:

        PUNK_OBJECT(SceneGraph)
	};

    PUNK_OBJECT_UTIL(SceneGraph)
}

#endif	//	_H_PUNK_SCENE_MAIN_HEADER
