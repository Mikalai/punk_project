#include <ostream>
#include <istream>
#include "sphere.h"

namespace Math
{
	bool Sphere::Save(std::ostream& stream) const
	{
		m_center.Save(stream);
		stream.write((char*)&m_radius, sizeof(m_radius));
		return true;
	}

	bool Sphere::Load(std::istream& stream)
	{
		m_center.Load(stream);
		stream.read((char*)&m_radius, sizeof(m_radius));
		return true;
	}
}
