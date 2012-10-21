#include <iostream>
#include "../system/logger.h"
#include "../string/string.h"
#include "../virtual/data/data.h"
#include "../virtual/skinning/skinning.h"
#include "../system/object.h"
#include "../audio/punk_audio.h"
#include "../opengl/driver.h"

#include "node.h"

namespace Scene
{
	Node::Node()
		: m_parent(nullptr)
		, m_data(nullptr)
	{}

	Node::~Node()
	{
		for (auto obj : m_children)
		{
			delete obj;
		}
	}

	bool Node::Save(std::ostream& stream)
	{		
		System::Object::Save(stream);

		m_parent_name.Save(stream);
		m_name.Save(stream);
		int flag = (m_data == nullptr) ? 0 : 1;
		stream.write((char*)&flag, sizeof(flag));
		if (flag)
		{
			System::ObjectType type = m_data->GetType();
			stream.write((char*)&type, sizeof(type));
			m_data->Save(stream);
		}

		int size = (int)m_children.size();
		stream.write((char*)&size, sizeof(size));
		for (auto child : m_children)
		{
			child->Save(stream);
		}

		return true;
	}

	bool Node::Load(std::istream& stream)
	{
		System::Object::Load(stream);

		m_parent_name.Load(stream);
		m_name.Load(stream);
		int flag = 0;
		stream.read((char*)&flag, sizeof(flag));
		if (flag)
		{
			System::ObjectType type;
			stream.read((char*)&type, sizeof(type));
			switch (type)
			{
			case System::RESOURCE_NONE:
				break;
			case System::PERMANENT_RESOURCE_STATIC_MESH:
				m_data = OpenGL::StaticMesh::CreateFromStream(stream);
				break;
			case System::PERMANENT_RESOURCE_SKINNED_MESH:
				m_data = OpenGL::SkinnedMesh::CreateFromStream(stream);
				break;
			case System::PERMANENT_RESOURCE_AUDIO_BUFFER:
				m_data = Audio::AudioBuffer::CreateFromStream(stream);
				break;
			case System::PERMANENT_RESOURCE_COLLISION_SHAPE:
				break;
			case System::PERMANENT_RESOURCE_TEXTURE2D:
				m_data = OpenGL::Texture2D::CreateFromStream(stream);
				break;
			case System::PERMANENT_RESOURCE_SCENE:
				break;
			case System::PERMANENT_RESOURCE_ARMATURE:
				m_data = Virtual::Armature::CreateFromStream(stream);
				break;
			case System::PERMANENT_RESOURCE_WEAPON_TYPE:
				break;
			case System::DYNAMIC_RESOURCE_START:
				break;
			case System::DYNAMIC_RESOURCE_CAMERA_FPS:
				m_data = Virtual::Cameras::FirstPersonCamera::CreateFromStream(stream);
				break;
			case System::DYNAMIC_RESOURCE_CAMERA_1:
				break;
			case System::DYNAMIC_RESOURCE_CAMERA_2:
				break;
			case System::DYNAMIC_RESOURCE_PROXY:
				break;
			case System::DYNAMIC_RESOURCE_TRANSFORM:
				break;
			case System::DYNAMIC_RESOURCE_POINT_LIGHT:
				m_data = Virtual::PointLight::CreateFromStream(stream);
				break;
			case System::DYNAMIC_RESOURCE_SPOT_LIGHT:
				break;
			case System::DYNAMIC_RESOURCE_MATERIAL:
				m_data = Virtual::Material::CreateFromStream(stream);
				break;
			case System::DYNAMIC_RESOURCE_ARMATURE_ANIMATION_MIXER:
				break;
			case System::DYNAMIC_RESOURCE_OBJECT_ANIMATION_MIXER:
				break;
			default:
				break;
			}
		}

		int size = (int)m_children.size();
		stream.read((char*)&size, sizeof(size));
		for (auto child : m_children)
		{
			child->Load(stream);
		}

		return true;
	}

	Node* Node::GetChild(const System::string& name, bool deep_search)
	{
		return const_cast<Node*>(static_cast<const Node*>(this)->GetChild(name, deep_search));
	}

	const Node* Node::GetChild(const System::string& name, bool deep_search) const
	{
		for (auto obj : m_children)
		{
			if (obj && obj->GetName() == name)
				return obj;

			if (deep_search && obj)
			{
				const Node* res = obj->GetChild(name, deep_search);
				if (res)
				{
					return res;
				}
			}
		}
		return 0;
	}

	int Node::GetChildIndex(const System::string& name)
	{
		int index = 0;
		for (auto child : m_children)
		{
			if (child->GetName() == name)
				return index;
			index++;
		}
		return -1;
	}

	bool Node::Apply(NodeVisitor* value)
	{
		if (!(*value)(this))
			return false;

		for (auto child : m_children)
		{
			value->PreEnter();
			auto flag = child->Apply(value);
			value->PostEnter();
			if (!flag)
				return false;
		}
		return true;
	}
}

