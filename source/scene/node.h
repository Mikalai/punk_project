#ifndef _H_PUNK_SCENE_NODE
#define _H_PUNK_SCENE_NODE

#include <vector>
#include "../system/compound_object.h"
#include "../string/string.h"
#include "../math/bounding_box.h"
#include "../math/bounding_shere.h"

namespace Utility { class AsyncParserTask; }
namespace Virtual { class Entity; }

namespace Scene
{
    class SceneGraph;

	class PUNK_ENGINE_API Node : public System::CompoundObject
	{
    public:
        using System::CompoundObject::Remove;
        using System::CompoundObject::Find;
	public:

        Node();
        Node(const Node&) = delete;
        Node& operator = (const Node&) = delete;
        virtual const System::string ToString() const;
		virtual ~Node();		

		void SetBoundingBox(const Math::BoundingBox& bbox) { m_bbox = bbox; }
		const Math::BoundingBox& GetBoundingBox() const { return m_bbox; }

		void SetBoundingSphere(const Math::BoundingSphere& value) { m_bsphere = value; }
		const Math::BoundingSphere& GetBoundingSphere() const { return m_bsphere; }

        virtual Node* Clone();

        void SetData(System::Object* value);
        System::Object* GetData();
        const System::Object* GetData() const;

        void SetName(const System::string& value);
        const System::string& GetName() const;

        size_t GetIndex(const System::string& name) const;
        bool Remove(const System::string& name, bool depth = false);
        Node* Find(const System::string& name, bool in_depth = false);
        const Node* Find(const System::string& name, bool in_depth = false) const;
        std::vector<Node*> FindAll(const System::string& name, bool in_depth, bool strict_compare = true);

        SceneGraph* GetSceneGraph() const;

        Utility::AsyncParserTask* Task() const;
        Utility::AsyncParserTask* Task(Utility::AsyncParserTask* value);

    private:
        void CloneInternals(Node *dst);

    private:
        System::string m_name;
        System::Object* m_data;
		Math::BoundingBox m_bbox;
        Math::BoundingSphere m_bsphere;
        Utility::AsyncParserTask* m_task;
        SceneGraph* m_graph;
    public:
        PUNK_OBJECT(Node)
	};
}

#endif	//	H_PUNK_SCENE_NODE
