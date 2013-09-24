#include <ostream>
#include <istream>
#include "../system/buffer.h"
#include "sphere.h"

namespace Math
{
    const Sphere operator * (const mat4& m, const Sphere& s)
    {
        Sphere res;
        res.m_center = m * s.GetCenter();
        //	consider that transform do not effect the radius
        res.m_radius = s.GetRadius();
        return res;
    }

    const Sphere operator + (const Sphere& a, const Sphere& b)
    {
        float d = (a.GetCenter() - b.GetCenter()).Length();
        if (d + a.GetRadius() <= b.GetRadius())
            return b;
        if (d + b.GetRadius() <= a.GetRadius())
            return a;

        Sphere res;
        float r = 0.5f * (d + a.GetRadius() + b.GetRadius());
        res.SetRadius(r);
        res.SetCenter(a.GetCenter() + (r - a.GetRadius()) / d * (b.GetCenter() - a.GetCenter()));
        return res;
    }

    void SaveSphere(System::Buffer* buffer, const Sphere& value)
    {
        SaveVector3f(buffer, value.m_center);
        buffer->WriteReal32(value.m_radius);
    }

    void LoadSphere(System::Buffer* buffer, Sphere& value)
    {
        LoadVector3f(buffer, value.m_center);
        value.m_radius = buffer->ReadReal32();
    }
}
