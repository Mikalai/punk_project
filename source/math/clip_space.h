#ifndef _H_PUNK_MATH_CLIP_SPACE
#define _H_PUNK_MATH_CLIP_SPACE

#include <vector>
#include "../config.h"
#include "plane.h"

namespace Math
{
	class PUNK_ENGINE ClipSpace
	{
	public:
		typedef std::vector<Plane> PlanesCollection;
		typedef PlanesCollection::iterator iterator;
		typedef PlanesCollection::const_iterator const_iterator;
	public:

		void Add(const Plane& plane);

		iterator begin() { return m_planes.begin(); }
		const_iterator begin() const { return m_planes.begin(); }
		iterator end() { return m_planes.end(); }
		const_iterator end() const { return m_planes.end(); }

	private:
		PlanesCollection m_planes;
	};
}

#endif