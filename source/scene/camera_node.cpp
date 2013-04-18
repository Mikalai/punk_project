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
		Node::Save(stream);

		System::GetFactory()->SaveToStream(stream, m_camera);

		return true;
	}

	bool CameraNode::Load(std::istream& stream)
	{
		Node::Load(stream);

		m_camera = Cast<Virtual::Camera*>(System::GetFactory()->LoadFromStream(stream));

		return true;
	}

	CameraNode* CameraNode::CreateFromFile(const System::string& path)
	{
		std::ifstream stream(path.ToStdString().c_str(), std::ios::binary);
		if (!stream.is_open())
			throw System::PunkInvalidArgumentException(L"Can't open file " + path);
		return CreateFromStream(stream);
	}

	CameraNode* CameraNode::CreateFromStream(std::istream& stream)
	{
		std::unique_ptr<CameraNode> node(new CameraNode);
		node->Load(stream);
		return node.release();
	}

	bool CameraNode::Apply(AbstractVisitor* visitor)
	{
		return visitor->Visit(this);
	}
}
