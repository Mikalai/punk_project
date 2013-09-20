//#include "../engine_objects.h"
//#include "transformnode.h"

//namespace Scene
//{
//    System::StaticInormation<TransformNode> TransformNode::Info{"System.TransformNode", PUNK_TRANSFORM_NODE, &System::CompoundObject::Info.Type};

//    TransformNode::TransformNode(TransformNode *parent)
//        : m_parent(parent)
//        , m_index(-1)
//    {
//        Info.Add(this);
//    }

//    TransformNode::~TransformNode()
//    {
//        Info.Remove(this);
//    }

//    void TransformNode::ObjectIndex(unsigned value)
//    {
//        m_index = value;
//    }

//    unsigned TransformNode::ObjectIndex() const
//    {
//        m_index;
//    }

//    void TransformNode::Position(const Math::vec3& value)
//    {
//        m_position = value;
//    }

//    const Math::vec3& TransformNode::Position() const
//    {
//        return m_position;
//    }

//    Math::vec3& TransformNode::Position()
//    {
//        return m_position;
//    }

//    void TransformNode::Rotation(const Math::quat& value)
//    {
//        m_rotation = value;
//    }

//    const Math::quat& TransformNode::Rotation() const
//    {
//        return m_rotation;
//    }

//    Math::quat& TransformNode::Rotation()
//    {
//        return m_rotation;
//    }

//    void TransformNode::Scale(const Math::vec3& value)
//    {
//        m_scale = value;
//    }

//    const Math::vec3& TransformNode::Scale() const
//    {
//        return m_scale;
//    }

//    Math::vec3& TransformNode::Scale()
//    {
//        return m_scale;
//    }

//    const Math::mat4 TransformNode::ToMatrix() const
//    {
//        return Math::mat4::CreateTranslate(m_position)*Math::mat4::CreateFromQuaternion(m_rotation);
//    }

//    const Math::mat3 TransformNode::ToRotationMatrix() const
//    {
//        return Math::mat3::CreateFromQuaternion(m_rotation);
//    }

//    const Math::vec3 TransformNode::Transform(const Math::vec3& value) const
//    {
//        return m_rotation.Rotate(value) + m_position;
//    }

//    const Math::vec3 TransformNode::InversedTransform(const Math::vec3& value) const
//    {
//        Math::quat q(m_rotation.Conjugated());
//        return q.Rotate(value - m_position);
//    }

//    void TransformNode::Name(const System::string& value)
//    {
//        m_name = value;
//    }

//    const System::string& TransformNode::Name() const
//    {
//        return m_name;
//    }

//    void TransformNode::EntityName(const System::string& value)
//    {
//        m_entity_name = value;
//    }

//    const System::string& TransformNode::EntityName() const
//    {
//        return m_entity_name;
//    }

//    const System::string TransformNode::ToString() const
//    {
//        std::wstringstream stream;
//        stream << m_name << std::endl;
//        stream << m_position.ToString() << std::endl;
//        stream << m_rotation.ToString() << std::endl;
//        stream << m_entity_name << std::endl;
//        stream << CompoundObject::ToString() << std::endl;
//        return System::string(stream.str().c_str());
//    }
//}
