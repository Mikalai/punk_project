#include "../../scene/module.h"
#include "../../system/module.h"
#include "parse_functions.h"

namespace Utility
{
    System::Object* LoadWorld(const System::string& path)
    {
        System::Buffer buffer;
        System::BinaryFile::Load(path, buffer);
        std::unique_ptr<Scene::SceneGraph> scene(new Scene::SceneGraph);
        ParseWorld(buffer, scene.get());
        scene->SetActiveCamera(new Virtual::Camera());
        return scene.release();
    }
}
