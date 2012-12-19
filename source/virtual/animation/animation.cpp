#include <ostream>
#include <istream>
#include "animation.h"

IMPLEMENT_MANAGER(L"resource.animations", L"*.animation", System::Environment::Instance()->GetModelFolder(), System::ObjectType::ANIMATION, Virtual, Animation);

namespace Virtual
{
	Animation::Animation()
		: m_animation_type(AnimationType::ANIMATION_NONE)
	{
		SetType(System::ObjectType::ANIMATION);
	}

	void Animation::AddPositionKey(int frame, Math::vec3& position)
	{
		m_pos_track.AddKey(frame, position);
	}
		
	void Animation::AddRotationKey(int frame, Math::quat& rotation)
	{
		m_rot_track.AddKey(frame, rotation);
	}
		
	Math::vec3& Animation::GetOrCreatePositionKey(int time)
	{
		if (!m_pos_track.HasKeyAt(time))
			m_pos_track.AddKey(time, Math::vec3());
		bool flag;
		return m_pos_track.GetOriginalKey(time, flag);
	}

	Math::quat& Animation::GetOrCreateRotationKey(int time)
	{
		if (!m_rot_track.HasKeyAt(time))
			m_rot_track.AddKey(time, Math::quat());
		bool flag;
		return m_rot_track.GetOriginalKey(time, flag);
	}

	const Math::vec3 Animation::GetPosition(float time) const
	{
		return m_pos_track.GetKey(time);
	}
		
	const Math::quat Animation::GetRotation(float time) const
	{
		return m_rot_track.GetKey(time);
	}

	bool Animation::Save(std::ostream& stream) const
	{
		if (!System::Object::Save(stream))
			return (out_error() << "Can't save animation" << std::endl, false);

		stream.write((char*)&m_animation_type, sizeof(m_animation_type));
		m_pos_track.Save(stream);
		m_rot_track.Save(stream);
		return true;
	}

	bool Animation::Load(std::istream& stream)
	{
		if (!System::Object::Load(stream))
			return (out_error() << "Can't save animation" << std::endl, false);

		stream.read((char*)&m_animation_type, sizeof(m_animation_type));
		m_pos_track.Load(stream);
		m_rot_track.Load(stream);
		return true;
	}

	System::Proxy<Animation> Animation::CreateFromFile(const System::string& path)
	{
		std::ifstream stream(path.Data(), std::ios::binary);
		if (!stream.is_open())
			return (out_error() << "Can't open file " << path << std::endl, System::Proxy<Animation>(nullptr));
		return CreateFromStream(stream);
	}

	System::Proxy<Animation> Animation::CreateFromStream(std::istream& stream)
	{
		System::Proxy<Animation> node(new Animation);
		if (!node->Load(stream))
			return (out_error() << "Can't load node from file" << std::endl, System::Proxy<Animation>(nullptr));
		return node;
	}
}
