#include "clip_space.h"

namespace Math
{
	void ClipSpace::Add(const Plane& plane)
	{
		m_planes.push_back(plane);
	}

	const ClipSpace::PlanesCollection& ClipSpace::GetPlanes() const
	{
		return m_planes;
	}
}
