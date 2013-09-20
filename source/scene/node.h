#ifndef _H_PUNK_SCENE_NODE
#define _H_PUNK_SCENE_NODE

#include <vector>
#include "../system/compound_object.h"
#include "../string/string.h"
#include "../math/bounding_box.h"
#include "../math/bounding_shere.h"
#include "../math/quat.h"

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
        System::Object* GetOrLoadData();

        size_t GetIndex(const System::string& name) const;
        bool Remove(const System::string& name, bool depth = false);
        Node* Find(const System::string& name, bool in_depth = false);
        const Node* Find(const System::string& name, bool in_depth = false) const;
        std::vector<Node*> FindAll(const System::string& name, bool in_depth, bool strict_compare = true);

        SceneGraph* Graph() const;
        void Graph(SceneGraph* graph);

        void LocalPosition(const Math::vec3& value);
        const Math::vec3& LocalPosition() const;
        Math::vec3& LocalPosition();

        const Math::vec3& GlobalPosition() const;
        Math::vec3& GlobalPosition();

        void LocalRotation(const Math::quat& value);
        const Math::quat& LocalRotation() const;
        Math::quat& LocalRotation();

        const Math::quat& GlobalRotation() const;
        Math::quat& GlobalRotation();

        void LocalScale(const Math::vec3& value);
        const Math::vec3& LocalScale() const;
        Math::vec3& LocalScale();

        const Math::vec3& GlobalScale() const;
        Math::vec3& GlobalScale();

        const Math::mat4 GetLocalMatrix() const;
        const Math::mat3 GetLocalRotationMatrix() const;

        const Math::mat4 GetGlobalMatrix() const;
        const Math::mat3 GetGlobalRotationMatrix() const;

        const Math::vec3 LocalTransform(const Math::vec3& value) const;
        const Math::vec3 LocalInversedTransform(const Math::vec3& value) const;

        const Math::vec3 GlobalTransform(const Math::vec3& value) const;
        const Math::vec3 GlobalInversedTransform(const Math::vec3& value) const;

        void EntityName(const System::string& value);
        const System::string& EntityName() const;

        Utility::AsyncParserTask* Task() const;
        Utility::AsyncParserTask* Task(Utility::AsyncParserTask* value);

        bool NeedTransformUpdate() const;
        void UpdateGlobalTransform();
    private:
        void CloneInternals(Node *dst);
        void LoadObject();
        void UpdateGlobalPosition();
        void UpdateGlobalRotation();
        void UpdateGlobalScale();

    private:
        SceneGraph* m_graph;
        System::Object* m_data;
        System::string m_entity_name;
		Math::BoundingBox m_bbox;
        Math::BoundingSphere m_bsphere;
        Utility::AsyncParserTask* m_task;
        Math::vec3 m_local_position;
        Math::quat m_local_rotation;
        Math::vec3 m_local_scale;
        Math::vec3 m_global_position;
        Math::quat m_global_rotation;
        Math::vec3 m_global_scale;
        bool m_need_transform_update;
    public:
        PUNK_OBJECT(Node)
	};

    void UpdateUpToDown(Node* node);
}

#endif	//	H_PUNK_SCENE_NODE
