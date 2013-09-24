#include <ostream>
#include <istream>
#include <vector>
#include <algorithm>
#include "../../system/logger.h"
#include "../../system/serializable.h"
#include "../../math/interpolation.h"
#include "animation_track.h"

namespace Virtual
{
    void LoadAnimationTrack(System::Buffer *buffer, AnimationTrack<Math::quat> &value)
    {
        int frame_count = buffer->ReadSigned32();
        if (frame_count)
        {
            value.m_keys.resize(frame_count);
            for (int i = 0; i != frame_count; ++i)
            {
                AnimationTrack<Math::quat>::Frame f = buffer->ReadSigned32();
                Math::quat v;
                Math::LoadQuaternion(buffer, v);
                value.m_keys[i] = std::pair<AnimationTrack<Math::quat>::Frame, Math::quat>(f, v);
            }
        }
    }


    void LoadAnimationTrack(System::Buffer* buffer, AnimationTrack<Math::vec3>& value)
    {
        int frame_count = buffer->ReadSigned32();
        if (frame_count)
        {
            value.m_keys.resize(frame_count);
            for (int i = 0; i != frame_count; ++i)
            {
                AnimationTrack<Math::vec3>::Frame f = buffer->ReadSigned32();
                Math::vec3 v;
                Math::LoadVector3f(buffer, v);
                value.m_keys[i] = std::pair<AnimationTrack<Math::vec3>::Frame, Math::vec3>(f, v);
            }
        }
    }

    void SaveAnimationTrack(System::Buffer* buffer, const AnimationTrack<Math::quat>& value)
    {
        int frame_count = value.m_keys.size();
        buffer->WriteSigned32(frame_count);
        if (frame_count)
        {
            for (auto& p : value.m_keys)
            {
                buffer->WriteSigned32(p.first);
                Math::SaveQuaternion(buffer, p.second);
            }
        }
    }

    void SaveAnimationTrack(System::Buffer* buffer, const AnimationTrack<Math::vec3>& value)
    {
        int frame_count = value.m_keys.size();
        buffer->WriteSigned32(frame_count);
        if (frame_count)
        {
            for (auto& p : value.m_keys)
            {
                buffer->WriteSigned32(p.first);
                Math::SaveVector3f(buffer, p.second);
            }
        }
    }

}

