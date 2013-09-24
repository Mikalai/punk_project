#ifndef _H_PUNK_UTILITY_TRACK
#define _H_PUNK_UTILITY_TRACK

#include <ostream>
#include <istream>
#include <vector>
#include <algorithm>
#include "../../system/logger.h"
#include "../../system/serializable.h"
#include "../../math/interpolation.h"
#include "../../math/quat.h"
#include "../../math/vec3.h"

namespace Virtual
{
    template<class T>
    class AnimationTrack
    {
        typedef int Frame;
        typedef std::vector<std::pair<Frame, T>> Type;
        Type m_keys;
    public:
        void AddKey(int frame, const T& pos);
        const T GetKey(float frame) const;
        bool HasKeyAt(int frame);
        T& GetOriginalKey(int frame, bool& flag);
        const T& GetOriginalKey(int frame, bool& flag) const;
        std::wostream& out_formatted(std::wostream& stream);

        friend void SaveAnimationTrack(System::Buffer* buffer, const AnimationTrack<T>& value);
        friend void LoadAnimationTrack(System::Buffer* buffer, AnimationTrack<T>& value);
    };

    template<class T>
    inline T& AnimationTrack<T>::GetOriginalKey(int frame, bool& value)
    {
        return const_cast<T&>(static_cast<const AnimationTrack<T>&>(*this).GetOriginalKey(frame, value));
    }

    template<class T>
    inline const T& AnimationTrack<T>::GetOriginalKey(int frame, bool& flag) const
    {
        for (auto it = m_keys.begin(); it != m_keys.end(); ++it)
        {
            if (frame == it->first)
            {
                flag = true;
                return it->second;
            }
        }
        flag = false;
        return m_keys.begin()->second;
    }

    template<class T>
    inline bool AnimationTrack<T>::HasKeyAt(int frame)
    {
        for (auto it = m_keys.begin(); it != m_keys.end(); ++it)
        {
            if (it->first == frame)
                return true;
        }
        return false;
    }

    template<class T>
    inline void AnimationTrack<T>::AddKey(int frame, const T& v)
    {
        std::pair<Frame, T> p(frame, v);
        m_keys.push_back(p);
        /*auto it = m_keys.begin();
        for (; it != m_keys.end(); ++it)
        {
            if (p.first  it->first)
                break;
        }
        m_keys.insert(it, p);*/
    }

    template<class T>
    inline const T AnimationTrack<T>::GetKey(float frame) const
    {
        if (m_keys.empty())
            return T();

        if (m_keys.size() == 1)
            return (*m_keys.begin()).second;

        // parameter check
        if (frame < (float)(*m_keys.begin()).first)
        {
            frame = (float)(*m_keys.begin()).first;
        }

        float delta = float(m_keys.back().first - m_keys.front().first);
        float v = (frame - m_keys.front().first) / delta;
        v = modff(v, &v);
        frame = m_keys.front().first + delta * v;

        auto it1 = m_keys.begin();
        auto it2 = m_keys.begin();
        for (; it1 != m_keys.end() && frame >= (float)it1->first; ++it1);
        it2 = it1;
        --it1;
        if (it2 == m_keys.end())
            it2 = m_keys.begin();

        const T& p1 = it1->second;
        const T& p2 = it2->second;

        const T res = Math::linear_interpolation(p1, p2, (frame - it1->first) / (float)(it2->first - it1->first));
        return res;
    }

    template<>
    inline const Math::quat AnimationTrack<Math::quat>::GetKey(float frame) const
    {
        if (m_keys.empty())
            return Math::quat();

        if (m_keys.size() == 1)
            return (*m_keys.begin()).second;

        // parameter check
        if (frame < (float)(*m_keys.begin()).first)
        {
            frame = (float)(*m_keys.begin()).first;
        }

        float delta = float(m_keys.back().first - m_keys.front().first);
        float v = (frame - m_keys.front().first) / delta;
        v = modff(v, &v);
        frame = m_keys.front().first + delta * v;

        auto it1 = m_keys.begin();
        auto it2 = m_keys.begin();
        for (; it1 != m_keys.end() && frame >= (float)it1->first; ++it1);
        it2 = it1;
        --it1;

        if (it2 == m_keys.end())
            it2 = it1;

        const Math::quat& p1 = it1->second;
        const Math::quat& p2 = it2->second;

        const Math::quat res = Math::spherical_linear_interpolation(p1, p2, (frame - it1->first) / (float)(it2->first - it1->first));
        return res;
    }

    template<class T>
    inline std::wostream& AnimationTrack<T>::out_formatted(std::wostream& stream)
    {
        stream << Tab() << typeid(*this).name() << std::endl;
        Tab::Inc();
        for (auto key : m_keys)
        {
            stream << Tab() << key.first << ", ";
            stream << key.second.ToString();
            stream << std::endl;
        }
        stream << Tab::Dec() << typeid(*this).name();
        return stream;
    }

    PUNK_ENGINE_API void SaveAnimationTrack(System::Buffer* buffer, const AnimationTrack<Math::vec3>& value);
    PUNK_ENGINE_API void SaveAnimationTrack(System::Buffer* buffer, const AnimationTrack<Math::quat>& value);
    PUNK_ENGINE_API void LoadAnimationTrack(System::Buffer* buffer, AnimationTrack<Math::vec3>& value);
    PUNK_ENGINE_API void LoadAnimationTrack(System::Buffer* buffer, AnimationTrack<Math::quat>& value);
}

#endif
