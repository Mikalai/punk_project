#ifndef PROCESS_ARMATURE_H
#define PROCESS_ARMATURE_H

namespace Scene { class Node; }
namespace System { class Object; }

namespace Render
{
    class Render2;

    void ProcessArmature(Render2* render, Scene::Node*, System::Object* mixer);
}

#endif // PROCESS_ARMATURE_H
