#ifndef _H_PUNK_VIRTUAL_DATA_LOCATION
#define _H_PUNK_VIRTUAL_DATA_LOCATION

#include "../../config.h"
#include "../../math/vec3.h"
#include "transform.h"

namespace Virtual
{
	class PUNK_ENGINE Location : public TransformNode
	{
	public:

		/**
		*	point in world coordinate system
		*/
		virtual bool IsPointIn(const Math::vec3& point) = 0;

		/**
		*	local coordinate in the location
		*/
		virtual const Math::vec3 LocalCoordinate(const Math::vec3& point) = 0;

		virtual float GetTermperature(const Math::vec3& point) = 0;
		virtual float GetIlluminationLevel(const Math::vec3& point) = 0;
		virtual float GetRadiationLevel(const Math::vec3& point) = 0;
		
	};
}

#endif	//	_H_PUNK_VIRTUAL_DATA_LOCATION