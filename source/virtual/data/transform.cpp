#include "transform.h"
#include "../../utility/descriptors/object_desc.h"
#include "../../system/logger.h"
#include "../../engine_objects.h"
namespace Virtual
{
    PUNK_OBJECT_REG(Transform, "Virtual.Transform", PUNK_TRANSFORM, &System::Object::Info.Type);

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

}
