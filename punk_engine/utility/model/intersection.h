#ifndef _H_INTERSECTION
#define _H_INTERSECTION

#include "../../system/string.h"
#include <vector>
#include <map>
#include "../../math/vec3.h"

namespace Utility
{
	class Intersection
	{
	public:
		typedef std::vector<Math::vec3> IntersectionPoints;
		typedef IntersectionPoints::iterator iterator;
		typedef IntersectionPoints::const_iterator const_iterator;

		System::string m_name;
		IntersectionPoints m_points;
	public:
		
		void SetName(const System::string& name)
		{
			m_name = name;
		}

		const System::string& GetName() const
		{
			return m_name;
		}

		void push_back(const Math::vec3& v)
		{
			m_points.push_back(v);
		}

		unsigned size()
		{
			return m_points.size();
		}

		iterator begin()
		{
			return m_points.begin();
		}

		const_iterator begin() const
		{
			m_points.begin();
		}

		iterator end()
		{
			m_points.end();
		}

		const_iterator end() const
		{
			m_points.end();
		}

		Math::vec3& operator [] (int index)
		{
			return m_points[index];
		}

		const Math::vec3& operator [] (int index) const
		{
			return m_points[index];
		}
	};

	typedef std::map<System::string, Intersection> IntersectionCollection;
}

#endif