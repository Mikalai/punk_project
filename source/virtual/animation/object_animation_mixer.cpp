#include <ostream>
#include <istream>
#include "object_animation_mixer.h"
#include "animation.h"

namespace Virtual
{
	void ObjectAnimationMixer::AddTrack(const std::string& name, Animation* anim)
	{
        (void)name; (void)anim;
	}

	void ObjectAnimationMixer::RemoveTrack(const std::string& name)
	{
        (void)name;
	}

	Animation* ObjectAnimationMixer::GetOrCreateTrack(const System::string& name)
	{
		auto it = m_tracks.find(name);
		if (it != m_tracks.end())
			return it->second.get();
		m_tracks[name].reset(new Animation);
		m_active[name] = false;
		m_factors[name] = 1;
		return m_tracks[name].get();
	}

	const Math::Vector3<float> ObjectAnimationMixer::GetPosition(float frame)
	{
		Math::vec3 res;
		for (auto it = m_tracks.begin(); it != m_tracks.end(); ++it)
		{
			if (m_active[it->first])
			{
				res += it->second->GetPosition(frame) * m_factors[it->first];
			}
		}
		return res;
	}

	const Math::Quaternion<float> ObjectAnimationMixer::GetRotation(float frame)
	{
		Math::quat res;
		for (auto it = m_tracks.begin(); it != m_tracks.end(); ++it)
		{
			if (m_active[it->first])
			{
				res += it->second->GetRotation(frame) * m_factors[it->first];
			}
		}
		return res;
	}

	bool ObjectAnimationMixer::HasAnimation()
	{
		return !m_tracks.empty();
	}

	void ObjectAnimationMixer::DisableAllTracks()
	{
		for (auto it = m_tracks.begin(); it != m_tracks.end(); ++it)
		{
			m_active[it->first] = false;
		}		
	}

	void ObjectAnimationMixer::EnableTrack(const System::string name, bool flag)
	{
		m_active[name] = flag;
		NormalizeWeights();
	}

	//void ObjectAnimationMixer::SetLooping(const System::string name, bool flag)
	//{
	//	m_tracks[name]->SetLooping(flag);		
	//}

	void ObjectAnimationMixer::SetTrackWeight(const System::string name, float value)
	{
		m_factors[name] = value;
		NormalizeWeights();
	}

	void ObjectAnimationMixer::NormalizeWeights()
	{
		float total_weight= 0;
		for (auto it = m_tracks.begin(); it != m_tracks.end(); ++it)
		{
			if (m_active[it->first])
			{
				total_weight += m_factors[it->first];
			}
		}

		for (auto it = m_tracks.begin(); it != m_tracks.end(); ++it)
		{
			if (m_active[it->first])
			{
				m_factors[it->first] /= total_weight;
			}
		}
	}

//	bool ObjectAnimationMixer::Save(std::ostream& stream) const
//	{
//		int track_count = m_tracks.size();
//		stream.write(reinterpret_cast<const char*>(&track_count), sizeof(track_count));
//		for(auto it = m_tracks.begin(); it != m_tracks.end(); ++it)
//		{
//			const System::string& name = it->first;
//			name.Save(stream);
//			it->second->Save(stream);

//			bool is_active = m_active.at(name);
//			float factor = m_factors.at(name);
//			stream.write(reinterpret_cast<const char*>(&is_active), sizeof(is_active));
//			stream.write(reinterpret_cast<const char*>(&factor), sizeof(factor));
//		}
//		return true;
//	}

//	bool ObjectAnimationMixer::Load(std::istream& stream)
//	{
//		int track_count= 0;
//		stream.read(reinterpret_cast<char*>(&track_count), sizeof(track_count));
//		for (int i = 0; i < track_count; ++i)
//		{
//			System::string name;
//			name.Load(stream);
//			m_tracks[name].reset(new Animation);
//			m_tracks[name]->Load(stream);

//			bool is_active;
//			float factor;
//			stream.read(reinterpret_cast<char*>(&is_active), sizeof(is_active));
//			stream.read(reinterpret_cast<char*>(&factor), sizeof(factor));
//			m_active[name] = is_active;
//			m_factors[name] = factor;
//		}
//		return true;
//	}
}
