#ifndef _H_PUNK_SCENE_SKINE_MESH_NODE
#define _H_PUNK_SCENE_SKINE_MESH_NODE

#include "../virtual/data/skin_geometry.h"

#include "geometry_node.h"

namespace Virtual { class SkinGeometry; }

namespace Scene
{

	class PUNK_ENGINE SkinMeshNode : public GeometryNode
	{
	public:

		SkinMeshNode();

		virtual bool Save(std::ostream& stream) const;
		virtual bool Load(std::istream& stream);

		static System::Proxy<SkinMeshNode> CreateFromFile(const System::string& path);
		static System::Proxy<SkinMeshNode> CreateFromStream(std::istream& stream);

		virtual bool Apply(AbstractVisitor* visitor);

		System::Proxy<Virtual::SkinGeometry> GetSkinGeometry();
	};
}

REGISTER_MANAGER(L"resource.skin_mesh_nodes", L"*.skin_mesh_node", System::Environment::Instance()->GetModelFolder(), System::ObjectType::SKIN_MESH_NODE, Scene, SkinMeshNode, return, return);

#endif	//_H_PUNK_SCENE_SKINE_MESH_NODE