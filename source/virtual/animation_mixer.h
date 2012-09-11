#ifndef _H_PUNK_UTILITY_ANIMATION_MIXER
#define _H_PUNK_UTILITY_ANIMATION_MIXER

#include "../config.h"
#include <map>
#include <memory>
#include "animation.h"

namespace System { class string; }
namespace Utility
{
	class PUNK_ENGINE AnimationMixer
	{
		typedef std::map<System::string, std::shared_ptr<Animation>> Type;
		typedef std::map<System::string, bool> ActiveTracks;
		typedef std::map<System::string, float> MixFactors;
		Type m_tracks;
		ActiveTracks m_active;
		MixFactors m_factors;
	public:
		void AddTrack(const std::string& name, Animation* anim);
		void RemoveTrack(const std::string& name);

		Animation* GetOrCreateTrack(const System::string& name);

		const Math::Vector3<float> GetPosition(float frame);
		const Math::Quaternion<float> GetRotation(float frame);

		bool HasAnimation();

		void DisableAllTracks();
		void EnableTrack(const System::string name, bool flag);
		void SetLooping(const System::string name, bool flag);
		void SetTrackWeight(const System::string name, float value);

		void Save(std::ostream& stream);
		void Load(std::istream& stream);

	private:
		void NormalizeWeights();
	};
}

#endif