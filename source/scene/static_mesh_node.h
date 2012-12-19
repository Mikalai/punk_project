#ifndef _H_PUNK_SCENE_STATIC_MESH_NODE
#define _H_PUNK_SCENE_STATIC_MESH_NODE

#include "../virtual/data/static_geometry.h"

#include "geometry_node.h"

namespace Scene
{

	class PUNK_ENGINE StaticMeshNode : public GeometryNode
	{
	public:

		StaticMeshNode();

		virtual bool Save(std::ostream& stream) const;
		virtual bool Load(std::istream& stream);

		static System::Proxy<StaticMeshNode> CreateFromFile(const System::string& path);
		static System::Proxy<StaticMeshNode> CreateFromStream(std::istream& stream);

		virtual bool Apply(AbstractVisitor* visitor);

		System::Proxy<Virtual::StaticGeometry> GetStaticGeometry();
	};
}

REGISTER_MANAGER(L"resource.static_mesh_nodes", L"*.static_mesh_node", System::Environment::Instance()->GetModelFolder(), System::ObjectType::STATIC_MESH_NODE, Scene, StaticMeshNode, return, return);

#endif	//_H_PUNK_SCENE_STATIC_MESH_NODE