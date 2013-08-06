#ifndef PROCESS_SUN_H
#define PROCESS_SUN_H

namespace System { class Object; }
namespace Scene { class Node; }

namespace Render
{
    class Render2;
    void ProcessSun(Render2* render, Scene::Node* node, System::Object* sun);
}

#endif // PROCESS_SUN_H
