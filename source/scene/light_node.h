#ifndef _H_PUNK_SCENE_LIGHT_NODE
#define _H_PUNK_SCENE_LIGHT_NODE

#include "node.h"
#include "../virtual/data/light_set.h"

namespace Scene
{
	class PUNK_ENGINE_API LightNode : public Node
	{
	public:

		LightNode();

		virtual bool Save(std::ostream& stream) const;
		virtual bool Load(std::istream& stream);		

		//void SetLightSet(System::Proxy<Virtual::LightSet> value) { m_light_set = value; }
		//System::Proxy<Virtual::LightSet> GetLightSet() { return m_light_set; }

		//static System::Proxy<LightNode> CreateFromFile(const System::string& path);
		//static System::Proxy<LightNode> CreateFromStream(std::istream& stream);

		virtual bool Apply(AbstractVisitor* visitor);

		virtual Virtual::Light* GetLight() = 0;

	private:
		//System::Proxy<Virtual::LightSet> m_light_set;
	};
}

#endif	//	_H_PUNK_SCENE_LIGHT_NODE
