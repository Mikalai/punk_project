#include <ostream>
#include <istream>

#include "../system/logger.h"
#include "bounding_box.h"
#include "mat3.h"
#include "helper.h"

namespace Math
{
    void BoundingBox::Save(System::Buffer *buffer) const
    {
        m_center_of_mass.Save(buffer);
        m_center.Save(buffer);
        m_r.Save(buffer);
        m_s.Save(buffer);
        m_t.Save(buffer);
        for (int i = 0; i < 6; ++i)
            m_plane[i].Save(buffer);
    }

    void BoundingBox::Load(System::Buffer *buffer)
    {
        m_center_of_mass.Load(buffer);
        m_center.Load(buffer);
        m_r.Load(buffer);
        m_s.Load(buffer);
        m_t.Load(buffer);
        for (int i = 0; i < 6; ++i)
            m_plane[i].Load(buffer);
    }

    bool BoundingBox::Create(const std::vector<vec3>& vertex)
    {
        //	check input data
        if (vertex.empty())
            return (out_error() << "Bad arguments" << std::endl, false);

        //	find average of the vertices
        m_center_of_mass = CalculateAverage(vertex);

        if (!CalculateNativeAxis(vertex, m_r, m_s, m_t))
            return (out_error() << "Can't create bounding box" << std::endl, false);

        //	find plane distances
        float d[6];

        //	init distances with appropriate values
        const vec3 v = vertex.front();
        d[0] = v.Dot(m_r);
        d[1] = v.Dot(m_r);

        d[2] = v.Dot(m_s);
        d[3] = v.Dot(m_s);

        d[4] = v.Dot(m_t);
        d[5] = v.Dot(m_t);

        for (auto v : vertex)
        {
            float r = m_r.Dot(v);
            if (d[0] > r)
                d[0] = r;
            if (d[1] < r)
                d[1] = r;

            float s = m_s.Dot(v);
            if (d[2] > s)
                d[2] = s;
            if (d[3] < s)
                d[3] = s;

            float t = m_t.Dot(v);
            if (d[4] > t)
                d[4] = t;
            if (d[5] < t)
                d[5] = t;
        }

        //	find natural planes
        m_plane[0].Set(m_r, -d[0]);
        m_plane[1].Set(-m_r, d[1]);
        m_plane[2].Set(m_s, -d[2]);
        m_plane[3].Set(-m_s, d[3]);
        m_plane[4].Set(m_t, -d[4]);
        m_plane[5].Set(-m_t, d[5]);

        //	find bbox center
        {
            float a = (d[0] + d[1]) / 2.0f;
            float b = (d[2] + d[3]) / 2.0f;
            float c = (d[4] + d[5]) / 2.0f;

            m_center = a*m_r + b*m_s + c*m_t;

            m_r *= (d[1] - d[0]);
            m_s *= (d[3] - d[2]);
            m_t *= (d[5] - d[4]);

            m_min_corner = m_center - m_r * 0.5f - m_s * 0.5f - m_t * 0.5f;
        }

        return true;
    }

    const BoundingSphere BoundingBox::ToBoundingSphere()
    {
        std::vector<vec3> p {m_min_corner, m_min_corner + m_r + m_s + m_t, m_min_corner + m_r, m_min_corner + m_s};
        BoundingSphere s;
        s.Create(p);
        return s;
    }
}
