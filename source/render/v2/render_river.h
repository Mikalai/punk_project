#ifndef RENDER_RIVER_H
#define RENDER_RIVER_H

namespace System { class Object; }
namespace Scene { class Node; }

namespace Render
{
    class Render2;
    void ProcessRiver(Render2* render, Scene::Node* node, System::Object* river);
}


#endif // RENDER_RIVER_H
