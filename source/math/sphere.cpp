#include <ostream>
#include <istream>
#include "sphere.h"

namespace Math
{
    void Sphere::Save(System::Buffer *buffer) const
	{
        m_center.Save(buffer);
        buffer->WriteReal32(m_radius);
	}

    void Sphere::Load(System::Buffer *buffer)
	{
        m_center.Load(buffer);
        m_radius = buffer->ReadReal32();
	}
}
