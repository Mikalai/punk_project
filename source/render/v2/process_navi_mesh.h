#ifndef PROCESS_NAVI_MESH_H
#define PROCESS_NAVI_MESH_H

namespace System { class Object; }
namespace Scene { class Node; }

namespace Render
{
    class Render2;
    void ProcessNaviMesh(Render2* render, Scene::Node* node, System::Object* mesh);
}

#endif // PROCESS_NAVI_MESH_H
