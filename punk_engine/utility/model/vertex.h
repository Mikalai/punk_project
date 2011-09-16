#ifndef _H_PUNK_UTILITY_VERTEX
#define _H_PUNK_UTILITY_VERTEX

#include "../config.h"

namespace Utility
{
	enum VertexComponent {COMPONENT_POSITION = 1, COMPONENT_NORMAL = 2, COMPONENT_TEXTURE = 4, COMPONENT_BITANGENT = 8, COMPONENT_TANGENT = 16, COMPONENT_BONE_ID = 32, COMPONENT_BONE_WEIGHT = 64};

	namespace internal_data
	{

	}

	struct LIB_UTILITY Vertex
	{
		static int GetOffset(VertexComponent component)
		{
			switch(component)
			{
			case COMPONENT_POSITION:
				return 0;
			case COMPONENT_NORMAL:
				return 4*sizeof(float);
			case COMPONENT_TEXTURE:
				return 8*sizeof(float);
			case COMPONENT_BITANGENT:
				return 12*sizeof(float);
			case COMPONENT_TANGENT:
				return 16*sizeof(float);
			case COMPONENT_BONE_ID:
				return 20*sizeof(float);
			case COMPONENT_BONE_WEIGHT:
				return 24*sizeof(float);
			default:
				return -1;
			}
		}
	};

	struct VertexPositionTexture : public Vertex
	{
		float x, y, z, w;
		float u, v, s, q;
	};

	struct VertexPositionNormalTextureTangentBitangent : public Vertex
	{
		float x, y, z, w;
		float nx, ny, nz, nw;
		float u, v, s, q;
		float bx, by, bz, bw;
		float tx, ty, tz, tw;
	};


	struct VertexPositionNormalTextureTangentBitangentBone : public Vertex
	{
		float x, y, z, w;
		float nx, ny, nz, nw;
		float u, v, s, q;
		float bx, by, bz, bw;
		float tx, ty, tz, tw;
		float   b1, b2, b3, b4;
		float w1, w2, w3, w4;
	};
}

#endif