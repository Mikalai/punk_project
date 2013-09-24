#include <ostream>
#include <math.h>
#include "../system/buffer.h"
#include "math_error.h"
#include "vec3.h"
#include "mat3.h"
#include "mat4.h"
#include "quat.h"

namespace Math
{
    void SaveQuaternion(System::Buffer* buffer, const quat& value)
    {
        for (int i = 0; i != 4; ++i)
        {
            buffer->WriteReal32(value[i]);
        }
    }

    void LoadQuaternion(System::Buffer* buffer, quat& value)
    {        
        for (int i = 0; i != 3; ++i)
        {
            value[i] = buffer->ReadReal32();
        }
    }

    quat::quat()
        : m_v{0, 0, 0, 0}
    {}

    quat::quat(float w, float x, float y, float z)
        : m_v{w, x, y, z}
    {}

    quat::quat(const quat &q)
    {
        memcpy(m_v, q.m_v, sizeof(m_v));
    }

    quat::quat(float w, const vec3 &v)
    {
        m_v[0] = w;
        m_v[1] = v[0];
        m_v[2] = v[1];
        m_v[3] = v[2];
    }

    float& quat::Scalar()
    {
        return m_v[0];
    }

    vec3& quat::Vector()
    {
        vec3* p = (vec3*)&m_v[1];   //  TODO: Will this work???
        return *p;
    }

    const float& quat::Scalar() const
    {
        return m_v[0];
    }

    const vec3& quat::Vector() const
    {
        vec3* p = (vec3*)&m_v[1];   //  TODO: Will this work???
        return *p;
    }

    const vec4 quat::ToAngleAxis() const
    {
        vec4 res;
        //Normalize();
        float angle = 2 * acosf(m_v[0]);
        double s = sqrt(1-m_v[0]*m_v[0]); // assuming quaternion normalised then w is less than 1, so term always positive.
        if (s < 0.001)
        { // test to avoid divide by zero, s is always positive due to sqrt
            // if s close to zero then direction of axis not important
            res[0] = m_v[1]; // if it is important that axis is normalised then replace with x=1; y=z=0;
            res[1] = m_v[2];
            res[2] = m_v[3];
        }
        else
        {
            res[0] = m_v[1] / (float)s; // normalise axis
            res[1] = m_v[2] / (float)s;
            res[2] = m_v[3] / (float)s;
        }
        res[3] = angle;
        return res;
    }

    float& quat::operator [] (int i)
    {
        return m_v[i];
    }

    const float& quat::operator[] (int i) const
    {
        return m_v[i];
    }

    void quat::Set(float w, float x, float y, float z)
    {
        m_v[0] = w;
        m_v[1] = x;
        m_v[2] = y;
        m_v[3] = z;
    }

    float& quat::W()
    {
        return m_v[0];
    }

    const float& quat::W() const
    {
        return m_v[0];
    }

    float& quat::X()
    {
        return m_v[1];
    }

    const float& quat::X() const
    {
        return m_v[1];
    }

    float& quat::Y()
    {
        return m_v[2];
    }

    const float& quat::Y() const
    {
        return m_v[2];
    }

    float& quat::Z()
    {
        return m_v[3];
    }

    const float& quat::Z() const
    {
        return m_v[3];
    }

    const quat quat::Conjugated() const
    {
        return quat(m_v[0], -m_v[1], -m_v[2], -m_v[3]);
    }

    quat& quat::Conjugate()
    {
        m_v[1] = -m_v[1];
        m_v[2] = -m_v[2];
        m_v[3] = -m_v[3];
        return *this;
    }

    quat& quat::Normalize()
    {
        float l = 1.0f / Length();
        m_v[0] *= l;
        m_v[1] *= l;
        m_v[2] *= l;
        m_v[3] *= l;

        return *this;
    }

    const quat quat::Normalized() const
    {
        float l = Length();
        return quat(m_v[0] / l, m_v[1] / l, m_v[2] / l, m_v[3] / l);
    }

    float quat::Length() const
    {
        return std::sqrt(m_v[0]*m_v[0] + m_v[1]*m_v[1] + m_v[2]*m_v[2] + m_v[3]*m_v[3]);
    }

    float quat::SquareLength() const
    {
        return m_v[0]*m_v[0] + m_v[1]*m_v[1] + m_v[2]*m_v[2] + m_v[3]*m_v[3];
    }

    const System::string quat::ToString() const
    {
        return System::string("[{0}, ({1}; {2}, {3}})]").arg(m_v[0]).arg(m_v[1]).arg(m_v[2]).arg(m_v[3]);
    }

    const vec3 quat::Rotate(const vec3& v) const
    {
        quat p(0, v.X(), v.Y(), v.Z());
        quat inv_q = Inversed();
        const quat& q = *this;

        p = q * p * inv_q;

        return vec3(p.X(), p.Y(), p.Z());
    }

    const quat quat::Inversed() const
    {
        float l = SquareLength();
        quat q = Conjugated();
        return q / l;
    }

    const quat quat::operator - () const
    {
        return quat(-m_v[0], -Vector());
    }

    float quat::Dot(const quat& q) const
    {
        return m_v[0]*q[0] + m_v[1]*q[1] + m_v[2]*q[2] + m_v[3]*q[3];
    }

    const mat4 quat::ToMatrix4x4() const
    {
        mat4 m;
        float xx = X()*X();
        float xy = X()*Y();
        float xz = X()*Z();
        float wx = X()*W();

        float yy = Y()*Y();
        float yz = Y()*Z();
        float wy = Y()*W();

        float zz = Z()*Z();
        float wz = Z()*W();

        m[0] = 1 - 2*yy - 2*zz;
        m[1] = 2*xy + 2*wz;
        m[2] = 2*xz - 2*wy;

        m[4] = 2*xy - 2*wz;
        m[5] = 1 - 2*xx - 2*zz;
        m[6] = 2*yz + 2*wx;

        m[8] = 2*xz + 2*wy;
        m[9] = 2*yz - 2*wx;
        m[10] = 1 - 2*xx - 2*yy;

        m[3] = m[7] = m[11] = m[12] = m[13] = m[14] = float(0.0);
        m[15] = float(1.0);

        return m;
    }

    const mat3 quat::ToMatrix3x3() const
    {
        mat3 m;
        float xx = X()*X();
        float xy = X()*Y();
        float xz = X()*Z();
        float wx = X()*W();

        float yy = Y()*Y();
        float yz = Y()*Z();
        float wy = Y()*W();

        float zz = Z()*Z();
        float wz = Z()*W();

        m[0] = 1 - 2*yy - 2*zz;
        m[1] = 2*xy + 2*wz;
        m[2] = 2*xz - 2*wy;

        m[3] = 2*xy - 2*wz;
        m[4] = 1 - 2*xx - 2*zz;
        m[5] = 2*yz + 2*wx;

        m[6] = 2*xz + 2*wy;
        m[7] = 2*yz - 2*wx;
        m[8] = 1 - 2*xx - 2*yy;

        return m;
    }

    quat& quat::operator += (const quat& v)
    {
        m_v[0] += v[0];
        m_v[1] += v[1];
        m_v[2] += v[2];
        m_v[3] += v[3];
        return *this;
    }

    quat& quat::operator -= (const quat& v)
    {
        m_v[0] -= v[0];
        m_v[1] -= v[1];
        m_v[2] -= v[2];
        m_v[3] -= v[3];
        return *this;
    }

    quat& quat::operator *= (const quat& v)
    {
        float w1 = W(); float w2 = v.W();
        float x1 = X(); float x2 = v.X();
        float y1 = Y(); float y2 = v.Y();
        float z1 = Z(); float z2 = v.Z();
        float w = w1*w2 - x1*x2 - y1*y2 - z1*z2;
        float x = w1*x2 + x1*w2 + y1*z2 - z1*y2;
        float y = w1*y2 - x1*z2 + y1*w2 + z1*x2;
        float z = w1*z2 + x1*y2 - y1*x2 + z1*w2;

        m_v[0] = w;
        m_v[1] = x;
        m_v[2] = y;
        m_v[3] = z;

        return *this;
    }

    quat& quat::operator *= (float v)
    {
        m_v[0] *= v;
        m_v[1] *= v;
        m_v[2] *= v;
        m_v[3] *= v;
        return *this;
    }

    quat& quat::operator /= (float v)
    {
        m_v[0] /= v;
        m_v[1] /= v;
        m_v[2] /= v;
        m_v[3] /= v;
        return *this;
    }

    const quat operator + (const quat& q1, const quat& q2)
    {
        quat q(q1);
        q += q2;
        return q;
    }

    const quat operator - (const quat& q1, const quat& q2)
    {
        quat q(q1);
        q -= q2;
        return q;
    }

    const quat operator * (const quat& q, const float& s)
    {
        quat res(q);
        res *= s;
        return res;
    }

    const quat operator * (const float& s, const quat& q)
    {
        quat r(q);
        r *= s;
        return r;
    }

    const quat operator / (const quat& q, const float& s)
    {
        quat r(q);
        r /= s;
        return r;
    }

    const quat operator * (const quat& q1, const quat& q2)
    {
        quat r(q1);
        r *= q2;
        return r;
    }

    bool operator == (const quat& l, const quat& r)
    {
        return l[0] == r[0] && l[1] == r[1] && l[2] == r[2] && l[3] == r[3];
    }

    bool operator != (const quat& l, const quat& r)
    {
        return !(l == r);
    }

    const quat quat::CreateFromAngleAxis(float angle, const vec3& axis)
    {
        quat q;
        q.m_v[0] = std::cos(angle / float(2.0));
        q.m_v[1] = axis[0] * std::sin(angle / float(2.0));
        q.m_v[2] = axis[1] * std::sin(angle / float(2.0));
        q.m_v[3] = axis[2] * std::sin(angle / float(2.0));

        q.Normalize();

        return q;
    }

    const quat quat::CreateFromMatrix4x4(const mat4& m)
    {
        float t = m[0] + m[5] + m[10] + float(1);
        if (t > 0)
        {
            float s = float(0.5) / (float)sqrtf((float)t);
            float w = float(0.25) / s;
            float x = (m[6] - m[9]) * s;
            float y = (m[8] - m[2]) * s;
            float z = (m[1] - m[4]) * s;
            return quat(w, x, y, z);
        }
        int Max = 0;
        for (int i = 0; i < 3; i++)
        {
            if (m[Max*4 + Max] < m[i*4 + i])
                Max = i;
        }

        switch(Max)
        {
        case 0:
        {
            float s = sqrt(float(1.0) + m[0] - m[5] - m[10]) * float(2.0);
            float x = float(0.5) / s;
            float y = (m[1] + m[4]) / s;
            float z = (m[2] + m[8]) / s;
            float w = (m[6] + m[9]) / s;
            return quat(w, x, y, z);
        }
        case 1:
        {
            float s = sqrt(float(1.0) + m[5] - m[0] - m[10]) * float(2.0);
            float x = (m[1] + m[4]) / s;
            float y = float(0.5) / s;
            float z = (m[6] + m[9]) / s;
            float w = (m[2] + m[8]) / s;
            return quat(w, x, y, z);
        }
        case 2:
        {
            float s = sqrt(float(1.0) + m[10] - m[0] - m[5]) * float(2.0);
            float x = (m[2] + m[8]) / s;
            float y = (m[6] + m[9]) / s;
            float z = float(0.5) / s;
            float w = (m[1] + m[4]) / s;
            return quat(w, x, y, z);
        }
        default:
            throw System::PunkException(L"Can't convert matrix to quaternion");
        }
    }

    const quat quat::CreateFromMatrix3x3(const mat3& m)
    {
        float t = m[0] + m[4] + m[8] + float(1);
        if (t > 0)
        {
            float s = float(0.5) / (float)sqrtf((float)t);
            float w = float(0.25) / s;
            float x = (m[5] - m[7]) * s;
            float y = (m[6] - m[2]) * s;
            float z = (m[1] - m[3]) * s;
            return quat(w, x, y, z);
        }
        int Max = 0;
        for (int i = 0; i < 3; i++)
        {
            if (m[Max*3 + Max] < m[i*3 + i])
                Max = i;
        }

        switch(Max)
        {
        case 0:
        {
            float s = sqrt(float(1.0) + m[0] - m[4] - m[8]) * float(2.0);
            float x = float(0.5) / s;
            float y = (m[1] + m[3]) / s;
            float z = (m[2] + m[6]) / s;
            float w = (m[5] + m[7]) / s;
            return quat(w, x, y, z);
        }
        case 1:
        {
            float s = sqrt(float(1.0) + m[4] - m[0] - m[8]) * float(2.0);
            float x = (m[1] + m[3]) / s;
            float y = float(0.5) / s;
            float z = (m[5] + m[7]) / s;
            float w = (m[2] + m[6]) / s;
            return quat(w, x, y, z);
        }
        case 2:
        {
            float s = sqrt(float(1.0) + m[8] - m[0] - m[4]) * float(2.0);
            float x = (m[2] + m[6]) / s;
            float y = (m[5] + m[7]) / s;
            float z = float(0.5) / s;
            float w = (m[1] + m[3]) / s;
            return quat(w, x, y, z);
        }
        default:
            throw System::PunkException(L"Can't convert matrix to quaternion");
        }
    }

    std::wostream& operator << (std::wostream& stream, const quat& q)
    {
        stream << L'[' << q[0] << L'(' << q[1] << L',' << L' ' << q[2] << L',' << L' ' << q[1] << L')' << L']';
        return stream;
    }
}

