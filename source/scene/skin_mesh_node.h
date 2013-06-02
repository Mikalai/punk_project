#ifndef _H_PUNK_SCENE_SKINE_MESH_NODE
#define _H_PUNK_SCENE_SKINE_MESH_NODE

#include "../virtual/data/skin_geometry.h"

#include "geometry_node.h"

namespace Virtual { class SkinGeometry; }

namespace Scene
{

	class PUNK_ENGINE_API SkinMeshNode : public GeometryNode
	{
	public:

		SkinMeshNode();

		virtual bool Save(std::ostream& stream) const;
		virtual bool Load(std::istream& stream);

		SkinMeshNode* CreateFromFile(const System::string& path);
		SkinMeshNode* CreateFromStream(std::istream& stream);

		virtual bool Apply(AbstractVisitor* visitor);

		Virtual::SkinGeometry* GetSkinGeometry();
	};
}

#endif	//_H_PUNK_SCENE_SKINE_MESH_NODE