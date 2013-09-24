/*
MODULE FOR WORKING WITH 4 DIMENSIONAL VECTOR
AUTHOR: Mikalai Abramau
*/

#ifndef _H_PUNK_MATH_VEC4
#define _H_PUNK_MATH_VEC4

#include "../config.h"
#include <iosfwd>
#include <stdio.h>
#include <cmath>

namespace System
{
    class string;
    class Buffer;
}

namespace Math
{
    class vec3;
    class vec2;

    class PUNK_ENGINE_API vec4
    {
    public:
        vec4();
        vec4(float x, float y, float z, float w);
        vec4(float x);
        vec4(const vec4& origin, const vec4& destination);
        vec4(const vec3& p, float d = 1);
        vec4(const vec4& vec);
        const vec3 ToHomogeneus() const;
        float& operator[] (int i);
        const float& operator[] (int i) const;
        operator float* ();
        const float& X() const;
        float& X();
        const float& Y() const;
        float& Y();
        const float& Z() const;
        float& Z();
        const float& W() const;
        float& W();
        vec4& operator = (const vec4& vec);
        vec4& operator /= (const float& v);
        vec4& operator += (const vec4& v);
        vec4& operator -= (const vec4& v);
        vec4& operator *= (const float& v);
        float Length() const;
        const vec4 Normalized() const;
        vec4& Normalize();
        float Dot(const vec4& vec) const;
        void Set(float x);
        void Set(float x, float y, float z, float w);
        const vec4 ComponentMul(const vec4& v);
        const System::string ToString() const;
        const vec2 XY() const;
        const vec2 YX() const;
        const vec2 XZ() const;
        const vec2 ZX() const;
        const vec2 YZ() const;
        const vec2 ZY() const;
        const vec2 XW() const;
        const vec2 WX() const;
        const vec2 WZ() const;
        const vec2 ZW() const;
        const vec2 YW() const;
        const vec2 WY() const;
        const vec3 XYZ() const;
        const vec3 XZY() const;
        const vec3 YXZ() const;
        const vec3 YZX() const;
        const vec3 ZXY() const;
        const vec3 ZYX() const;
        const vec4 XYZW() const;
        const vec4 XYWZ() const;
        const vec4 XZYW() const;
        const vec4 XZWY() const;
        const vec4 XWYZ() const;
        const vec4 XWZY() const;
        const vec4 YXZW() const;
        const vec4 YXWZ() const;
        const vec4 YZXW() const;
        const vec4 YZWX() const;
        const vec4 YWZX() const;
        const vec4 YWXZ() const;
        const vec4 ZXYW() const;
        const vec4 ZXWY() const;
        const vec4 ZYXW() const;
        const vec4 ZYWX() const;
        const vec4 ZWXY() const;
        const vec4 ZWYX() const;
        const vec4 WXYZ() const;
        const vec4 WXZY() const;
        const vec4 WYXZ() const;
        const vec4 WYZX() const;
        const vec4 WZXY() const;
        const vec4 WZYX() const;
    private:
        static const int Size_c = 4;
        float m_v[Size_c];
    };

    PUNK_ENGINE_API const vec4 operator + (const vec4& a, const vec4& b);
    PUNK_ENGINE_API const vec4 operator - (const vec4& a, const vec4& b);
    PUNK_ENGINE_API const vec4 operator *(const vec4& a, float d);
    PUNK_ENGINE_API const vec4 operator *(float d, const vec4& a);
    PUNK_ENGINE_API const vec4 operator /(const vec4& a, double d);
    PUNK_ENGINE_API bool operator ==(const vec4& a, const vec4& b);
    PUNK_ENGINE_API bool operator !=(const vec4& a, const vec4& b);
    PUNK_ENGINE_API void SaveVector4f(System::Buffer* buffer, const vec4& value);
    PUNK_ENGINE_API void LoadVector4f(System::Buffer* buffer, vec4& value);

    class PUNK_ENGINE_API ivec4
    {
    public:
        ivec4();
        ivec4(int x, int y, int z, int w);
        ivec4(int x);
        ivec4(const ivec4& vec);
        int& operator[] (int i);
        const int& operator[] (int i) const;
        void Set(int x, int y, int z, int w);
    private:
        static const int Size_c = 4;
        int m_v[Size_c];
    };
}

#endif  //  _H_PUNK_MATH_VEC4
