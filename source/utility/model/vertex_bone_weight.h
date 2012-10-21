#ifndef _H_PUNK_UTILITY_VERTEX_BONE_WEIGHT
#define _H_PUNK_UTILITY_VERTEX_BONE_WEIGHT

#include <map>
#include "../../string/string.h"
#include "vertex_index.h"

namespace Virtual
{
	typedef std::map<VertexIndex, std::map<System::string, float>> VertexBoneWeights;
}

#endif