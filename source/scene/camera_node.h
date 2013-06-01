#ifndef _H_PUNK_SCENE_CAMERA_NODE
#define _H_PUNK_SCENE_CAMERA_NODE

#include "transform_node.h"
#include "../virtual/data/camera.h"

namespace Scene
{
	class PUNK_ENGINE_PUBLIC CameraNode : public TransformNode
	{
	public:
		
		CameraNode();

		virtual bool Save(std::ostream& stream) const;
		virtual bool Load(std::istream& stream);
		
		static CameraNode* CreateFromFile(const System::string& path);
		static CameraNode* CreateFromStream(std::istream& stream);

		virtual bool Apply(AbstractVisitor* visitor);

		void SetCamera(Virtual::Camera* value) { m_camera = value; }
		Virtual::Camera* GetCamera() { return m_camera; }

	private:
		Virtual::Camera* m_camera;
	};
}

#endif	//	_H_PUNK_SCENE_CAMERA_NODE