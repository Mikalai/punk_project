/*
File: AxisAlignedBox.h
Author: Abramaŭ Mikałaj
Description: A bounding box
*/

#ifndef _H_PUNK_MATH_AABB
#define _H_PUNK_MATH_AABB

#include <iosfwd>
#include "../config.h"
#include "mat4.h"
#include "vec3.h"

namespace Math
{
	class Line3D;

	class PUNK_ENGINE_API AxisAlignedBox
	{
	public:
		
		void Create(const float* data, unsigned offset, int count);

		const vec3& MinPoint() const;
		const vec3& MaxPoint() const;
		vec3& MinPoint();
		vec3& MaxPoint();		

        void Set(const vec3& min_point, const vec3& max_point);

    private:
        vec3 m_min;
        vec3 m_max;

        friend void SaveBoundingBox(System::Buffer* buffer, const AxisAlignedBox& value);
        friend void LoadBoundingBox(System::Buffer* buffer, AxisAlignedBox& value);
	};

	PUNK_ENGINE_API AxisAlignedBox Merge(const AxisAlignedBox* b1, const AxisAlignedBox* b2);


    PUNK_ENGINE_API void SaveBoundingBox(System::Buffer* buffer, const AxisAlignedBox& value);
    PUNK_ENGINE_API void LoadBoundingBox(System::Buffer* buffer, AxisAlignedBox& value);


}

#endif	//	_H_PUNK_MATH_AABB
