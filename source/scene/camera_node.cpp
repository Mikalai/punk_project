#include "camera_node.h"
#include "../system/factory.h"
#include "../virtual/manager/manager.h"

namespace Scene
{
	CameraNode::CameraNode()
	{
		SetType(System::ObjectType::CAMERA_NODE);
	}

	bool CameraNode::Save(std::ostream& stream) const
	{
		if (!Node::Save(stream))
			return (out_error() << "Can't save camera node" << std::endl, false);

		if (!System::Factory::Instance()->SaveToStream(stream, m_camera))
			return (out_error() << "Can't save camera object to stream" << std::endl, false);

		return true;		
	}

	bool CameraNode::Load(std::istream& stream) 
	{
		if (!Node::Load(stream))
			return (out_error() << "Can't load camera node" << std::endl, false);
		
		m_camera = System::Factory::Instance()->LoadFromStream(stream);
		if (m_camera.IsValid())
			return (out_error() << "Can't load camera object from stream" << std::endl, false);

		return true;
	}

	System::Proxy<CameraNode> CameraNode::CreateFromFile(const System::string& path)
	{
		std::ifstream stream(path.Data(), std::ios::binary);
		if (!stream.is_open())
			return (out_error() << "Can't open file " << path << std::endl, System::Proxy<CameraNode>(nullptr));
		return CreateFromStream(stream);
	}

	System::Proxy<CameraNode> CameraNode::CreateFromStream(std::istream& stream)
	{
		System::Proxy<CameraNode> node(new CameraNode);
		if (!node->Load(stream))
			return (out_error() << "Can't load node from file" << std::endl, System::Proxy<CameraNode>(nullptr));
		return node;
	}

	bool CameraNode::Apply(AbstractVisitor* visitor)
	{
		return visitor->Visit(this);
	}
}