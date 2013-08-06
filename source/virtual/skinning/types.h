#ifndef _H_PUNK_VIRTUAL_SKINNING_TYPES
#define _H_PUNK_VIRTUAL_SKINNING_TYPES

#include <memory>
#include <map>
#include "../../string/string.h"

namespace Virtual
{
	class Bone;
	typedef System::string BoneName;
	typedef int BoneID;		
	typedef float Weight;
	typedef std::map<BoneName, Weight> BoneWeights;
	typedef std::map<BoneName, std::shared_ptr<Bone>> BonesCollection;
	typedef std::vector<Bone*> BonesCache;
	typedef std::map<BoneName, Bone*> BonesNamedCache;
}

#endif	//	_H_PUNK_VIRTUAL_SKINNING_TYPES