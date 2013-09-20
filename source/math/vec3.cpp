#include "../system/buffer.h"
#include "vec3.h"

namespace Math
{
    vec3::vec3(const std::initializer_list<float>& v)
    {
        for (int i = 0; i < v.size() && i < 3; ++i)
        {
            m_v[i] = *(v.begin() + i);
        }
    }

    void vec3::Save(System::Buffer *buffer) const
    {
        for (int i = 0; i != 3; ++i)
        {
            buffer->WriteReal32(m_v[i]);
        }
    }

    void vec3::Load(System::Buffer *buffer)
    {
        for (int i = 0; i != 3; ++i)
        {
            m_v[i] = buffer->ReadReal32();
        }
    }

    void ivec3::Save(System::Buffer* buffer) const
    {
        for (int i = 0; i != 3; ++i)
        {
            buffer->WriteSigned32(m_v[i]);
        }
    }

    void ivec3::Load(System::Buffer* buffer)
    {
        for (int i = 0; i != 3; ++i)
        {
            m_v[i] = buffer->ReadSigned32();
        }
    }

    float vec3::Length() const
    {
        return sqrtf(m_v[0]*m_v[0]+m_v[1]*m_v[1]+m_v[2]*m_v[2]);
    }

    const vec3 vec3::Normalized() const
    {
        float length = Length();
        if (length == 0)
            return *this;
        return *this / length;
    }

    vec3& vec3::Normalize()
    {
        float length = Length();
        if (length == 0)
            return *this;
        m_v[0] /= length;
        m_v[1] /= length;
        m_v[2] /= length;
        return *this;
    }

    const vec3 vec3::Cross(const vec3& vec) const
    {
        vec3 v(
                    m_v[1] * vec.m_v[2] - m_v[2] * vec.m_v[1],
                m_v[2] * vec.m_v[0] - m_v[0] * vec.m_v[2],
                m_v[0] * vec.m_v[1] - m_v[1] * vec.m_v[0]);
        return v;
    }

}

