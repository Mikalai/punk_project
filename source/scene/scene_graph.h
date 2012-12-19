#ifndef _H_PUNK_SCENE_MAIN_HEADER
#define _H_PUNK_SCENE_MAIN_HEADER

#include "../system/resource_manager.h"
#include "../system/object.h"
#include "node.h"
#include "geometry_node.h"
#include "transform_node.h"
#include "camera_node.h"
#include "light_node.h"
#include "location_indoor.h"
#include "portal_node.h"
#include "point_light_node.h"
#include "material_node.h"
#include "default_visitor.h"
#include "armature_node.h"
#include "static_mesh_node.h"
#include "skin_mesh_node.h"

namespace Scene
{
	class PUNK_ENGINE SceneGraph : public System::Object
	{
	public:
		typedef std::vector<System::Proxy<Virtual::Material>> MaterialsCollection;

	public:
		SceneGraph();

		virtual bool Save(std::ostream& stream) const;
		virtual bool Load(std::istream& stream);
				
		static System::Proxy<SceneGraph> CreateFromFile(const System::string& path);
		static System::Proxy<SceneGraph> CreateFromStream(std::istream& stream);

		void SetRootNode(System::Proxy<Node> value) { m_root = value; }
		System::Proxy<Node> GetRootNode() { return m_root; }

		void AddMaterial(System::Proxy<Virtual::Material> value) { m_used_materials.push_back(value); }

		void SetActiveCamera(System::Proxy<Virtual::Camera> value);
		System::Proxy<CameraNode> GetCameraNode() { return m_camera_node; }

	private:	
		SceneGraph(const SceneGraph&);
		SceneGraph& operator = (const SceneGraph&);

	private:

		System::Proxy<CameraNode> m_camera_node;
		System::Proxy<Node> m_root;
		MaterialsCollection m_used_materials;

	};
}

REGISTER_MANAGER(L"resource.scenes", L"*.scene_graph", System::Environment::Instance()->GetModelFolder(), System::ObjectType::SCENE_GRAPH, Scene, SceneGraph, return, return);

#endif	//	_H_PUNK_SCENE_MAIN_HEADER
