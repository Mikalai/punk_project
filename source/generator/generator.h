#ifndef _H_PUNK_GENERATOR
#define _H_PUNK_GENERATOR

#include "..\common\geometry.h"

namespace Generator
{
	class Creator
	{
	public:
		static Common::StaticGeometry* GenerateBox(float width, float height, float depth);
		static Common::StaticGeometry* GeneratPlane(float width, float height, int width_slice, int height_slice);
	};
}

#endif