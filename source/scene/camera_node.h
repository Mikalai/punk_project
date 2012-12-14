#ifndef _H_PUNK_SCENE_CAMERA_NODE
#define _H_PUNK_SCENE_CAMERA_NODE

#include "transform_node.h"
#include "../virtual/data/camera.h"

namespace Scene
{
	class PUNK_ENGINE CameraNode : public TransformNode
	{
	public:
		
		CameraNode();

		virtual bool Save(std::ostream& stream) const;
		virtual bool Load(std::istream& stream);
		
		static System::Proxy<CameraNode> CreateFromFile(const System::string& path);
		static System::Proxy<CameraNode> CreateFromStream(std::istream& stream);

		virtual bool Apply(AbstractVisitor* visitor);

		void SetCamera(System::Proxy<Virtual::Camera> value) { m_camera = value; }
		System::Proxy<Virtual::Camera> GetCamera() { return m_camera; }

	private:
		System::Proxy<Virtual::Camera> m_camera;
	};
}

REGISTER_MANAGER(L"resource.camera_nodes", L"*.camera_node", System::Environment::Instance()->GetModelFolder(), System::ObjectType::CAMERA_NODE, Scene, CameraNode);

#endif	//	_H_PUNK_SCENE_CAMERA_NODE