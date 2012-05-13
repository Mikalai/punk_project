#include "animation_mixer.h"

namespace Utility
{
	void AnimationMixer::AddTrack(const std::string& name, Animation* anim)
	{
	}

	void AnimationMixer::RemoveTrack(const std::string& name)
	{
	}

	Animation* AnimationMixer::GetOrCreateTrack(const System::string& name)
	{
		auto it = m_tracks.find(name);
		if (it != m_tracks.end())
			return it->second.get();
		m_tracks[name].reset(new Animation);
		m_active[name] = false;
		m_factors[name] = 1;
		return m_tracks[name].get();
	}

	const Math::Vector3<float> AnimationMixer::GetPosition(int frame)
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

	const Math::Quaternion<float> AnimationMixer::GetRotation(int frame)
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

	bool AnimationMixer::HasAnimation()
	{
		return !m_tracks.empty();
	}

	void AnimationMixer::EnableTrack(const System::string name, bool flag)
	{
		m_active[name] = flag;
		NormalizeWeights();
	}

	void AnimationMixer::SetLooping(const System::string name, bool flag)
	{
		m_tracks[name]->SetLooping(flag);		
	}

	void AnimationMixer::SetTrackWeight(const System::string name, float value)
	{
		m_factors[name] = value;
		NormalizeWeights();
	}

	void AnimationMixer::NormalizeWeights()
	{
		float total_weight = 0;
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
}