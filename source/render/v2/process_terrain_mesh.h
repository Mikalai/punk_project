#ifndef PROCESS_TERRAIN_MESH_H
#define PROCESS_TERRAIN_MESH_H

namespace System { class Object; }
namespace Scene { class Node; }

namespace Render
{
    class Render2;
    void ProcessTerrainMesh(Render2* render, Scene::Node* node, System::Object* mesh);
}

#endif // PROCESS_TERRAIN_MESH_H
