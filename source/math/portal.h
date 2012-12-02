#ifndef _H_PUNK_MATH_PORTAL
#define _H_PUNK_MATH_PORTAL

#include <vector>
#include "../config.h"

#include "vec3.h"

namespace Math
{
	class PUNK_ENGINE Portal
	{
	public:
		typedef std::vector<vec3> PointsCollection;
		typedef PointsCollection::iterator iterator;
		typedef PointsCollection::const_iterator const_iterator;

	public:
		bool SetPoints(const PointsCollection& points);

		bool Save(std::ostream& stream) const;
		bool Load(std::istream& stream);

		iterator begin() { return m_points.begin(); }
		const_iterator begin() const { return m_points.begin(); }
		iterator end() { return m_points.end(); }
		const_iterator end() const { return m_points.end(); }
		unsigned size() const { return m_points.size(); }

		const vec3& operator [] (int index) const { return m_points[index]; }
		vec3& operator [] (int index) { return m_points[index]; }

	private:
		PointsCollection m_points;
		vec3 m_normal;
	};
}

#endif	//	_H_PUNK_MATH_PORTAL