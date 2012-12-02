#include "clip_space.h"

namespace Math
{
	void ClipSpace::Add(const Plane& plane)
	{
		m_planes.push_back(plane);
	}

}
