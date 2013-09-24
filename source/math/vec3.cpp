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

    const vec3 vec3::Null()
    {
        return vec3(0,0,0);
    }

    vec3::vec3(const vec3& vec)
    {
        m_v[0] = vec.m_v[0];
        m_v[1] = vec.m_v[1];
        m_v[2] = vec.m_v[2];
    }

    vec3::vec3()
    {
        memset(m_v, 0, sizeof(m_v));
    }

    vec3::vec3(float x, float y, float z)
    {
        m_v[0] = x;
        m_v[1] = y;
        m_v[2] = z;
    }

    vec3::vec3(const vec3& origin, const vec3& destination)
    {
        for (int i = 0; i < Size_c; i++)
        {
            m_v[i] = destination[i] - origin[i];
        }
    }

    const float& vec3::X() const
    {
        return m_v[0];
    }

    float& vec3::X()
    {
        return m_v[0];
    }

    float vec3::Length() const
    {
        auto sqr_l = m_v[0]*m_v[0] + m_v[1]*m_v[1] + m_v[2]*m_v[2];
        auto res = sqrt(sqr_l);
        return res;
    }

    const vec3 vec3::Normalized() const
    {
        auto p = *this;
        auto l = Length();
        return p / l;
    }

    const float& vec3::Y() const
    {
        return m_v[1];
    }

    float& vec3::Y()
    {
        return m_v[1];
    }

    const float& vec3::Z() const
    {
        return m_v[2];
    }

    float& vec3::Z()
    {
        return m_v[2];
    }

    const vec3 vec3::Negated() const
    {
        return vec3(-m_v[0], -m_v[1], -m_v[2]);
    }

    vec3& vec3::Negate()
    {
        m_v[0] = -m_v[0];
        m_v[1] = -m_v[1];
        m_v[2] = -m_v[2];

        return *this;
    }

    const vec3 vec3::Cross(const vec3& vec) const
    {
        vec3 v( m_v[1] * vec.m_v[2] - m_v[2] * vec.m_v[1],
                m_v[2] * vec.m_v[0] - m_v[0] * vec.m_v[2],
                m_v[0] * vec.m_v[1] - m_v[1] * vec.m_v[0]);
        return v;
    }

    vec3& vec3::Chop(float eps)
    {
        for (int i = 0; i != 3; ++i)
            if (fabs(float(m_v[i])) < eps)
                m_v[i] = float(0);
        return *this;
    }

    const vec3 vec3::ComponentMult(const vec3& v) const
    {
        return vec3(m_v[0]*v[0], m_v[1]*v[1], m_v[2]*v[2]);
    }

    const vec2 vec3::XY() const
    {
        return vec2(m_v[0], m_v[1]);
    }

    const vec2 vec3::YX() const
    {
        return vec2(m_v[1], m_v[0]);
    }

    const vec2 vec3::XZ() const
    {
        return vec2(m_v[0], m_v[2]);
    }

    const vec2 vec3::ZX() const
    {
        return vec2(m_v[2], m_v[0]);
    }

    const vec2 vec3::YZ() const
    {
        return vec2(m_v[1], m_v[2]);
    }

    const vec2 vec3::ZY() const
    {
        return vec2(m_v[2], m_v[1]);
    }

    const vec3 vec3::XYZ() const
    {
        return vec3(m_v[0], m_v[1], m_v[2]);
    }

    const vec3 vec3::XZY() const
    {
        return vec3(m_v[0], m_v[2], m_v[1]);
    }

    const vec3 vec3::YXZ() const
    {
        return vec3(m_v[1], m_v[0], m_v[2]);
    }

    const vec3 vec3::YZX() const
    {
        return vec3(m_v[1], m_v[2], m_v[0]);
    }

    const vec3 vec3::ZXY() const
    {
        return vec3(m_v[2], m_v[0], m_v[1]);
    }

    const vec3 vec3::ZYX() const
    {
        return vec3(m_v[2], m_v[1], m_v[0]);
    }

    vec3& vec3::Nullify()
    {
        memset(m_v, 0, sizeof(m_v));
        return *this;
    }

    vec3& vec3::operator += (const vec3& vec)
    {
        m_v[0] += vec.m_v[0];
        m_v[1] += vec.m_v[1];
        m_v[2] += vec.m_v[2];
        return *this;
    }

    vec3& vec3::operator -= (const vec3& vec)
    {
        m_v[0] -= vec.m_v[0];
        m_v[1] -= vec.m_v[1];
        m_v[2] -= vec.m_v[2];
        return *this;
    }

    vec3& vec3::operator *= (float value)
    {
        m_v[0] *= value;
        m_v[1] *= value;
        m_v[2] *= value;
        return *this;
    }

    vec3& vec3::operator /= (float value)
    {
        m_v[0] /= value;
        m_v[1] /= value;
        m_v[2] /= value;
        return *this;
    }

    float& vec3::operator [] (int i)
    {
        return m_v[i];
    }

    const float& vec3::operator [] (int i) const
    {
        return m_v[i];
    }

    float vec3::SquareLength() const
    {
        return m_v[0]*m_v[0]+m_v[1]*m_v[1]+m_v[2]*m_v[2];
    }

    void vec3::Set(float x, float y, float z)
    {
        m_v[0] = x;
        m_v[1] = y;
        m_v[2] = z;
    }

    float vec3::Dot(const vec3& a) const
    {
        return m_v[0] * a.m_v[0] + m_v[1] * a.m_v[1] + m_v[2] * a.m_v[2];
    }

    vec3& vec3::operator = (const vec3& vec)
    {
        memcpy(m_v, vec.m_v, sizeof(m_v));
        return *this;
    }

    const vec3 vec3::operator -()  const
    {
        return vec3(-m_v[0], -m_v[1], -m_v[2]);
    }

    System::string vec3::ToString() const
    {
        return System::string("({0}; {1}; {2})").arg(m_v[0]).arg(m_v[1]).arg(m_v[2]);
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

    const vec3 operator + (const vec3& a, const vec3& b)
    {
        vec3 res = vec3(a[0] + b[0], a[1] + b[1], a[2] + b[2]);
        return res;
    }

    const vec3 operator -(const vec3& a, const vec3& b)
    {
        return vec3(a[0] - b[0], a[1] - b[1], a[2] - b[2]);
    }

    const vec3 operator *(const vec3& a, float d)
    {
        return vec3(a[0] * d, a[1] * d, a[2] * d);
    }

    const vec3 operator *(float d, const vec3& a)
    {
        return vec3(a[0] * d, a[1] * d, a[2] * d);
    }

    const vec3 operator *(const vec3& a, const vec3& b)
    {
        return vec3(a[0] * b[0], a[1] * b[1], a[2] * b[2]);
    }

    const vec3 operator /(const vec3& a, float d)
    {
        return vec3(a[0] / d, a[1] / d, a[2] / d);
    }

    bool operator ==(const vec3& a, const vec3& b)
    {
        return a[0] == b[0] && a[1] == b[1] && a[2] == b[2];
    }

    bool operator !=(const vec3& a, const vec3& b)
    {
        return !(a == b);
    }

    void SaveVector3i(System::Buffer *buffer, const ivec3 &value)
    {
        buffer->WriteBuffer(&value[0], sizeof(value));
    }

    void LoadVector3i(System::Buffer *buffer, ivec3 &value)
    {
        buffer->ReadBuffer(&value[0], sizeof(value));
    }

    void SaveVector3f(System::Buffer *buffer, const vec3 &value)
    {
        buffer->WriteBuffer(&value[0], sizeof(value));
    }

    void LoadVector3f(System::Buffer *buffer, vec3 &value)
    {
        buffer->ReadBuffer(&value[0], sizeof(value));
    }

    ivec3::ivec3()
        : m_v{0,0,0}
    {}

    ivec3::ivec3(int x, int y, int z)
        : m_v{x, y, z}
    {}

    ivec3::ivec3(const ivec3& vec)        
    {
        memcpy(m_v, vec.m_v, sizeof(m_v));
    }

    const int& ivec3::X() const
    {
        return m_v[0];
    }

    int& ivec3::X()
    {
        return m_v[0];
    }

    const int& ivec3::Y() const
    {
        return m_v[1];
    }

    int& ivec3::Y()
    {
        return m_v[1];
    }

    const int& ivec3::Z() const
    {
        return m_v[2];
    }

    int& ivec3::Z()
    {
        return m_v[2];
    }

    int& ivec3::operator [] (int i)
    {
        return m_v[i];
    }

    const int& ivec3::operator [] (int i) const
    {
        return m_v[i];
    }

    void ivec3::Set(int x, int y, int z)
    {
        m_v[0] = x;
        m_v[1] = y;
        m_v[2] = z;
    }
}

