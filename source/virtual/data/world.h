#ifndef _H_PUNK_VIRTUAL_WORLD
#define _H_PUNK_VIRTUAL_WORLD

#include <memory>
#include "../../config.h"
#include "../../system/object.h"

namespace Utility { class WorldDesc; }
namespace Scene { class Node; }
namespace Scene { class NodeVisitor; }

namespace Virtual
{
	class PUNK_ENGINE_PUBLIC World : public System::Object
	{		
	public:
		World();
		World(const Utility::WorldDesc& value);
		virtual ~World();

		bool Traverse(Scene::NodeVisitor* value) const;
	private:
		std::unique_ptr<Scene::Node> m_root;		
	};
}

#endif	//	_H_PUNK_VIRTUAL_WORLD
