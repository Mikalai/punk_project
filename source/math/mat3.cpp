#include "../system/buffer.h"
#include "../system/errors/module.h"
#include "mat2.h"
#include "vec3.h"
#include "quat.h"
#include "mat3.h"

namespace Math
{

    const mat3 mat3::CreateFromQuaternion(const quat& q)
    {
        float wx, wy, wz, xx, yy, yz, xy, xz, zz, x2, y2, z2;
        x2 = q[0] + q[0];
        y2 = q[1] + q[1];
        z2 = q[2] + q[2];
        xx = q[0] * x2;   xy = q[0] * y2;   xz = q[0] * z2;
        yy = q[1] * y2;   yz = q[1] * z2;   zz = q[2] * z2;
        wx = q[3] * x2;   wy = q[3] * y2;   wz = q[3] * z2;
        mat3 mat;
        float* m = &mat[0];
        m[0*3 + 0]=1.0f-(yy+zz); m[0*3 + 1]=xy-wz;        m[0*2 + 2]=xz+wy;
        m[1*3 + 0]=xy+wz;        m[1*3 + 1]=1.0f-(xx+zz); m[1*2 + 2]=yz-wx;
        m[2*3 + 0]=xz-wy;        m[2*3 + 1]=yz+wx;        m[2*2 + 2]=1.0f-(xx+yy);
        return mat;
    }

    mat3::mat3(float m0, float m1, float m2, float m3, float m4, float m5, float m6, float m7, float m8)
    {
        m[0] = m0;
        m[1] = m1;
        m[2] = m2;
        m[3] = m3;
        m[4] = m4;
        m[5] = m5;
        m[6] = m6;
        m[7] = m7;
        m[8] = m8;
    }

    mat3::mat3(const vec3& column0, const vec3& column1, const vec3& column2)
    {
        m[0] = column0[0];
        m[1] = column0[1];
        m[2] = column0[2];
        m[3] = column1[0];
        m[4] = column1[1];
        m[5] = column1[2];
        m[6] = column2[0];
        m[7] = column2[1];
        m[8] = column2[2];
    }

    mat3::mat3()
    {
        memset(m, 0, sizeof(m));
        m[0] = m[4] = m[8] = float(1);
    }

    mat3::mat3(std::initializer_list<float> v)
    {
        int i = 0;
        for (auto e : v)
        {
            m[i++] = e;
            if (i == 9)
                break;
        }
    }

    mat3::mat3(const mat3& mat)
    {
        if (this != &mat)
        {
            memcpy(m, mat.m, sizeof(m));
        }
    }

    mat3& mat3::operator = (const mat3& mat)
    {
        if (this != &mat)
        {
            memcpy(m, mat.m, sizeof(m));
        }
        return *this;
    }

    float& mat3::operator [] (int i)
    {
        if (i < 0 || i > 8)
            throw System::PunkException("Index out of range");

        return m[i];
    }

    const float& mat3::operator [] (int i) const
    {
        if (i < 0 || i > 8)
            throw System::PunkException("Index out of range");
        return m[i];
    }


    mat3::operator float*()
    {
        return m;
    }

    mat3::operator const float*() const
    {
        return m;
    }

    mat3& mat3::operator += (const mat3& v)
    {
        for (int i = 0; i < 9; ++i)
            m[i] += v[i];
        return *this;
    }

    mat3& mat3::operator -= (const mat3& v)
    {
        for (int i = 0; i < 9; ++i)
            m[i] -= v[i];
        return *this;
    }

    mat3& mat3::operator *= (float s)
    {
        for (int i = 0; i < 9; i++)
            m[i] *= s;

        return *this;
    }

    mat3& mat3::operator /= (float s)
    {
        s = float(1) / s;
        for (int i = 0; i < 9; i++)
            m[i] *= s;

        return *this;
    }

    //
    //  find determinant
    //
    float mat3::Determinant() const
    {
        return m[0] * (m[4] * m[8] - m[5] * m[7])
                - m[1] * (m[3] * m[8] - m[5] * m[6])
                + m[2] * (m[3] * m[7] - m[4] * m[6]);
    }

    float mat3::At(int row, int col) const
    {
        return m[col*3 + row];
    }

    float& mat3::At(int row, int col)
    {
        return m[col*3 + row];
    }

    mat3& mat3::SwapRows(int row1, int row2)
    {
        int size = 3;
        for (int col = 0; col < size; ++col)
            std::swap(At(row1, col), At(row2, col));
        return *this;
    }

    mat3& mat3::Chop(float eps)
    {
        for (int i = 0; i != 9; ++i)
            if (fabs(m[i]) < eps)
                m[i] = float(0);
        return *this;
    }

    //
    //	returned inversed copy
    //
    const mat3 mat3::Inversed() const
    {
        mat3 inversedMatrix;
        inversedMatrix[0] = m[4] * m[8] - m[5] * m[7];
        inversedMatrix[1] = -(m[1] * m[8] - m[2] * m[7]);
        inversedMatrix[2] = m[1] * m[5] - m[2] * m[4];
        inversedMatrix[3] = -(m[3] * m[8] - m[5] * m[6]);
        inversedMatrix[4] = m[0] * m[8] - m[2] * m[6];
        inversedMatrix[5] = -(m[0] * m[5] - m[2] * m[3]);
        inversedMatrix[6] = m[3] * m[7] - m[4] * m[6];
        inversedMatrix[7] = -(m[0] * m[7] - m[1] * m[6]);
        inversedMatrix[8] = m[0] * m[4] - m[1] * m[3];

        float d = Determinant();

        if (d == float(0))
            throw System::PunkException("Can't inverse matrix. Determinant is 0");

        return inversedMatrix / d;
    }

    mat3& mat3::Inverse()
    {
        float d = Determinant();
        float tm[9];

        tm[0] = m[4] * m[8] - m[5] * m[7];
        tm[1] = -(m[1] * m[8] - m[2] * m[7]);
        tm[2] = m[1] * m[5] - m[2] * m[4];
        tm[3] = -(m[3] * m[8] - m[5] * m[6]);
        tm[4] = m[0] * m[8] - m[2] * m[6];
        tm[5] = -(m[0] * m[5] - m[2] * m[3]);
        tm[6] = m[3] * m[7] - m[4] * m[6];
        tm[7] = -(m[0] * m[7] - m[1] * m[6]);
        tm[8] = m[0] * m[4] - m[1] * m[3];

        memcpy(m, tm, sizeof(m));

        if (d == float(0))
            throw System::PunkException("Can't inverse matrix. Determinant is 0");

        return *this /= d;
    }

    mat3& mat3::SetColumn(int column, const vec3& v)
    {
        for (int i = 0; i < 3; i++)
        {
            m[column * 3 + i] = v[i];
        }
        return *this;
    }

    mat3& mat3::SetRow(int row, const vec3& v)
    {
        for (int i = 0; i < 3; ++i)
            m[3*i + row] = v[i];
        return *this;
    }

    mat3& mat3::Identity()
    {
        float tm[9] = {1, 0, 0,
                       0, 1, 0,
                       0, 0, 1};

        memcpy(m, tm, sizeof(m));

        return *this;
    }

    mat3& mat3::Zerofy()
    {
        memset(m, 0, sizeof(m));
        return *this;
    }

    const vec2 mat3::TranslationPart() const
    {
        return vec2(m[6], m[7]);
    }

    const mat2 mat3::RotationPart() const
    {
        mat2 tm;
        tm[0] = m[0];
        tm[1] = m[1];
        tm[2] = m[3];
        tm[3] = m[4];
        return tm;
    }

    const System::string mat3::ToString() const
    {
        return System::string(L"\n {0:7.3} {1:7.3} %{2:7.3}\n {3:7.3} {4:7.3} {5:7.3}\n{6:7.3} %{7:7.3} {8:7.3}\n").arg(m[0])
                .arg(m[3]).arg(m[6]).arg(m[1]).arg(m[4]).arg(m[7]).arg(m[2]).arg(m[5]).arg(m[8]);
    }

    //	0 3 6
    //	1 4 7
    //	2 5 8
    const mat3 mat3::Transposed() const
    {
        mat3 res;
        res.m[1] = m[3];
        res.m[3] = m[1];
        res.m[6] = m[2];
        res.m[2] = m[6];
        res.m[5] = m[7];
        res.m[7] = m[5];
        res.m[0] = m[0];
        res.m[4] = m[4];
        res.m[8] = m[8];
        return res;
    }

    mat3& mat3::Transpose()
    {
        float tm[9];
        tm[1] = m[3];
        tm[3] = m[1];
        tm[6] = m[2];
        tm[2] = m[6];
        tm[5] = m[7];
        tm[7] = m[5];
        tm[0] = m[0];
        tm[4] = m[4];
        tm[8] = m[8];

        memcpy(m, tm, sizeof(tm));
        return *this;
    }

    const mat3 mat3::Null()
    {
        mat3 res;
        memset(&res, 0, sizeof(res));
        return res;
    }

    const mat3 mat3::Create2DTranslate(float dx, float dy)
    {
        mat3 res;
        res[0] = res[4] = res[8] = float(1);
        res[6] = dx;
        res[7] = dy;
        return res;
    }


    const mat3 mat3::Create2DTranslate(const vec2& v)
    {
        return Create2DTranslate(v.X(), v.Y());
    }

    const mat3 mat3::Create2DRotate(float angle)
    {
        mat3 res;
        res[0] = cos(angle);
        res[1] = sin(angle);
        res[2] = 0;
        res[3] = -sin(angle);
        res[4] = cos(angle);
        res[5] = 0;
        res[6] = 0;
        res[7] = 0;
        res[8] = 1;
        return res;
    }

    const mat3 mat3::CreateFreeForm2DRotate(float angle, float x, float y)
    {
        return Create2DTranslate(x, y) * Create2DRotate(angle) * Create2DTranslate(x, y).Inversed();
    }

    const mat3 mat3::CreateFreeForm2DRotate(float angle, const vec2& v)
    {
        return CreateFreeForm2DRotate(angle, v.X(), v.Y());
    }

    const mat3 mat3::Create2DScale(float sx, float sy)
    {
        mat3 m;
        m[0] = sx;
        m[4] = sy;
        m[8] = 1;
        return m;
    }

    const mat3 mat3::Create2DScale(const vec2& v)
    {
        return Create2DScale(v[0], v[1]);
    }

    const mat3 mat3::CreateIdentity()
    {
        return mat3();
    }

    const mat3 mat3::Create2DFreeFormScale(float sx, float sy, const vec2& v)
    {
        return Create2DTranslate(v) * Create2DScale(sx, sy) * Create2DTranslate(v).Inversed();
    }

    const mat3 mat3::Create2DFreeFormScale(float sx, float sy, float x, float y)
    {
        return Create2DTranslate(x, y) * Create2DScale(sx, sy) * Create2DTranslate(x, y).Inversed();
    }

    const mat3 mat3::Create2DReflectionX()
    {
        mat3 m;
        m[0] = 1;
        m[4] = -1;
        m[8] = 1;
        return m;
    }

    const mat3 mat3::Create2DReflectionY()
    {
        mat3 m;
        m[0] = -1;
        m[4] = 1;
        m[8] = 1;
        return m;
    }

    const mat3 mat3::Create2DOriginReflection()
    {
        mat3 m;
        m[0] = -1;
        m[4] = -1;
        m[8] = 1;
        return m;
    }

    const mat3 operator *(const mat3& a, const mat3& b)
    {
        mat3 c;
        c.SetColumn(0, vec3(
                        b[0] * a[0] + b[1] * a[3] + b[2] * a[6],
                b[0] * a[1] + b[1] * a[4] + b[2] * a[7],
                b[0] * a[2] + b[1] * a[5] + b[2] * a[8]));
        c.SetColumn(1, vec3(
                        b[3] * a[0] + b[4] * a[3] + b[5] * a[6],
                b[3] * a[1] + b[4] * a[4] + b[5] * a[7],
                b[3] * a[2] + b[4] * a[5] + b[5] * a[8]));
        c.SetColumn(2, vec3(
                        b[6] * a[0] + b[7] * a[3] + b[8] * a[6],
                b[6] * a[1] + b[7] * a[4] + b[8] * a[7],
                b[6] * a[2] + b[7] * a[5] + b[8] * a[8]));
        return c;
    }

    const mat3 operator * (const float& s, const mat3& a)
    {
        mat3 m;
        m[0] = a[0] * s;
        m[1] = a[1] * s;
        m[2] = a[2] * s;
        m[3] = a[3] * s;
        m[4] = a[4] * s;
        m[5] = a[5] * s;
        m[6] = a[6] * s;
        m[7] = a[7] * s;
        m[8] = a[8] * s;
        return m;
    }

    const mat3 operator * (const mat3& a, const float& s)
    {
        mat3 m;
        m[0] = a[0] * s;
        m[1] = a[1] * s;
        m[2] = a[2] * s;
        m[3] = a[3] * s;
        m[4] = a[4] * s;
        m[5] = a[5] * s;
        m[6] = a[6] * s;
        m[7] = a[7] * s;
        m[8] = a[8] * s;
        return m;
    }

    const mat3 operator / (const mat3& a, const float& s)
    {
        mat3 m;
        m[0] = a[0] / s;
        m[1] = a[1] / s;
        m[2] = a[2] / s;
        m[3] = a[3] / s;
        m[4] = a[4] / s;
        m[5] = a[5] / s;
        m[6] = a[6] / s;
        m[7] = a[7] / s;
        m[8] = a[8] / s;
        return m;
    }

    const mat3 operator + (const mat3& a, const mat3& b)
    {
        mat3 m;
        m[0] = a[0] + b[0];
        m[1] = a[1] + b[1];
        m[2] = a[2] + b[2];
        m[3] = a[3] + b[3];
        m[4] = a[4] + b[4];
        m[5] = a[5] + b[5];
        m[6] = a[6] + b[6];
        m[7] = a[7] + b[7];
        m[8] = a[8] + b[8];
        return m;
    }

    const mat3 operator - (const mat3& a, const mat3& b)
    {
        mat3 m;
        m[0] = a[0] - b[0];
        m[1] = a[1] - b[1];
        m[2] = a[2] - b[2];
        m[3] = a[3] - b[3];
        m[4] = a[4] - b[4];
        m[5] = a[5] - b[5];
        m[6] = a[6] - b[6];
        m[7] = a[7] - b[7];
        m[8] = a[8] - b[8];
        return m;
    }

    const mat3 MultTransposed(const vec3& a, const vec3& b)
    {
        mat3 m;
        m[0] = a[0]*b[0];
        m[3] = a[0]*b[1];
        m[6] = a[0]*b[2];

        m[1] = a[1]*b[0];
        m[4] = a[1]*b[1];
        m[7] = a[1]*b[2];

        m[2] = a[2]*b[0];
        m[5] = a[2]*b[1];
        m[8] = a[2]*b[2];

        return m;
    }

    const vec3 operator * (const mat3& m, const vec3& v)
    {
        vec3 res;
        res[0] = m[0] * v[0] + m[3] * v[1] + m[6] * v[2];
        res[1] = m[1] * v[0] + m[4] * v[1] + m[7] * v[2];
        res[2] = m[2] * v[0] + m[5] * v[1] + m[8] * v[2];

        return res;
    }

    bool operator == (const mat3& l, const mat3& r)
    {
        for (int i = 0; i < 9; ++i)
            if (l[i] != r[i])
                return false;
        return true;;
    }

    bool mat3::IsEqual(const mat3& v, float eps) const
    {
        for (int i = 0; i < 9; ++i)
        {
            float a = fabs(v[i] - m[i]);
            if (a > eps)
                return false;
        }
        return true;
    }
}

