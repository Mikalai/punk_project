#include "transform.h"
#include "../../utility/descriptors/object_desc.h"
#include "../../system/logger.h"
#include "../../engine_objects.h"

namespace Virtual
{
    PUNK_OBJECT_REG(Transform, "Virtual.Transform", PUNK_TRANSFORM, SaveTransform, LoadTransform, &System::Object::Info.Type);

	Transform::Transform(const Math::mat4& m)
	{
		m_transform = m;
        Info.Add(this);
	}

    Transform::Transform()
    {
        Info.Add(this);
    }

	Transform::~Transform()
    {
        Info.Remove(this);
    }

    void SaveTransform(System::Buffer* buffer, const System::Object* o)
    {
        System::SaveObject(buffer, o);
        const Transform* t = Cast<const Transform*>(o);
        Math::SaveMatrix4f(buffer, t->m_transform);
    }

    void LoadTransform(System::Buffer* buffer, System::Object* o)
    {
        System::LoadObject(buffer, o);
        Transform* t = Cast<Transform*>(o);
        Math::LoadMatrix4f(buffer, t->m_transform);
    }
}
