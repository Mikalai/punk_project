#ifndef PROCESS_LIGHT_H
#define PROCESS_LIGHT_H

namespace Scene
{
    class Node;
}

namespace Render
{
    class Render2;

    void ProcessLight(Render2* render, Scene::Node* node, System::Object* light);
}

#endif // PROCESS_LIGHT_H
