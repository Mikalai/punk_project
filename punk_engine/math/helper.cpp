#include "helper.h"

namespace Math
{
    mat4 Translate(vec3 pos)
    {
        mat4 res;
        res[12] = pos[0];
        res[13] = pos[1];
        res[14] = pos[2];
        return res;
    }

    mat4 ProjectionMatrix(float fovx, float aspect, float znear, float zfar)
    {
        float e = 1.0f / tanf(fovx / 2.0f);
        float aspectInv = 1.0f / aspect;
        float fovy = 2.0f * atanf(aspectInv / e);
        float xScale = 1.0f / tanf(0.5f * fovy);
        float yScale = xScale / aspectInv;
        mat4 res;
        float* m = &res[0];
        m[0*4 + 0] = xScale;
        m[0*4 + 1] = 0.0f;
        m[0*4 + 2] = 0.0f;
        m[0*4 + 3] = 0.0f;

        m[1*4 + 0] = 0.0f;
        m[1*4 + 1] = yScale;
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

    mat4 TargetCamera(vec3 eye, vec3 target, vec3 up)
    {
        // Builds a look-at style view matrix.
        // This is essentially the same matrix used by gluLookAt().
        vec3 zAxis = eye - target;
        zAxis.Normalize();

        vec3 xAxis = up.Cross(zAxis);
        xAxis.Normalize();

        vec3 yAxis = zAxis.Cross(xAxis);
        yAxis.Normalize();

        mat4 res;
        float* m = &res[0];

        m[0*4 + 0] = xAxis[0];
        m[1*4 + 0] = xAxis[1];
        m[2*4 + 0] = xAxis[2];
        m[3*4 + 0] = -xAxis.Dot(eye);

        m[0*4 + 1] = yAxis[0];
        m[1*4 + 1] = yAxis[1];
        m[2*4 + 1] = yAxis[2];
        m[3*4 + 1] = -yAxis.Dot(eye);

        m[0*4 + 2] = zAxis[0];
        m[1*4 + 2] = zAxis[1];
        m[2*4 + 2] = zAxis[2];
        m[3*4 + 2] = -zAxis.Dot(eye);

        m[0*4 + 3] = 0.0f;
        m[1*4 + 3] = 0.0f;
        m[2*4 + 3] = 0.0f;
        m[3*4 + 3] = 1.0f;
        return res;
    }

    mat4 FreeCamera(vec3 eye, vec3 dir, vec3 up)
    {
        // Builds a look-at style view matrix.
        // This is essentially the same matrix used by gluLookAt().
        vec3 target = eye + dir;
        vec3 zAxis = eye - target;
        zAxis.Normalize();

        vec3 xAxis = up.Cross(zAxis);
        xAxis.Normalize();

        vec3 yAxis = zAxis.Cross(xAxis);
        yAxis.Normalize();

        mat4 res;
        float* m = &res[0];

        m[0*4 + 0] = xAxis[0];
        m[1*4 + 0] = xAxis[1];
        m[2*4 + 0] = xAxis[2];
        m[3*4 + 0] = -xAxis.Dot(eye);

        m[0*4 + 1] = yAxis[0];
        m[1*4 + 1] = yAxis[1];
        m[2*4 + 1] = yAxis[2];
        m[3*4 + 1] = -yAxis.Dot(eye);

        m[0*4 + 2] = zAxis[0];
        m[1*4 + 2] = zAxis[1];
        m[2*4 + 2] = zAxis[2];
        m[3*4 + 2] = -zAxis.Dot(eye);

        m[0*4 + 3] = 0.0f;
        m[1*4 + 3] = 0.0f;
        m[2*4 + 3] = 0.0f;
        m[3*4 + 3] = 1.0f;
        return res;
    }

    mat3 NormalMatrixFromWorldView(const mat4& worldView)
    {
        mat3 res;
        float* m = res;
        m[0*3 + 0] = worldView[0*4 + 0];
        m[0*3 + 1] = worldView[0*4 + 1];
        m[0*3 + 2] = worldView[0*4 + 2];

        m[1*3 + 0] = worldView[1*4 + 0];
        m[1*3 + 1] = worldView[1*4 + 1];
        m[1*3 + 2] = worldView[1*4 + 2];

        m[2*3 + 0] = worldView[2*4 + 0];
        m[2*3 + 1] = worldView[2*4 + 1];
        m[2*3 + 2] = worldView[2*4 + 2];

        res = res.Inversed().Transpose();

        return res;
    }
    mat4 RotationMatrixFromQuaternion(const quat& q)
    {
        float wx, wy, wz, xx, yy, yz, xy, xz, zz, x2, y2, z2;
        x2 = q[0] + q[0];
        y2 = q[1] + q[1];
        z2 = q[2] + q[2];
        xx = q[0] * x2;   xy = q[0] * y2;   xz = q[0] * z2;
        yy = q[1] * y2;   yz = q[1] * z2;   zz = q[2] * z2;
        wx = q[3] * x2;   wy = q[3] * y2;   wz = q[3] * z2;
        mat4 mat;
        float* m = &mat[0];
        m[0*4 + 0]=1.0f-(yy+zz); m[0*4 + 1]=xy-wz;        m[0*4 + 2]=xz+wy;
        m[1*4 + 0]=xy+wz;        m[1*4 + 1]=1.0f-(xx+zz); m[1*4 + 2]=yz-wx;
        m[2*4 + 0]=xz-wy;        m[2*4 + 1]=yz+wx;        m[2*4 + 2]=1.0f-(xx+yy);

        m[0*4 + 3] = m[1*4 + 3] = m[2*4 + 3] = 0;
        m[3*4 + 0] = m[3*4 + 1] = m[3*4 + 2] = 0;
        m[3*4 + 3] = 1;
        return mat;
    }
}
