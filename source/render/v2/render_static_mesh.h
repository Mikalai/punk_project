#ifndef RENDER_STATIC_MESH_H
#define RENDER_STATIC_MESH_H

namespace Scene { class Node; }
namespace System { class Object; }

namespace Render
{
    class Render2;
    void ProcessStaticMesh(Render2* render, Scene::Node* node, System::Object* geom);
}

#endif // RENDER_STATIC_MESH_H
