#include "scene_helper.h"
#include "../system/object.h"
#include "node.h"
#include "../virtual/module.h"

namespace Scene
{
    const Math::mat4 GetGlobalMatrix(const System::Object* object)
    {
        Math::mat4 res;
        if (object->GetOwner() == nullptr)
            return res;
        std::vector<const Virtual::Transform*> transforms;
        const System::Object* owner = object;
        while (1)
        {
            if (!owner)
                break;
            const Scene::Node* transform = As<const Scene::Node*>(owner);
            if (transform)
            {
                const System::Object* data = transform->GetData();
                if (data && data->GetType()->IsEqual(&Virtual::Transform::Info.Type))
                    transforms.push_back((Virtual::Transform*)transform->GetData());
            }
            owner = owner->GetOwner();
        }
        for (auto it = transforms.rbegin(); it != transforms.rend(); ++it)
        {
            res *= (*it)->Get();
        }
        return res;
    }
}
