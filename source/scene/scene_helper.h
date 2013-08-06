#ifndef SCENE_HELPER_H
#define SCENE_HELPER_H

#include "../config.h"
#include "../math/mat4.h"

namespace System { class Object; }

namespace Scene
{
    PUNK_ENGINE_API const Math::mat4 GetGlobalMatrix(const System::Object* object);
}
#endif // SCENE_HELPER_H
