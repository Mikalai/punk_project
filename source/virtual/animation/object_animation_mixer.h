#ifndef _H_PUNK_VIRTUAL_ANIMATION_OBJECT_ANIMATION_MixER
#define _H_PUNK_VIRTUAL_ANIMATION_OBJECT_ANIMATION_MixER

#include "../../config.h"
#include "../../math/vec3.h"
#include "../../math/quat.h"
#include "animation_mixer.h"
#include <map>
#include <memory>

namespace Virtual
{
	class Animation;
}

namespace Virtual
{
	class PUNK_ENGINE_API ObjectAnimationMixer : public AnimationMixer
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

        const Math::vec3 GetPosition(float frame);
        const Math::quat GetRotation(float frame);

		bool HasAnimation();

		void DisableAllTracks();
		void EnableTrack(const System::string name, bool flag);
		void SetLooping(const System::string name, bool flag);
		void SetTrackWeight(const System::string name, float value);

//		void Save(System::Buffer* buffer) const;
//		void Load(System::Buffer* buffer);

	private:
		void NormalizeWeights();
	};
}

#endif	//	_H_PUNK_VIRTUAL_ANIMATION_OBJECT_ANIMATION_MixER
