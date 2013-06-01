#ifndef _H_PUNK_SCENE_STATIC_MESH_NODE
#define _H_PUNK_SCENE_STATIC_MESH_NODE

#include "../virtual/data/static_geometry.h"

#include "geometry_node.h"

namespace Scene
{

	class PUNK_ENGINE_PUBLIC StaticMeshNode : public GeometryNode
	{
	public:

		StaticMeshNode();

		virtual bool Save(std::ostream& stream) const;
		virtual bool Load(std::istream& stream);

		static StaticMeshNode* CreateFromFile(const System::string& path);
		static StaticMeshNode* CreateFromStream(std::istream& stream);

		virtual bool Apply(AbstractVisitor* visitor);

		Virtual::StaticGeometry* GetStaticGeometry();
	};
}

#endif	//_H_PUNK_SCENE_STATIC_MESH_NODE