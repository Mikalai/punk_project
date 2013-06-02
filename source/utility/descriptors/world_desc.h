#ifndef _H_PUNK_VIRTUAL_WORLD_DESC
#define _H_PUNK_VIRTUAL_WORLD_DESC

#include <map>
#include <iosfwd>
#include "../../config.h"
#include "../../string/string.h"

#include <vector>

namespace Utility
{
	class ObjectDesc;
	class MaterialDesc;
	class ArmatureDesc;
	class ActionDesc;

	class PUNK_ENGINE_API WorldDesc
	{
	public:
		std::vector<ObjectDesc*> m_children;
		std::map<System::string, MaterialDesc*> m_materials;		
		std::map<System::string, ActionDesc*> m_actions;
		~WorldDesc();

		const System::string ToString() const;
		///	analog;
		std::wostream& out_formatted(std::wostream& stream) const;

	};
}

#endif	//	_H_PUNK_VIRTUAL_SCENE_DESC