#ifndef _H_ARMATURE_ANIMATION
#define _H_ARMATURE_ANIMATION

#include <iosfwd>
#include <map>

#include "../../config.h"
#include "../../math/vec3.h"
#include "../../math/quat.h"
#include "../../math/mat4.h"
#include "../../string/string.h"
#include "animation_mixer.h"

namespace Virtual
{
	class Armature;
    class Action;
	class BoneAnimation;
    class Bone;

    /**
     * @brief The ArmatureAnimationMixer class
     *  All bones should present in animations
     */
	class PUNK_ENGINE_API ArmatureAnimationMixer : public AnimationMixer
	{
	public:
        ArmatureAnimationMixer();
        ArmatureAnimationMixer(const ArmatureAnimationMixer&) = delete;
        ArmatureAnimationMixer& operator = (const ArmatureAnimationMixer&) = delete;
        virtual ~ArmatureAnimationMixer();

        virtual void SetTrackTime(float time) override;
        virtual float GetTrackTime() const override { return m_current_time; }
        virtual void SetLooping(size_t track, bool flag) override;

        //void UpdateBones(float frame);
        void SetArmature(Armature* value);
		void DisableAllTracks();
		void EnableTrack(const System::string&, bool flag);
		void SetTrackWeight(const System::string&, float value);
		void SetLooping(const System::string&, bool flag);
        //void AddBoneAnimation(const System::string &track_name, const System::string &bone_name, BoneAnimation *anim);
		bool GetBoneMatrix(const System::string& bone, Math::mat4& matrix);		

        size_t GetTrackIndex(const System::string& value);
        size_t GetBoneIndex(const System::string& value);
        void EnableTrack(size_t track, bool flag);
        void SetTrackWeight(size_t track, float value);        
        bool GetBoneMatrix(size_t bone, Math::mat4& matrix);

        const Math::mat4& GetAnimatedGlobalMatrix(size_t bone) const;

        virtual void Save(System::Buffer* buffer) const override;
        virtual void Load(System::Buffer* buffer) override;		

        Armature* GetArmature();

    private:
		
        void UpdateGlobalMatrix();
        void UpdateBonesMatrix(Bone* value);

		/**	Contains info about track */
		struct PUNK_ENGINE_API TrackOption
		{
			float m_weight;
			bool m_enable;			
			bool m_loop;		

			TrackOption()
				: m_weight(1)
				, m_enable(false)
				, m_loop(true)
			{}
		};

		/** Interpolated data for each bone */
		struct PUNK_ENGINE_API InterpolatedData
		{
			Math::vec3 m_position;
			Math::quat m_rotation;
		};

        //std::map<System::string, TrackOption> m_options;
		//	[ track_name: [ bone_name: animation ] ]
        //std::map<System::string, std::map<System::string, BoneAnimation*>> m_tracks;

        std::vector<TrackOption> m_options;
        std::vector<System::string> m_tracks;
        std::vector<Action*> m_tracks_array;
        std::vector<std::vector<BoneAnimation*>> m_bones_animation_cache;

		//	result interpolated data for current time for each bone
		//	[bone_name: pos_rot]
        std::vector<InterpolatedData> m_result;
        std::vector<Math::mat4> m_animated_global_matrix;
        //std::map<System::string, InterpolatedData> m_result;

		///	current time of the animation;
        float m_current_time;

        //  A place from which a structure can be get
        Armature* m_armature;

        PUNK_OBJECT(ArmatureAnimationMixer)
	};
}

#endif
