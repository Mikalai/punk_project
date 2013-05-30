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
        size_t size() const { return m_planes.size(); }
        bool empty() const { return m_planes.empty(); }
        const Plane& operator[] (size_t index) const { return m_planes[index]; }
        Plane& operator[] (size_t index) { return m_planes[index]; }

		const PlanesCollection& GetPlanes() const;

	private:
		PlanesCollection m_planes;
	};
}

#endif
