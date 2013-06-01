#ifndef _H_ARMATURE_ANIMATION
#define _H_ARMATURE_ANIMATION

#include <iosfwd>
#include <map>

#include "../../config.h"
#include "../../math/vec3.h"
#include "../../math/quat.h"
#include "../../math/mat4.h"
#include "../../string/string.h"
#include "animation_Mixer.h"

namespace Virtual
{
	class Armature;
	class BoneAnimation;

	class PUNK_ENGINE_PUBLIC ArmatureAnimationMixer : public AnimationMixer
	{
	public:
		ArmatureAnimationMixer();		
		void UpdateBones(float frame);
		void DisableAllTracks();
		void EnableTrack(const System::string&, bool flag);
		void SetTrackWeight(const System::string&, float value);
		void SetLooping(const System::string&, bool flag);
		void AddBoneAnimation(const System::string& track_name, const System::string& bone_name, BoneAnimation* anim);
		bool GetBoneMatrix(const System::string& bone, Math::mat4& matrix);
		void SetTrackTime(float time);
		float GetTrackTime() const { return m_current_time; }

		virtual bool Save(std::ostream& stream) const;
		virtual bool Load(std::istream& stream);
		virtual ~ArmatureAnimationMixer();

	private:
		
		/**	Contains info about track */
		struct PUNK_ENGINE_PUBLIC TrackOption
		{
			float m_weight;
			float m_max_time;	
			bool m_enable;			
			bool m_loop;		

			TrackOption()
				: m_weight(1)
				, m_max_time(0)
				, m_enable(false)
				, m_loop(true)
			{}
		};

		/** Interpolated data for each bone */
		struct PUNK_ENGINE_PUBLIC InterpolatedData
		{
			Math::vec3 m_position;
			Math::quat m_rotation;
		};

		std::map<System::string, TrackOption> m_options;		
		//	[ track_name: [ bone_name: animation ] ]
		std::map<System::string, std::map<System::string, BoneAnimation*>> m_tracks;
		
		//	result interpolated data for current time for each bone
		//	[bone_name: pos_rot]
		std::map<System::string, InterpolatedData> m_result;

		///	current time of the animation;
		float m_current_time;		
	};
}

#endif