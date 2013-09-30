/**********************************************************
*	File: mat3.h
*	Author: Mikalai Abramau
*	Desc: Implements a 3x3 matrix entity
***********************************************************/

#ifndef _H_MAT3X3_MATH
#define _H_MAT3X3_MATH

#include <initializer_list>
#include "../config.h"

namespace System
{
    class Buffer;
    class string;
}

namespace Math
{
    class quat;
    class vec3;
    class vec2;
    class mat2;

    class PUNK_ENGINE_API mat3
    {
    public:
        mat3();
        mat3(std::initializer_list<float> v);
        mat3(const mat3& m);
        mat3(float m0, float m1, float m2, float m3, float m4, float m5, float m6, float m7, float m8);
        mat3(const vec3& column0, const vec3& column1, const vec3& column2);
        void Save(System::Buffer* buffer) const;
        void Load(System::Buffer* buffer);
        mat3& operator = (const mat3& mat);
        float& operator [] (int i);
        const float& operator [] (int i) const;
        operator float*();
        operator const float*() const;
        mat3& operator += (const mat3& v);
        mat3& operator -= (const mat3& v);
        mat3& operator *= (float s);
        mat3& operator /= (float s);
        float Determinant() const;
        float At(int row, int col) const;
        float& At(int row, int col);
        mat3& SwapRows(int row1, int row2);
        mat3& Chop(float eps = float(0.00001));
        const mat3 Inversed() const;
        mat3& Inverse();
        mat3& SetColumn(int column, const vec3& v);
        mat3& SetRow(int row, const vec3& v);
        mat3& Identity();
        mat3& Zerofy();
        const vec2 TranslationPart() const;
        const mat2 RotationPart() const;
        const System::string ToString() const;
        const mat3 Transposed() const;
        mat3& Transpose();
        bool IsEqual(const mat3& m, float eps = 1e-6) const;
        static const mat3 Null();
        static const mat3 Create2DTranslate(float dx, float dy);
        static const mat3 Create2DTranslate(const vec2& v);
        static const mat3 Create2DRotate(float angle);
        static const mat3 CreateFreeForm2DRotate(float angle, float x, float y);
        static const mat3 CreateFreeForm2DRotate(float angle, const vec2& v);
        static const mat3 Create2DScale(float sx, float sy);
        static const mat3 Create2DScale(const vec2& v);
        static const mat3 CreateIdentity();
        static const mat3 Create2DFreeFormScale(float sx, float sy, const vec2& v);
        static const mat3 Create2DFreeFormScale(float sx, float sy, float x, float y);
        static const mat3 Create2DReflectionX();
        static const mat3 Create2DReflectionY();
        static const mat3 Create2DOriginReflection();
        static const mat3 CreateFromQuaternion(const quat& value);
    private:
        float m[9];
    };

    PUNK_ENGINE_API const mat3 operator * (const mat3& a, const mat3& b);
    PUNK_ENGINE_API const mat3 operator * (const float& s, const mat3& a);
    PUNK_ENGINE_API const mat3 operator * (const mat3& a, const float& s);
    PUNK_ENGINE_API const mat3 operator / (const mat3& a, const float& s);
    PUNK_ENGINE_API const mat3 operator + (const mat3& a, const mat3& b);
    PUNK_ENGINE_API const mat3 operator - (const mat3& a, const mat3& b);
    PUNK_ENGINE_API const mat3 MultTransposed(const vec3& a, const vec3& b);
    PUNK_ENGINE_API const vec3 operator * (const mat3& m, const vec3& v);
    PUNK_ENGINE_API bool operator == (const mat3& l, const mat3& r);
}

#endif  //  _H_MAT3X3_MATH
