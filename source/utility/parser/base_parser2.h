#ifndef _H_PUNK_VIRTUAL_BASE_LOADER
#define _H_PUNK_VIRTUAL_BASE_LOADER

#include <vector>
#include "../../utility/model/vertex_bone_weight.h"
#include "../../virtual/animation/animation_track.h"
#include "keywords.h"
#include "../../system/object.h"


namespace Utility
{
	PUNK_ENGINE System::Proxy<System::Object> ParsePunkFile(const System::string& path);
	PUNK_ENGINE System::Proxy<System::Object>  LoadWorld(const System::string& path);
}

#endif