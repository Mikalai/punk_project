#ifndef RENDER_SKIN_MESH_H
#define RENDER_SKIN_MESH_H

namespace Scene { class SkinGeometry; }
namespace System { class Object; }

namespace Render
{
    class Render2;
    void ProcessSkinMesh(Render2* render, Scene::Node* node, System::Object* geom);
};

#endif // RENDER_SKIN_MESH_H
