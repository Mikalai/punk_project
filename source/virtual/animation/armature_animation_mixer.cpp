#include <ostream>
#include <math.h>
#include <istream>
#include "../../system/environment.h"
#include "../../utility/module.h"
#include "../../math/helper.h"
#include "armature_animation_mixer.h"
#include "bone_animation.h"
#include "action.h"
#include "../skinning/armature.h"
#include "../../system/logger.h"
#include "../../engine_objects.h"

namespace Virtual
{
    PUNK_OBJECT_REG(ArmatureAnimationMixer, "Virtual.ArmatureAnimationMixer", PUNK_ARMATURE_ANIMATION_MIXER, &AnimationMixer::Info.Type);

    ArmatureAnimationMixer::ArmatureAnimationMixer()
        : m_current_time(0)
        , m_armature(nullptr)
    {        
        Info.Add(this);
    }

    ArmatureAnimationMixer::~ArmatureAnimationMixer()
    {
        Info.Remove(this);
    }

    bool ArmatureAnimationMixer::GetBoneMatrix(const System::string& bone, Math::mat4& matrix)
    {
        try
        {
            Math::mat4 pos = Math::mat4::CreateTranslate(m_result[GetBoneIndex(bone)].m_position);
            Math::mat4 rot = Math::QuaternionToMatrix4x4(m_result[GetBoneIndex(bone)].m_rotation);
            matrix = pos*rot;
            return true;
        }
        catch(std::out_of_range&)
        {
            out_error() << "No bone in armature with name " << bone << std::endl;
            return false;
        }
        return true;
    }

    void ArmatureAnimationMixer::SetTrackTime(float frame)
    {
        size_t result_size = m_armature->GetBonesCount();
        m_result.resize(result_size);
        for (auto& bone : m_result)
        {
            bone.m_position.Set(0,0,0);
            bone.m_rotation.Set(0,0,0,0);
        }

        for (size_t track_index = 0; track_index != m_tracks_array.size(); ++track_index)
        {
            TrackOption& options = m_options[track_index];
            Action* action = m_tracks_array[track_index];
            m_current_time = frame;
            //	find correct time
            if (options.m_enable)
            {
                if (m_current_time  > action->GetEndFrame())
                {
                    if (options.m_loop)
                    {
                        if (action->GetEndFrame() > 0)
                            while (m_current_time  > action->GetEndFrame()) m_current_time  -= action->GetEndFrame();
                    }
                    else
                        m_current_time = action->GetEndFrame();
                }

                for (size_t bone_index = 0; bone_index != m_bones_animation_cache[track_index].size(); ++bone_index)
                {
                    const BoneAnimation* track = m_bones_animation_cache[track_index][bone_index];

                    Math::vec3 pos = track->GetPosition(m_current_time);
                    Math::quat rot = track->GetRotation(m_current_time);

                    m_result[bone_index].m_position += pos * options.m_weight;
                    m_result[bone_index].m_rotation += rot * options.m_weight;
                }
            }
        }

        UpdateGlobalMatrix();
    }

    void ArmatureAnimationMixer::EnableTrack(const System::string& track_name, bool flag)
    {
        m_options[GetTrackIndex(track_name)].m_enable = flag;
    }

    void ArmatureAnimationMixer::DisableAllTracks()
    {
        for (auto& option : m_options)
        {
            option.m_enable = false;
        }
    }

    void ArmatureAnimationMixer::SetTrackWeight(const System::string& track_name, float value)
    {
        m_options[GetTrackIndex(track_name)].m_weight = value;
    }

    void ArmatureAnimationMixer::SetLooping(const System::string& track_name, bool flag)
    {
        m_options[GetTrackIndex(track_name)].m_loop = flag;
    }

    void ArmatureAnimationMixer::Save(System::Buffer *buffer) const
    {
        AnimationMixer::Save(buffer);
    }

    void ArmatureAnimationMixer::Load(System::Buffer *buffer)
    {
        AnimationMixer::Load(buffer);
    }

    size_t ArmatureAnimationMixer::GetTrackIndex(const System::string& value)
    {
        for (size_t i = 0; i != m_tracks.size(); ++i)
        {
            if (m_tracks[i] == value)
                return i;
        }
        return -1;
    }

    size_t ArmatureAnimationMixer::GetBoneIndex(const System::string& value)
    {
        return m_armature->GetBoneIndex(value);
    }

    void ArmatureAnimationMixer::EnableTrack(size_t track, bool flag)
    {
        if (track >= m_tracks.size())
            return;
        m_options[track].m_enable = flag;
    }

    void ArmatureAnimationMixer::SetTrackWeight(size_t track, float value)
    {
        if (track >= m_tracks.size())
            return;
        m_options[track].m_weight = value;
    }

    void ArmatureAnimationMixer::SetLooping(size_t track, bool flag)
    {
        if (track >= m_tracks.size())
            return;
        m_options[track].m_loop = flag;
    }

    bool ArmatureAnimationMixer::GetBoneMatrix(size_t bone, Math::mat4& matrix)
    {
        Math::mat4 pos = Math::mat4::CreateTranslate(m_result[bone].m_position);
        Math::mat4 rot = Math::QuaternionToMatrix4x4(m_result[bone].m_rotation);
        matrix = pos*rot;
        return true;
    }

    void ArmatureAnimationMixer::UpdateGlobalMatrix()
    {
        m_animated_global_matrix.resize(m_armature->GetBonesCount());
        for (size_t i = 0; i != m_armature->GetRootsBonesCount(); ++i)
        {
            UpdateBonesMatrix(m_armature->GetRootBone(i));
        }
    }

    void ArmatureAnimationMixer::UpdateBonesMatrix(Bone* value)
    {
        const Bone* parent = value->GetParent();
        if (parent)
        {
            Math::mat4 bone_matrix;
            GetBoneMatrix(value->GetIndex(), bone_matrix);
            Math::mat4 global = m_animated_global_matrix[parent->GetIndex()] * value->GetLocalMatrix() * bone_matrix * value->GetLocalMatrix().Inversed();
            m_animated_global_matrix[value->GetIndex()] = global;
        }
        else
        {
            Math::mat4 bone_matrix;
            GetBoneMatrix(value->GetIndex(), bone_matrix);
            Math::mat4 global = value->GetLocalMatrix() * bone_matrix * value->GetLocalMatrix().Inversed();
            m_animated_global_matrix[value->GetIndex()] = global;
        }
        for (auto child : value->GetChildren())
        {
            UpdateBonesMatrix(child);
        }
    }

    const Math::mat4& ArmatureAnimationMixer::GetAnimatedGlobalMatrix(size_t bone) const
    {
        return m_animated_global_matrix[bone];
    }

    Armature* ArmatureAnimationMixer::GetArmature()
    {
        return m_armature;
    }

    void ArmatureAnimationMixer::SetArmature(Armature *value)
    {
        m_armature = value;
        if (m_armature)
        {
            for (auto action_name : m_armature->GetSupportedActionArray())
            {
                Action* action = Cast<Action*>(Utility::ParsePunkFile(System::Environment::Instance()->GetModelFolder() + action_name + System::string(L".action")));
                m_tracks.push_back(action_name);
                m_options.push_back(TrackOption());
                m_tracks_array.push_back(action);
                size_t track_index = m_tracks.size() - 1;
                m_bones_animation_cache.push_back(std::vector<BoneAnimation*>());
                m_bones_animation_cache[track_index].resize(m_armature->GetBonesCount());
                for (auto o : *action)
                {
                    BoneAnimation* anim = As<BoneAnimation*>(o);
                    if (!anim)
                        continue;
                    m_bones_animation_cache[track_index][GetBoneIndex(anim->GetName())] = anim;
                }
            }
            DisableAllTracks();
            if (!m_options.empty())
                m_options[0].m_enable = true;
            SetTrackTime(0);
        }
    }

//    void ArmatureAnimationMixer::AddBoneAnimation(const System::string &track_name, const System::string &bone_name, BoneAnimation *anim)
//    {
//        auto track_index = GetTrackIndex(track_name);
//        if (track_index == -1)
//        {
//            m_tracks.push_back(track_name);
//            track_index = m_tracks.size() - 1;
//            m_tracks_array.resize(m_armature.GetBonesCount());
//        }
//        m_tracks_array[track_index][GetBoneIndex(bone_name)] = anim;
//    }
}
