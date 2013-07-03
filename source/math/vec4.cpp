#include "vec4.h"
#include "vec3.h"

namespace Math
{
    vec4::vec4()
        : Vector4<float>()
    {}

    vec4::vec4(float x, float y, float z, float w)
        : Vector4<float>(x, y, z, w)
    {}

    vec4::vec4(float x)
        : Vector4<float>(x)
    {}

    vec4::vec4(const vec4& origin, const vec4& destination)
        : Vector4<float>(origin, destination)
    {}

    vec4::vec4(const vec3& p, float d)
        : Vector4<float>(p, d)
    {}

    vec4::vec4(const vec4& vec)
        : Vector4<float>(vec)
    {}

    vec4::vec4(const Vector4<float>& vec)
        : Vector4<float>(vec)
    {}

    const vec3 vec4::ToHomogeneus() const
    {
        vec3 r;
        r[0] = X() / W();
        r[1] = Y() / W();
        r[2] = Z() / W();
        return r;
    }

    ivec4::ivec4()
        : Vector4<int>()
    {}

    ivec4::ivec4(int x, int y, int z, int w)
        : Vector4<int>(x, y, z, w)
    {}

    ivec4::ivec4(int x) : Vector4<int>(x)
    {}

    ivec4::ivec4(const ivec4& vec)
        : Vector4<int>(vec)
    {}

    ivec4::ivec4(const Vector4<int>& vec)
        : Vector4<int>(vec)
    {}
}
