#ifndef PROCESS_MATERIAL_H
#define PROCESS_MATERIAL_H

namespace System { class Object; }
namespace Scene { class Node; }

namespace Render
{
    class Render2;

    void ProcessMaterial(Render2* render, Scene::Node* node, System::Object* value);
}

#endif // PROCESS_MATERIAL_H
