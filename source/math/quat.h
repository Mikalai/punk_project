#ifndef _H_QUAT_MATH
#define _H_QUAT_MATH

#include <initializer_list>
#include <iosfwd>
#include <cmath>
#include <stdexcept>
#include <stdio.h>
#include "../string/string.h"
#include "vec4.h"

namespace Math
{	
    class mat4;
    class mat3;

    class PUNK_ENGINE_API quat
	{
	public:
        quat();
        quat(std::initializer_list<float> list);
        quat(float w, float x, float y, float z);
        quat(float w, const vec3& v);
        quat(const quat& q);

        float& Scalar();
        vec3& Vector();
        const vec4 ToAngleAxis() const;
        const float& Scalar() const;
        const vec3& Vector() const;
        float& operator [] (int i);
        const float& operator[] (int i) const;
        void Set(float w, float x, float y, float z);
        float& W();
        const float& W() const;
        float& X();
        const float& X() const;
        float& Y();
        const float& Y() const;
        float& Z();
        const float& Z() const;
        const quat Inversed() const;
        quat& Inverse();
        const quat Conjugated() const;
        quat& Conjugate();
        quat& Normalize();
        const quat Normalized() const;
        float Length() const;
        float SquareLength() const;
        const System::string ToString() const;
        const vec3 Rotate(const vec3& v) const;
        const quat operator - () const;
        float Dot(const quat& q) const;
        bool IsEqual(const quat& q, float eps = 1e-5);

        quat& operator -= (const quat& v);
        quat& operator += (const quat& v);
        quat& operator *= (const quat& v);
        quat& operator *= (float v);
        quat& operator /= (float v);

        const mat4 ToMatrix4x4() const;
        const mat3 ToMatrix3x3() const;

        static const quat CreateFromAngleAxis(float angle, const vec3& axis);
        static const quat CreateFromMatrix4x4(const mat4& m);
        static const quat CreateFromMatrix3x3(const mat3& m);


    private:
        float m_v[4];
	};

    PUNK_ENGINE_API std::wostream& operator << (std::wostream& stream, const Math::quat& q);
    PUNK_ENGINE_API bool operator == (const quat& l, const quat& r);
    PUNK_ENGINE_API bool operator != (const quat& l, const quat& r);
    PUNK_ENGINE_API const quat operator + (const quat& q1, const quat& q2);
    PUNK_ENGINE_API const quat operator - (const quat& q1, const quat& q2);
    PUNK_ENGINE_API const quat operator * (const quat& q, const float& s);
    PUNK_ENGINE_API const quat operator * (const float& s, const quat& q);
    PUNK_ENGINE_API const quat operator / (const quat& q, const float& s);
    PUNK_ENGINE_API const quat operator * (const quat& q1, const quat& q2);

    PUNK_ENGINE_API void SaveQuaternion(System::Buffer* buffer, const quat& value);
    PUNK_ENGINE_API void LoadQuaternion(System::Buffer* buffer, quat& value);
}

#endif
