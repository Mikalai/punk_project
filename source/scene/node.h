#ifndef _H_PUNK_SCENE_NODE
#define _H_PUNK_SCENE_NODE

#include <vector>
#include "../system/compound_object.h"
#include "../system/resource_manager.h"
#include "../string/string.h"
#include "visitor.h"
#include "../math/bounding_box.h"

namespace Virtual { class Entity; }

namespace Scene
{

	class PUNK_ENGINE Node : public System::CompoundObject
	{

	public:
		Node();
		virtual bool Save(std::ostream& stream) const;
		virtual bool Load(std::istream& stream);
		virtual ~Node();		

		static System::Proxy<Node> CreateFromFile(const System::string& path);
		static System::Proxy<Node> CreateFromStream(std::istream& stream);
			
		virtual bool Apply(AbstractVisitor* visitor);

	protected:
		virtual bool Update(int time_ms);
	private:

		Math::BoundingBox m_bbox;

	private:
		Node(const Node&);
		Node& operator = (const Node&);
		void Init();
		void Clear();	
	};
}

REGISTER_MANAGER(L"resource.nodes", L"*.node", System::Environment::Instance()->GetModelFolder(), System::ObjectType::NODE, Scene, Node, return, return);

#endif	//	H_PUNK_SCENE_NODE