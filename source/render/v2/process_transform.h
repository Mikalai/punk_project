#ifndef PROCESS_TRANSFORM_H
#define PROCESS_TRANSFORM_H

namespace System { class Object; }
namespace Scene { class Node; }

namespace Render
{
    class Render2;
    void ProcessTransform(Render2* render, Scene::Node* node, System::Object* o);
}

#endif // PROCESS_TRANSFORM_H
