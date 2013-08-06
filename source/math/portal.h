#ifndef _H_PUNK_MATH_PORTAL
#define _H_PUNK_MATH_PORTAL

#include <vector>
#include "../config.h"

#include "vec3.h"
#include "mat4.h"
#include "plane.h"

namespace Math
{
	class PUNK_ENGINE_API Portal
	{
	public:
		typedef std::vector<vec3> PointsCollection;
		typedef PointsCollection::iterator iterator;
		typedef PointsCollection::const_iterator const_iterator;

	public:
		bool SetPoints(const PointsCollection& points);

        void Save(System::Buffer* buffer) const;
        void Load(System::Buffer* buffer);

		iterator begin() { return m_points.begin(); }
		const_iterator begin() const { return m_points.begin(); }
		iterator end() { return m_points.end(); }
		const_iterator end() const { return m_points.end(); }
		unsigned size() const { return m_points.size(); }

		const vec3& operator [] (int index) const { return m_points[index]; }
		vec3& operator [] (int index) { return m_points[index]; }

		const vec3& GetNormal() const { return m_plane.GetNormal(); }
		float GetDistance() const { return m_plane.GetDistance(); }

	private:
		PointsCollection m_points;
		Plane m_plane;

		friend PUNK_ENGINE_API const Portal operator * (const mat4& m, const Portal& p);
	};

	//	transforms portal to other space
	PUNK_ENGINE_API const Portal operator * (const mat4& m, const Portal& p);
}

#endif	//	_H_PUNK_MATH_PORTAL
