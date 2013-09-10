#include "frustum.h"
#include "math.h"
#include "relations.h"
#include "perspective_decoder.h"
#include "frustum_plane.h"
#include "frustum_points.h"

namespace Math
{
    //    Frustum::Frustum()
    //        : m_fov(0)
    //        , m_zfar(0)
    //        , m_znear(0)
    //        , m_aspect(0)
    //        , m_need_update(true)
    //    {}

    //    Frustum::Frustum(const mat4 &projection_matrix)
    //        : m_projection_matrix(projection_matrix)
    //    {}

    //    void Frustum::SetFovY(float value)
    //    {
    //        m_fov = value;
    //        m_need_update = true;
    //    }

    //    void Frustum::SetAspectRatio(float value)
    //    {
    //        m_aspect = value;
    //        m_need_update = true;
    //    }

    //    void Frustum::SetNearPlane(float value)
    //    {
    //        m_znear = value;
    //        m_need_update = true;
    //    }

    //    void Frustum::SetFarPlane(float value)
    //    {
    //        m_zfar = value;
    //        m_need_update = true;
    //    }

    //    const Plane& Frustum::GetPlane(FrustumPlane value) const
    //    {
    //        return m_planes[static_cast<int>(value)];
    //    }

    //    const mat4 Frustum::GetProjectionMatrix()
    //    {
    //        return mat4::CreatePerspectiveProjection(m_fov, m_aspect, 1, m_znear, m_zfar);
    //    }

    //    const Math::vec3& Frustum::GetPoint(FrustumPoints value) const
    //    {
    //        return m_points[value];
    //    }

    //    const Math::vec3& Frustum::GetTransformedPoint(FrustumPoints value) const
    //    {
    //        return m_transformed_points[value];
    //    }

    //    void Frustum::SetTransformMatrix(const Math::mat4& value)
    //    {
    //        for (int i = 0; i != 8; ++i)
    //        {
    //            m_transformed_points[i] = value * m_points[i];
    //        }
    //    }

    const ClipSpace FrustumToClipSpace(const FrustumCore &f)
    {
        Plane p[6];
        ProjectionMatrixToPlanes(FrustumCreatePerspectiveProjectionMatrix(f), p);
        ClipSpace res;
        //	skip near plane
        for (int i = 0; i != 6; ++i)
        {
            res.Add(p[i]);
        }
        return res;
    }

    /**
      * Creates a clip space from current frustum and point.
      */
    const ClipSpace FrustumBuildClipSpaceFromPoint(const FrustumCore& f, const Math::vec3& p)
    {
        if (ClassifyPoint(p, f) == Relation::INSIDE)
            return FrustumToClipSpace(f);

        ClipSpace result;
        //  true - point in front of the plane, false otherwise
        bool front[6];
        Math::Plane planes[6];
        ProjectionMatrixToPlanes(FrustumCreatePerspectiveProjectionMatrix(f), planes);
        for (int i = 0; i != 6; ++i)
        {
            front[i] = ClassifyPoint(p, planes[i]) == Relation::FRONT;
            //  planes for which point is in fornt of them construct add into the resulting clipspace
            if (front[i])
                result.Add(planes[i]);
        }

        //  for each plane that forms boundary (front[i] == true) create a plane, the goes
        //  through the
        for (int i = 0; i != 6; ++i)
        {
            FrustumPlane plane_a = (FrustumPlane)i;
            if (!front[i])
                continue;
            const Plane& a = planes[i];
            for (int j = 0; j != 6; ++j)
            {
                FrustumPlane plane_b = (FrustumPlane)j;
                if (front[j] || !IsAdjacent(plane_a, plane_b))
                    continue;
                const Plane& b = planes[j];
                Line3D line;
                if (CrossPlanePlane(a, b, line) != Relation::INTERSECT)
                    continue;
                Plane plane;
                plane.Set(line, p);
                result.Add(plane);
            }
        }

        return result;
    }

    void FrustumTransform(FrustumCore &f, const vec3 &center, const vec3 &view_dir, const vec3 &_up)
    {
        vec3 right = view_dir.Cross(_up);

        vec3 fc = center + view_dir*f.fard;
        vec3 nc = center + view_dir*f.neard;

        right = right.Normalized();
        vec3 up = right.Cross(view_dir);
        up = up.Normalized();

        // these heights and widths are half the heights and widths of
        // the near and far plane rectangles
        float near_height = tan(f.fov/2.0f) * f.neard;
        float near_width = near_height * f.ratio;
        float far_height = tan(f.fov/2.0f) * f.fard;
        float far_width = far_height * f.ratio;

        f.point[GetIndex(FrustumPoints::NLB)] = nc - up*near_height - right*near_width;
        f.point[GetIndex(FrustumPoints::NLT)] = nc + up*near_height - right*near_width;
        f.point[GetIndex(FrustumPoints::NRT)] = nc + up*near_height + right*near_width;
        f.point[GetIndex(FrustumPoints::NRB)] = nc - up*near_height + right*near_width;

        f.point[GetIndex(FrustumPoints::FLB)] = fc - up*far_height - right*far_width;
        f.point[GetIndex(FrustumPoints::FLT)] = fc + up*far_height - right*far_width;
        f.point[GetIndex(FrustumPoints::FRT)] = fc + up*far_height + right*far_width;
        f.point[GetIndex(FrustumPoints::FRB)] = fc - up*far_height + right*far_width;
    }

    void ProjectionMatrixToPlanes(const mat4 &p, Math::Plane (&plane)[6])
    {
        plane[GetIndex(FrustumPlane::Near)].Set(p.GetRow(3) + p.GetRow(2)).Normalize();
        plane[GetIndex(FrustumPlane::Far)].Set(p.GetRow(3) - p.GetRow(2)).Normalize();
        plane[GetIndex(FrustumPlane::Left)].Set(p.GetRow(3) + p.GetRow(0)).Normalize();
        plane[GetIndex(FrustumPlane::Right)].Set(p.GetRow(3) - p.GetRow(0)).Normalize();
        plane[GetIndex(FrustumPlane::Bottom)].Set(p.GetRow(3) + p.GetRow(1)).Normalize();
        plane[GetIndex(FrustumPlane::Top)].Set(p.GetRow(3) - p.GetRow(1)).Normalize();
        //planes2[Top].Set(0, -e * tb_coeff, -a * tb_coeff, 0);

        //        CrossThreePlane(m_planes[(int)FrustumPlane::Near], m_planes[(int)FrustumPlane::Left], m_planes[(int)FrustumPlane::Top], m_points[NLT]);
        //        CrossThreePlane(m_planes[(int)FrustumPlane::Near], m_planes[(int)FrustumPlane::Left], m_planes[(int)FrustumPlane::Bottom], m_points[NLB]);
        //        CrossThreePlane(m_planes[(int)FrustumPlane::Near], m_planes[(int)FrustumPlane::Right], m_planes[(int)FrustumPlane::Top], m_points[NRT]);
        //        CrossThreePlane(m_planes[(int)FrustumPlane::Near], m_planes[(int)FrustumPlane::Right], m_planes[(int)FrustumPlane::Bottom], m_points[NRB]);
        //        CrossThreePlane(m_planes[(int)FrustumPlane::Far], m_planes[(int)FrustumPlane::Left], m_planes[(int)FrustumPlane::Top], m_points[FLT]);
        //        CrossThreePlane(m_planes[(int)FrustumPlane::Far], m_planes[(int)FrustumPlane::Left], m_planes[(int)FrustumPlane::Bottom], m_points[FLB]);
        //        CrossThreePlane(m_planes[(int)FrustumPlane::Far], m_planes[(int)FrustumPlane::Right], m_planes[(int)FrustumPlane::Top], m_points[FRT]);
        //        CrossThreePlane(m_planes[(int)FrustumPlane::Far], m_planes[(int)FrustumPlane::Right], m_planes[(int)FrustumPlane::Bottom], m_points[FRB]);

        //        CrossThreePlane(planes2[Near], planes2[Left], planes2[Top], points2[NLT]);
        //        CrossThreePlane(planes2[Near], planes2[Left], planes2[Bottom], points2[NLB]);
        //        CrossThreePlane(planes2[Near], planes2[Right], planes2[Top], points2[NRT]);
        //        CrossThreePlane(planes2[Near], planes2[Right], planes2[Bottom], points2[NRB]);
        //        CrossThreePlane(planes2[Far], planes2[Left], planes2[Top], points2[FLT]);
        //        CrossThreePlane(planes2[Far], planes2[Left], planes2[Bottom], points2[FLB]);
        //        CrossThreePlane(planes2[Far], planes2[Right], planes2[Top], points2[FRT]);
        //        CrossThreePlane(planes2[Far], planes2[Right], planes2[Bottom], points2[FRB]);

        //		//float e = m_znear
        //float a = 1.0f / e;
        //m_planes[PLANE_NEAR].Set(vec3(0,0,-1), m_znear);
        //m_planes[PLANE_FAR].Set(vec3(0,0,1), m_zfar);
        //m_planes[PLANE_LEFT].Set(vec3(e/sqrt(e*e+1), 0, -1/sqrt(e*e+1)), 0);
        //m_planes[PLANE_RIGHT].Set(vec3(-e/sqrt(e*e+1), 0, -1/sqrt(e*e+1)), 0);
        //m_planes[PLANE_BOTTOM].Set(vec3(0, e/sqrt(e*e+a*a), -1/sqrt(e*e+a*a)), 0);
        //m_planes[PLANE_TOP].Set(vec3(0, -e/sqrt(e*e+a*a), -1/sqrt(e*e+a*a)), 0);
    }

    const FrustumCore FrustumCreateFromProjectionMatrix(const mat4 &p)
    {
        FrustumCore f;
        PerspectiveDecoder d(p);
        f.fard = d.GetFarZ();
        f.fov = d.GetFovY();
        f.neard = d.GetNearZ();
        f.ratio = d.GetWidthToHeightAspectRatio();
        return f;
    }

    const Math::mat4 FrustumCreatePerspectiveProjectionMatrix(const FrustumCore& f)
    {
        return Math::mat4::CreatePerspectiveProjection(f.fov, f.ratio, 1, f.neard, f.fard);
    }

    const Math::vec2 FrustumFindZRange(const FrustumCore& f, const Math::mat4& view)
    {
        // find the z-range of the current frustum as seen from the light
        // in order to increase precision
        Math::vec4 transf = view * Math::vec4(f.point[0], 1.0f);
        transf.Normalize();

        float min_z = transf.Z();
        float max_z = transf.Z();

        for (int j = 1; j < 8; ++j)
        {
            transf = view * Math::vec4(f.point[j], 1.0f);
            transf.Normalize();
            if (transf.Z() > max_z)
                max_z = transf.Z();
            if (transf.Z() < min_z)
                min_z = transf.Z();
        }
        return vec2(min_z, max_z);
    }
}

