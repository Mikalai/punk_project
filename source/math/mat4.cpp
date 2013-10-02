#include <limits>
#include "../system/buffer.h"
#include "frustum.h"
#include "quat.h"
#include "mat3.h"
#include "mat4.h"

namespace Math
{
    mat4::mat4()
        : m{1,0,0,0
            ,0,1,0,0
            ,0,0,1,0
            ,0,0,0,1}
    {}

    mat4::mat4(const mat4& mm)
    {
        memcpy(m, mm.m, sizeof(mm));
    }

    const mat4 mat4::CreatePerspectiveProjection(float fovy, float width, float height, float znear, float zfar)
    {
        mat4 res;

        float f = 1.0f / tanf(0.5f * fovy);
        float aspect = width / height;
        float* m = &res[0];

        m[0*4 + 0] = f / aspect;
        m[0*4 + 1] = 0.0f;
        m[0*4 + 2] = 0.0f;
        m[0*4 + 3] = 0.0f;

        m[1*4 + 0] = 0.0f;
        m[1*4 + 1] = f;
        m[1*4 + 2] = 0.0f;
        m[1*4 + 3] = 0.0f;

        m[2*4 + 0] = 0.0f;
        m[2*4 + 1] = 0.0f;
        m[2*4 + 2] = (zfar + znear) / (znear - zfar);
        m[2*4 + 3] = -1.0f;

        m[3*4 + 0] = 0.0f;
        m[3*4 + 1] = 0.0f;
        m[3*4 + 2] = (2.0f * zfar * znear) / (znear - zfar);
        m[3*4 + 3] = 0.0f;

        return res;
    }

    const mat4 mat4::CreateTargetCameraMatrix(const vec3& _eye, const vec3& _target, const vec3& _up)
    {
        vec3 F = (_target - _eye);
        vec3 f = F.Normalized();

        vec3 up = _up.Normalized();
        vec3 s = f.Cross(up).Normalized();
        vec3 u = s.Cross(f);

        mat4 m;
        m[0*4 + 0] = s[0];
        m[1*4 + 0] = s[1];
        m[2*4 + 0] = s[2];
        m[3*4 + 0] = 0;

        m[0*4 + 1] = u[0];
        m[1*4 + 1] = u[1];
        m[2*4 + 1] = u[2];
        m[3*4 + 1] = 0;

        m[0*4 + 2] = -f[0];
        m[1*4 + 2] = -f[1];
        m[2*4 + 2] = -f[2];
        m[3*4 + 2] = 0;

        m[0*4 + 3] = 0.0f;
        m[1*4 + 3] = 0.0f;
        m[2*4 + 3] = 0.0f;
        m[3*4 + 3] = 1.0f;/**/
        m = m * CreateTranslate(-_eye.X(), -_eye.Y(), -_eye.Z());
        return m;
    }

    const mat4 mat4::CreateFreeCameraMatrix(const vec3& eye, const vec3& dir, const vec3& up)
    {
        return CreateTargetCameraMatrix(eye, eye + dir, up);
    }

    const mat4 mat4::CreateTranslate(float x, float y, float z)
    {
        mat4 m;
        m[12] = x;
        m[13] = y;
        m[14] = z;
        return m;
    }

    float& mat4::operator [] (int i)
    {
        return m[i];
    }

    const float& mat4::operator [] (int i) const
    {
        return m[i];
    }

    const mat4 mat4::CreateTranslate(const vec3 &v)
    {
        return CreateTranslate(v[0], v[1], v[2]);
    }

    const vec4 mat4::GetRow(int row) const
    {
        return vec4(m[0 * 4 + row],
                m[1 * 4 + row],
                m[2 * 4 + row],
                m[3 * 4 + row]);
    }

    void mat4::SetColumn(int column, const vec4& v)
    {
        for (int i = 0; i < 4; i++)
        {
            m[column * 4 + i] = v[i];
        }
    }

    mat4& mat4::operator *= (const mat4& b)
    {
        mat4 a = *this;

        SetColumn(0, vec4(
                      b[0] * a[0] + b[1] * a[4] + b[2] * a[8] + b[3] * a[12],
                b[0] * a[1] + b[1] * a[5] + b[2] * a[9] + b[3] * a[13],
                b[0] * a[2] + b[1] * a[6] + b[2] * a[10] + b[3] * a[14],
                b[0] * a[3] + b[1] * a[7] + b[2] * a[11] + b[3] * a[15]));
        SetColumn(1, vec4(
                      b[4] * a[0] + b[5] * a[4] + b[6] * a[8] + b[7] * a[12],
                b[4] * a[1] + b[5] * a[5] + b[6] * a[9] + b[7] * a[13],
                b[4] * a[2] + b[5] * a[6] + b[6] * a[10] + b[7] * a[14],
                b[4] * a[3] + b[5] * a[7] + b[6] * a[11] + b[7] * a[15]));
        SetColumn(2, vec4(
                      b[8] * a[0] + b[9] * a[4] + b[10] * a[8] + b[11] * a[12],
                b[8] * a[1] + b[9] * a[5] + b[10] * a[9] + b[11] * a[13],
                b[8] * a[2] + b[9] * a[6] + b[10] * a[10] + b[11] * a[14],
                b[8] * a[3] + b[9] * a[7] + b[10] * a[11] + b[11] * a[15]));
        SetColumn(3, vec4(
                      b[12] * a[0] + b[13] * a[4] + b[14] * a[8] + b[15] * a[12],
                b[12] * a[1] + b[13] * a[5] + b[14] * a[9] + b[15] * a[13],
                b[12] * a[2] + b[13] * a[6] + b[14] * a[10] + b[15] * a[14],
                b[12] * a[3] + b[13] * a[7] + b[14] * a[11] + b[15] * a[15]));

        return *this;
    }

    const mat4 mat4::Inversed() const
    {
#define SWAP_ROWS(a, b) {  float * _tmp = a; (a)=(b); (b)=_tmp; }
#define MAT(m,r,c)     m [r*4+c]

        float	wtmp [4][8];
        float	m0, m1, m2, m3, s;
        float	* r0, * r1, * r2, * r3;

        r0 = wtmp [0];
        r1 = wtmp [1];
        r2 = wtmp [2];
        r3 = wtmp [3];

        r0 [0] = MAT(m,0,0);
        r0 [1] = MAT(m,0,1);
        r0 [2] = MAT(m,0,2);
        r0 [3] = MAT(m,0,3);
        r0 [4] = 1;
        r0 [5] =
                r0 [6] =
                r0 [7] = 0;

        r1 [0] = MAT(m,1,0);
        r1 [1] = MAT(m,1,1);
        r1 [2] = MAT(m,1,2);
        r1 [3] = MAT(m,1,3);
        r1 [5] = 1;
        r1 [4] =
                r1 [6] =
                r1 [7] = 0,

                r2 [0] = MAT(m,2,0);
        r2 [1] = MAT(m,2,1);
        r2 [2] = MAT(m,2,2);
        r2 [3] = MAT(m,2,3);
        r2 [6] = 1;
        r2 [4] =
                r2 [5] =
                r2 [7] = 0;

        r3 [0] = MAT(m,3,0);
        r3 [1] = MAT(m,3,1);
        r3 [2] = MAT(m,3,2);
        r3 [3] = MAT(m,3,3);
        r3 [7] = 1;
        r3 [4] =
                r3 [5] =
                r3 [6] = 0;

        // choose pivot - or die
        if ( fabs (r3 [0] )> fabs ( r2 [0] ) )
            SWAP_ROWS ( r3, r2 );

        if ( fabs ( r2 [0] ) > fabs ( r1 [0] ) )
            SWAP_ROWS ( r2, r1 );

        if ( fabs ( r1 [0] ) > fabs ( r0 [0 ] ) )
            SWAP_ROWS ( r1, r0 );

        if ( r0 [0] == 0 )
            return mat4();

        // eliminate first variable
        m1 = r1[0]/r0[0];
        m2 = r2[0]/r0[0];
        m3 = r3[0]/r0[0];

        s = r0[1];
        r1[1] -= m1 * s;
        r2[1] -= m2 * s;
        r3[1] -= m3 * s;

        s = r0[2];
        r1[2] -= m1 * s;
        r2[2] -= m2 * s;
        r3[2] -= m3 * s;

        s = r0[3];
        r1[3] -= m1 * s;
        r2[3] -= m2 * s;
        r3[3] -= m3 * s;

        s = r0[4];

        if ( s != 0 )
        {
            r1[4] -= m1 * s; r2[4] -= m2 * s; r3[4] -= m3 * s;
        }

        s = r0[5];

        if ( s != 0.0 )
        {
            r1[5] -= m1 * s; r2[5] -= m2 * s; r3[5] -= m3 * s;
        }

        s = r0[6];

        if ( s != 0 )
        {
            r1[6] -= m1 * s; r2[6] -= m2 * s; r3[6] -= m3 * s;
        }

        s = r0[7];

        if ( s != 0 )
        {
            r1[7] -= m1 * s; r2[7] -= m2 * s; r3[7] -= m3 * s;
        }

        // choose pivot - or die
        if ( fabs (r3 [1] ) > fabs ( r2 [1] ) )
            SWAP_ROWS ( r3, r2 );

        if ( fabs ( r2 [1] ) > fabs ( r1 [1] ) )
            SWAP_ROWS ( r2, r1 );

        if ( r1 [1] == 0 )
            return mat4();


        // eliminate second variable
        m2     = r2[1]/r1[1]; m3     = r3[1]/r1[1];
        r2[2] -= m2 * r1[2];  r3[2] -= m3 * r1[2];
        r2[3] -= m2 * r1[3];  r3[3] -= m3 * r1[3];

        s = r1[4];

        if ( 0 != s )
        {
            r2[4] -= m2 * s; r3[4] -= m3 * s;
        }

        s = r1[5];

        if ( 0 != s )
        {
            r2[5] -= m2 * s; r3[5] -= m3 * s;
        }

        s = r1[6];

        if ( 0 != s )
        {
            r2[6] -= m2 * s; r3[6] -= m3 * s;
        }

        s = r1[7];

        if ( 0 != s )
        {
            r2[7] -= m2 * s; r3[7] -= m3 * s;
        }

        // choose pivot - or die
        if ( fabs ( r3 [2] ) > fabs ( r2 [2] ) )
            SWAP_ROWS ( r3, r2 );

        if ( r2 [2] == 0)
            return mat4();

        // eliminate third variable
        m3     = r3[2]/r2[2];
        r3[3] -= m3 * r2[3], r3[4] -= m3 * r2[4],
                r3[5] -= m3 * r2[5], r3[6] -= m3 * r2[6],
                r3[7] -= m3 * r2[7];

        // last check
        if ( r3 [3] == 0 )
            return mat4();


        // now back substitute row 3
        s      = 1.0f/r3[3];
        r3[4] *= s; r3[5] *= s; r3[6] *= s; r3[7] *= s;

        // now back substitute row 2
        m2    = r2[3];
        s     = 1.0f/r2[2];
        r2[4] = s * (r2[4] - r3[4] * m2), r2[5] = s * (r2[5] - r3[5] * m2),
                r2[6] = s * (r2[6] - r3[6] * m2), r2[7] = s * (r2[7] - r3[7] * m2);
        m1     = r1[3];
        r1[4] -= r3[4] * m1, r1[5] -= r3[5] * m1,
                r1[6] -= r3[6] * m1, r1[7] -= r3[7] * m1;

        m0     = r0[3];
        r0[4] -= r3[4] * m0, r0[5] -= r3[5] * m0,
                r0[6] -= r3[6] * m0, r0[7] -= r3[7] * m0;

        // now back substitute row 1
        m1    = r1[2];
        s     = 1.0f/r1[1];
        r1[4] = s * (r1[4] - r2[4] * m1), r1[5] = s * (r1[5] - r2[5] * m1),
                r1[6] = s * (r1[6] - r2[6] * m1), r1[7] = s * (r1[7] - r2[7] * m1);

        m0     = r0[2];
        r0[4] -= r2[4] * m0, r0[5] -= r2[5] * m0,
                r0[6] -= r2[6] * m0, r0[7] -= r2[7] * m0;

        // now back substitute row 0
        m0    = r0[1];
        s     = 1.0f/r0[0];
        r0[4] = s * (r0[4] - r1[4] * m0), r0[5] = s * (r0[5] - r1[5] * m0),
                r0[6] = s * (r0[6] - r1[6] * m0), r0[7] = s * (r0[7] - r1[7] * m0);

        mat4 res;
        float* out = res.m;
        MAT(out,0,0) = r0[4]; MAT(out,0,1) = r0[5];
        MAT(out,0,2) = r0[6]; MAT(out,0,3) = r0[7];
        MAT(out,1,0) = r1[4]; MAT(out,1,1) = r1[5];
        MAT(out,1,2) = r1[6]; MAT(out,1,3) = r1[7];
        MAT(out,2,0) = r2[4]; MAT(out,2,1) = r2[5];
        MAT(out,2,2) = r2[6]; MAT(out,2,3) = r2[7];
        MAT(out,3,0) = r3[4]; MAT(out,3,1) = r3[5];
        MAT(out,3,2) = r3[6]; MAT(out,3,3) = r3[7];

#undef MAT
#undef SWAP_ROWS

        return res;
    }

    //  mult matrix

    const mat4 operator + (const mat4& a, const mat4& b)
    {
        mat4 c;
        for (int i = 0; i < 16; i++)
        {
            c[i] = a[i] + b[i];
        }
        return c;
    }

    //  mult matrix

    const mat4 operator * (const mat4& a, const mat4& b)
    {
        mat4 c;
        c.SetColumn(0, vec4(
                        b[0] * a[0] + b[1] * a[4] + b[2] * a[8] + b[3] * a[12],
                b[0] * a[1] + b[1] * a[5] + b[2] * a[9] + b[3] * a[13],
                b[0] * a[2] + b[1] * a[6] + b[2] * a[10] + b[3] * a[14],
                b[0] * a[3] + b[1] * a[7] + b[2] * a[11] + b[3] * a[15]));
        c.SetColumn(1, vec4(
                        b[4] * a[0] + b[5] * a[4] + b[6] * a[8] + b[7] * a[12],
                b[4] * a[1] + b[5] * a[5] + b[6] * a[9] + b[7] * a[13],
                b[4] * a[2] + b[5] * a[6] + b[6] * a[10] + b[7] * a[14],
                b[4] * a[3] + b[5] * a[7] + b[6] * a[11] + b[7] * a[15]));
        c.SetColumn(2, vec4(
                        b[8] * a[0] + b[9] * a[4] + b[10] * a[8] + b[11] * a[12],
                b[8] * a[1] + b[9] * a[5] + b[10] * a[9] + b[11] * a[13],
                b[8] * a[2] + b[9] * a[6] + b[10] * a[10] + b[11] * a[14],
                b[8] * a[3] + b[9] * a[7] + b[10] * a[11] + b[11] * a[15]));
        c.SetColumn(3, vec4(
                        b[12] * a[0] + b[13] * a[4] + b[14] * a[8] + b[15] * a[12],
                b[12] * a[1] + b[13] * a[5] + b[14] * a[9] + b[15] * a[13],
                b[12] * a[2] + b[13] * a[6] + b[14] * a[10] + b[15] * a[14],
                b[12] * a[3] + b[13] * a[7] + b[14] * a[11] + b[15] * a[15]));
        return c;
    }


    const vec4 operator * (const mat4& m, const vec4& v)
    {
        return vec4(
                    m[0]*v[0] + m[4]*v[1] + m[8]*v[2] + m[12]*v[3],
                m[1]*v[0] + m[5]*v[1] + m[9]*v[2] + m[13]*v[3],
                m[2]*v[0] + m[6]*v[1] + m[10]*v[2] + m[14]*v[3],
                m[3]*v[0] + m[7]*v[1] + m[11]*v[2] + m[15]*v[3]);
    }


    const vec3 operator * (const mat4& m, const vec3& v)
    {
        auto r = m * vec4(v[0], v[1], v[2], float(1));
        return vec3(r[0] / r[3], r[1] / r[3], r[2] / r[3]);
    }


    const mat4 operator * (const mat4& m, const float& v)
    {
        Math::mat4 res;
        for (int i = 0; i < 16; i++)
            res[i] = m[i]*v;
        return res;
    }


    const mat4 operator * (const float& v, const mat4& m)
    {
        Math::mat4 res;
        for (int i = 0; i < 16; i++)
            res[i] = m[i]*v;
        return res;
    }

    const mat4 mat4::CreateOrthographicProjection(float left, float right, float bottom, float top, float _near, float _far)
    {
        mat4 res;

        float tx = - (right + left) / (right - left);
        float ty = - (top + bottom) / (top - bottom);
        float tz = - (_far + _near) / (_far - _near);

        res[0] = 2.0f / (right - left);
        res[1] = 0;
        res[2] = 0;
        res[3] = 0;

        res[4] = 0;
        res[5] = 2.0f / (top - bottom);
        res[6] = 0;
        res[7] = 0;

        res[8] = 0;
        res[9] = 0;
        res[10] = -2.0f / (_far - _near);
        res[11] = 0;

        res[12] = tx;
        res[13] = ty;
        res[14] = tz;
        res[15] = 1;

        return res;
    }

    const Math::mat4 mat4::CreateOrthographicProjection2(float xmin, float xmax, float ymin, float ymax, float zmin, float zmax)
    {
        Math::mat4 m;
        m[0] = 2.0 / (xmax - xmin);
        m[1] = 0;
        m[2] = 0;
        m[3] = 0;

        m[4] = 0;
        m[5] = 2.0 / (ymax - ymin);
        m[6] = 0;
        m[7] = 0;

        m[8] = 0;
        m[9] = 0;
        m[10] = -2.0 / zmax;
        m[11] = 0;

        m[12] = - (xmax + xmin) / (xmax - xmin);
        m[13] = - (ymax + ymin) / (ymax - ymin);
        m[14] = -1;
        m[15] = 1;
        return m;
    }

    const Math::mat4 mat4::CreateTextureBiasMatrix()
    {
        const float bias[16] = {	0.5f, 0.0f, 0.0f, 0.0f,
                                    0.0f, 0.5f, 0.0f, 0.0f,
                                    0.0f, 0.0f, 0.5f, 0.0f,
                                    0.5f, 0.5f, 0.5f, 1.0f	};
        Math::mat4 b;
        for (int i = 0; i != 16; ++i)
        {
            b[i] = bias[i];
        }

        return b;
    }

    const Math::mat4 mat4::CreateCropMatrix(const Math::FrustumCore &frustum, const Math::mat4 &shadow_view, const Math::mat4& shadow_proj, float& min_x, float& max_x, float& min_y, float& max_y)
    {
        max_x = -std::numeric_limits<float>::infinity();
        min_x = std::numeric_limits<float>::infinity();
        max_y = -std::numeric_limits<float>::infinity();
        min_y = std::numeric_limits<float>::infinity();
        auto shadow_proj_view = shadow_proj * shadow_view;

        // find the extends of the frustum slice as projected in light's homogeneous coordinates
        for (int j = 0; j < 8; ++j)
        {
            auto transf = shadow_proj_view * Math::vec4(frustum.point[j], 1.0f);
            float x = transf.X() / transf.W();
            float y = transf.Y() / transf.W();

            if (x > max_x)
                max_x = x;
            if (x < min_x)
                min_x = x;
            if (y > max_y)
                max_y = y;
            if (y < min_y)
                min_y = y;
        }

        float scaleX = 2.0f / (max_x - min_x);
        float scaleY = 2.0f / (max_y - min_y);
        float offsetX = -0.5f * (max_x + min_x) * scaleX;
        float offsetY = -0.5f * (max_y + min_y) * scaleY;

        Math::mat4 crop_matrix;
        crop_matrix[0] = scaleX;
        crop_matrix[1 * 4 + 1] = scaleY;
        crop_matrix[3] = offsetX;
        crop_matrix[1 * 4 + 3] = offsetY;
        crop_matrix = crop_matrix.Transposed();
        return crop_matrix;
    }

    const Math::mat4 mat4::CreateLightProjectionMatrix(const Math::vec2& z_range)
    {
        // set the projection matrix with the new z-bounds
        // note the inversion because the light looks at the neg.
        auto projection = CreateOrthographicProjection2(-1.0, 1.0, -1.0, 1.0, -z_range[1], -z_range[0]);
        return projection;
    }

    const mat4 mat4::CreateFromQuaternion(const quat& q)
    {
        float wx, wy, wz, xx, yy, yz, xy, xz, zz, x2, y2, z2;
        x2 = q.X() + q.X();
        y2 = q.Y() + q.Y();
        z2 = q.Z() + q.Z();
        xx = q.X() * x2;   xy = q.X() * y2;   xz = q.X() * z2;
        yy = q.Y() * y2;   yz = q.Y() * z2;   zz = q.Z() * z2;
        wx = q.W() * x2;   wy = q.W() * y2;   wz = q.W() * z2;
        mat4 mat;
        float* m = &mat[0];
        m[0*4 + 0]=1.0f-(yy+zz); m[1*4 + 0]=xy-wz;        m[2*4 + 0]=xz+wy;
        m[0*4 + 1]=xy+wz;        m[1*4 + 1]=1.0f-(xx+zz); m[2*4 + 1]=yz-wx;
        m[0*4 + 2]=xz-wy;        m[1*4 + 2]=yz+wx;        m[2*4 + 2]=1.0f-(xx+yy);

        return mat;
    }

    const mat4 mat4::CreateRotation(float x, float y, float z, float angle)
    {
        float inversed_length = 1.0f/sqrtf(x*x+y*y+z*z);

        x *= inversed_length;
        y *= inversed_length;
        z *= inversed_length;

        mat4 result;
        float c = std::cos(angle);
        float s = std::sin(angle);
        result.SetColumn(0, vec4(c+(1-c)*x*x, (1-c)*x*y+s*z, (1-c)*x*z-s*y, 0));
        result.SetColumn(1, vec4((1-c)*x*y-s*z, c+(1-c)*y*y, (1-c)*y*z+s*x, 0));
        result.SetColumn(2, vec4((1-c)*x*z+s*y, (1-c)*y*z-s*x, c+(1-c)*z*z, 0));
        result.SetColumn(3, vec4(0,0,0,1));
        return result;
    }

    const mat4 mat4::CreateIdentity()
    {
        return mat4();
    }

    const mat4 mat4::Transposed() const
    {
        mat4 res;
        res.SetColumn(0, vec4(m[0], m[4], m[8], m[12]));
        res.SetColumn(1, vec4(m[1], m[5], m[9], m[13]));
        res.SetColumn(2, vec4(m[2], m[6], m[10], m[14]));
        res.SetColumn(3, vec4(m[3], m[7], m[11], m[15]));

        return res;
    }

    const vec3 mat4::TranslationPart() const
    {
        return vec3(m[12], m[13], m[14]);
    }

    const mat3 mat4::RotationPart() const
    {
        mat3 res;
        res.SetColumn(0, vec3(m[0], m[1], m[2]));
        res.SetColumn(1, vec3(m[4], m[5], m[6]));
        res.SetColumn(2, vec3(m[8], m[9], m[10]));
        return res;
    }

    const mat4 mat4::RotationPart4x4() const
    {
        mat4 res;
        res.SetColumn(0, vec4(m[0], m[1], m[2], 0));
        res.SetColumn(1, vec4(m[4], m[5], m[6], 0));
        res.SetColumn(2, vec4(m[8], m[9], m[10], 0));
        res.SetColumn(3, vec4(0, 0, 0, 1));
        return res;
    }

    const System::string mat4::ToString() const
    {
        return System::string(L"{0} {1} {2} {3}\n {4} {5} {6} {7} \n {8} {9} {10} {11}\n {12} {13} {14} {15}\n").
                arg(m[0]).arg(m[4]).arg(m[8]).arg(m[12]).
                arg(m[1]).arg(m[5]).arg(m[9]).arg(m[13]).
                arg(m[2]).arg(m[6]).arg(m[10]).arg(m[14]).
                arg(m[3]).arg(m[7]).arg(m[11]).arg(m[15]);
    }

    void SaveMatrix4f(System::Buffer* buffer, const mat4& value)
    {
        buffer->WriteBuffer(&value[0], sizeof(value));
    }

    void LoadMatrix4f(System::Buffer* buffer, mat4& value)
    {
        buffer->ReadBuffer(&value[0], sizeof(value));
    }
}
