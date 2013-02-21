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
#include "bone_node.h"
#include "bounding_volume_updater.h"
#include "texture_view_node.h"
#include "terrain_node.h"

namespace GUI
{
	class Widget;
}

namespace Scene
{
	class PUNK_ENGINE SceneGraph : public System::Object
	{
	public:
		SceneGraph();
		virtual ~SceneGraph();

		virtual bool Save(std::ostream& stream) const;
		virtual bool Load(std::istream& stream);
				
		static SceneGraph* CreateFromFile(const System::string& path);
		static SceneGraph* CreateFromStream(std::istream& stream);

		void SetRootNode(Node* value) { m_root = value; }
		Node* GetRootNode() { return m_root; }

		void SetActiveCamera(Virtual::Camera* value);
		CameraNode* GetCameraNode() { return m_camera_node; }

	private:	
		SceneGraph(const SceneGraph&);
		SceneGraph& operator = (const SceneGraph&);

	private:

		//	this node should be deleted
		CameraNode* m_camera_node;
		Node* m_root;
	};
}

#endif	//	_H_PUNK_SCENE_MAIN_HEADER
