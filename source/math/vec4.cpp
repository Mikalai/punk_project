#include "../system/buffer.h"
#include "constants.h"
#include "vec4.h"
#include "vec3.h"

namespace Math
{    
    vec4::vec4()
        : m_v{0,0,0,0}
    {}

    vec4::vec4(float x, float y, float z, float w)
        : m_v{x, y, z, w}
    {}

    vec4::vec4(float x)
        : m_v{x, x, x, x}
    {}

    vec4::vec4(const vec4& origin, const vec4& destination)
        : m_v{destination[0] - origin[0]
        , destination[1] - origin[1]
        , destination[2] - origin[2]
        , destination[3] - origin[3]}
    {}

    vec4::vec4(const vec3& p, float d)
        : m_v{p.X(), p.Y(), p.Z(), d}
    {}

    vec4::vec4(const vec4& vec)        
    {
        memcpy(m_v, vec.m_v, sizeof(vec));
    }

    const vec3 vec4::ToHomogeneus() const
    {
        vec3 r;
        r[0] = X() / W();
        r[1] = Y() / W();
        r[2] = Z() / W();
        return r;
    }

    float& vec4::operator[] (int i)
    {
        return m_v[i];
    }

    const float& vec4::operator[] (int i) const
    {
        return m_v[i];
    }

    vec4::operator float* ()
    {
        return m_v;
    }

    const float& vec4::X() const
    {
        return m_v[0];
    }

    float& vec4::X()
    {
        return m_v[0];
    }

    const float& vec4::Y() const
    {
        return m_v[1];
    }

    float& vec4::Y()
    {
        return m_v[1];
    }

    const float& vec4::Z() const
    {
        return m_v[2];
    }

    float& vec4::Z()
    {
        return m_v[2];
    }

    const float& vec4::W() const
    {
        return m_v[3];
    }

    float& vec4::W()
    {
        return m_v[3];
    }

    vec4& vec4::operator = (const vec4& vec)
    {
#ifdef _WIN32
        memcpy_s(m_v, sizeof(m_v), vec.m_v, sizeof(m_v));
#else
        memcpy(m_v, vec.m_v, sizeof(m_v));
#endif
        return *this;
    }

    vec4& vec4::operator /= (const float& v)
    {
        for (int i = 0; i < Size_c; i++)
        {
            float t = m_v[i] / v;
            m_v[i] = (fabs(v) < Eps) ? 0 : t;
        }
        return *this;
    }

    vec4& vec4::operator += (const vec4& v)
    {
        for (int i = 0; i < Size_c; i++)
        {
            m_v[i] += v[i];
        }
        return *this;
    }

    vec4& vec4::operator -= (const vec4& v)
    {
        for (int i = 0; i < Size_c; i++)
        {
            m_v[i] -= v[i];
        }
        return *this;
    }

    vec4& vec4::operator *= (const float& v)
    {
        for (int i = 0; i < Size_c; i++)
        {
            float t = m_v[i] * v;
            m_v[i] = (fabs(v) < Eps) ? 0 : t;
        }
        return *this;
    }

    float vec4::Length() const
    {
        //
        //	it will always convert to float
        //
        return static_cast<float>(sqrtf(float(m_v[0]*m_v[0]+m_v[1]*m_v[1]+m_v[2]*m_v[2]+m_v[3]*m_v[3])));
    }

    const vec4 vec4::Normalized() const
    {
        float length = Length();
        vec4 res(*this);
        res *= float(1) / length;
        return res;
    }

    vec4& vec4::Normalize()
    {
        double length = Length();
        for (int i = 0; i < Size_c; i++)
        {
            m_v[i] /= (float)length;
        }
        return *this;
    }

    float vec4::Dot(const vec4& vec) const
    {
        return m_v[0] * vec.m_v[0] + m_v[1] * vec.m_v[1] + m_v[2] * vec.m_v[2] + m_v[3] * vec.m_v[3];
    }

    void vec4::Set(float x)
    {
        m_v[0] = (fabs(x) < Eps) ? 0 : x;
        m_v[1] = (fabs(x) < Eps) ? 0 : x;
        m_v[2] = (fabs(x) < Eps) ? 0 : x;
        m_v[3] = (fabs(x) < Eps) ? 0 : x;
    }

    void vec4::Set(float x, float y, float z, float w)
    {
        m_v[0] = (fabs(x) < Eps) ? 0 : x;
        m_v[1] = (fabs(y) < Eps) ? 0 : y;
        m_v[2] = (fabs(z) < Eps) ? 0 : z;
        m_v[3] = (fabs(w) < Eps) ? 0 : w;
    }

    const vec4 vec4::ComponentMul(const vec4& v)
    {
        return vec4(m_v[0]*v[0], m_v[1]*v[1], m_v[2]*v[2], m_v[3]*v[3]);
    }

    const System::string vec4::ToString() const
    {
        return System::string("({0:.3}; {1:.3}; {2:.3}; {3:.3})").arg(m_v[0]).arg(m_v[1]).arg(m_v[2]).arg(m_v[3]);
    }

    const vec2 vec4::XY() const
    {
        return vec2(m_v[0], m_v[1]);
    }

    const vec2 vec4::YX() const
    {
        return vec2(m_v[1], m_v[0]);
    }

    const vec2 vec4::XZ() const
    {
        return vec2(m_v[0], m_v[2]);
    }

    const vec2 vec4::ZX() const
    {
        return vec2(m_v[2], m_v[0]);
    }

    const vec2 vec4::YZ() const
    {
        return vec2(m_v[1], m_v[2]);
    }

    const vec2 vec4::ZY() const
    {
        return vec2(m_v[2], m_v[1]);
    }

    const vec2 vec4::XW() const
    {
        return vec2(m_v[0], m_v[3]);
    }

    const vec2 vec4::WX() const
    {
        return vec2(m_v[3], m_v[0]);
    }

    const vec2 vec4::WZ() const
    {
        return vec2(m_v[3], m_v[2]);
    }

    const vec2 vec4::ZW() const
    {
        return vec2(m_v[2], m_v[3]);
    }

    const vec2 vec4::YW() const
    {
        return vec2(m_v[1], m_v[3]);
    }

    const vec2 vec4::WY() const
    {
        return vec2(m_v[3], m_v[1]);
    }

    const vec3 vec4::XYZ() const
    {
        return vec3(m_v[0], m_v[1], m_v[2]);
    }

    const vec3 vec4::XZY() const
    {
        return vec3(m_v[0], m_v[2], m_v[1]);
    }

    const vec3 vec4::YXZ() const
    {
        return vec3(m_v[1], m_v[0], m_v[2]);
    }

    const vec3 vec4::YZX() const
    {
        return vec3(m_v[1], m_v[2], m_v[0]);
    }

    const vec3 vec4::ZXY() const
    {
        return vec3(m_v[2], m_v[0], m_v[1]);
    }

    const vec3 vec4::ZYX() const
    {
        return vec3(m_v[2], m_v[1], m_v[0]);
    }

    const vec4 vec4::XYZW() const
    {
        return vec4(m_v[0], m_v[1], m_v[2], m_v[3]);
    }

    const vec4 vec4::XYWZ() const
    {
        return vec4(m_v[0], m_v[1], m_v[3], m_v[2]);
    }

    const vec4 vec4::XZYW() const
    {
        return vec4(m_v[0], m_v[2], m_v[1], m_v[3]);
    }

    const vec4 vec4::XZWY() const
    {
        return vec4(m_v[0], m_v[2], m_v[3], m_v[1]);
    }

    const vec4 vec4::XWYZ() const
    {
        return vec4(m_v[0], m_v[3], m_v[1], m_v[2]);
    }

    const vec4 vec4::XWZY() const
    {
        return vec4(m_v[0], m_v[3], m_v[2], m_v[1]);
    }

    const vec4 vec4::YXZW() const
    {
        return vec4(m_v[1], m_v[0], m_v[2], m_v[3]);
    }

    const vec4 vec4::YXWZ() const
    {
        return vec4(m_v[1], m_v[0], m_v[3], m_v[2]);
    }

    const vec4 vec4::YZXW() const
    {
        return vec4(m_v[1], m_v[2], m_v[0], m_v[3]);
    }

    const vec4 vec4::YZWX() const
    {
        return vec4(m_v[1], m_v[2], m_v[3], m_v[0]);
    }

    const vec4 vec4::YWZX() const
    {
        return vec4(m_v[1], m_v[3], m_v[2], m_v[0]);
    }

    const vec4 vec4::YWXZ() const
    {
        return vec4(m_v[1], m_v[3], m_v[0], m_v[2]);
    }


    const vec4 vec4::ZXYW() const
    {
        return vec4(m_v[2], m_v[0], m_v[1], m_v[3]);
    }

    const vec4 vec4::ZXWY() const
    {
        return vec4(m_v[2], m_v[0], m_v[3], m_v[1]);
    }

    const vec4 vec4::ZYXW() const
    {
        return vec4(m_v[2], m_v[1], m_v[0], m_v[3]);
    }

    const vec4 vec4::ZYWX() const
    {
        return vec4(m_v[2], m_v[1], m_v[3], m_v[0]);
    }

    const vec4 vec4::ZWXY() const
    {
        return vec4(m_v[2], m_v[3], m_v[0], m_v[1]);
    }

    const vec4 vec4::ZWYX() const
    {
        return vec4(m_v[2], m_v[3], m_v[1], m_v[0]);
    }

    const vec4 vec4::WXYZ() const
    {
        return vec4(m_v[3], m_v[0], m_v[1], m_v[2]);
    }

    const vec4 vec4::WXZY() const
    {
        return vec4(m_v[3], m_v[0], m_v[2], m_v[1]);
    }

    const vec4 vec4::WYXZ() const
    {
        return vec4(m_v[3], m_v[1], m_v[0], m_v[2]);
    }

    const vec4 vec4::WYZX() const
    {
        return vec4(m_v[3], m_v[1], m_v[2], m_v[0]);
    }

    const vec4 vec4::WZXY() const
    {
        return vec4(m_v[3], m_v[2], m_v[0], m_v[1]);
    }

    const vec4 vec4::WZYX() const
    {
        return vec4(m_v[3], m_v[2], m_v[1], m_v[0]);
    }


    const vec4 operator + (const vec4& a, const vec4& b)
    {
        return vec4(a[0] + b[0], a[1] + b[1], a[2] + b[2], a[3] + b[3]);
    }

    const vec4 operator - (const vec4& a, const vec4& b)
    {
        return vec4(a[0] - b[0], a[1] - b[1], a[2] - b[2], a[3] - b[3]);
    }

    const vec4 operator *(const vec4& a, float d)
    {
        return vec4(a[0] * d, a[1] * d, a[2] * d, a[3] * d);
    }

    const vec4 operator *(float d, const vec4& a)
    {
        return vec4(a[0] * d, a[1] * d, a[2] * d, a[3] * d);
    }

    const vec4 operator /(const vec4& a, double d)
    {
        return vec4(a[0] / d, a[1] / d, a[2] / d, a[3] / d);
    }

    bool operator ==(const vec4& a, const vec4& b)
    {
        return a[0] == b[0] && a[1] == b[1] && a[2] == b[2] && a[3] == b[3];
    }

    bool operator !=(const vec4& a, const vec4& b)
    {
        return !(a == b);
    }

    void SaveVector4f(System::Buffer *buffer, const vec4 &value)
    {
        buffer->WriteBuffer(&value[0], sizeof(value));
    }

    void LoadVector4f(System::Buffer *buffer, vec4 &value)
    {
        buffer->WriteBuffer(&value[0], sizeof(value));
    }

    ivec4::ivec4()
        : m_v{0,0,0,0}
    {}

    ivec4::ivec4(int x, int y, int z, int w)
        : m_v{x, y, z, w}
    {}

    ivec4::ivec4(int x)
        : m_v{x, x, x, x}
    {}

    ivec4::ivec4(const ivec4& vec)        
    {
        memcpy(m_v, vec.m_v, sizeof(vec));
    }

    int& ivec4::operator [] (int i)
    {
        return m_v[i];
    }

    const int& ivec4::operator [] (int i) const
    {
        return m_v[i];
    }

    void ivec4::Set(int x, int y, int z, int w)
    {
        m_v[0] = x;
        m_v[1] = y;
        m_v[2] = z;
        m_v[3] = w;
    }
}
