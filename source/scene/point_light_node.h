#ifndef _H_PUNK_SCENE_POINT_LIGHT_NODE
#define _H_PUNK_SCENE_POINT_LIGHT_NODE

#include "../config.h"
#include "light_node.h"
#include "../virtual/data/lights/point_light.h"

namespace Scene
{
	class PUNK_ENGINE PointLightNode : public LightNode
	{
	public:

		PointLightNode();

		virtual bool Save(std::ostream& stream) const;
		virtual bool Load(std::istream& stream);				

		static System::Proxy<PointLightNode> CreateFromFile(const System::string& path);
		static System::Proxy<PointLightNode> CreateFromStream(std::istream& stream);

		virtual bool Apply(AbstractVisitor* visitor);

		virtual System::Proxy<Virtual::Light> GetLight() { return m_point_light; }

		void SetPointLight(System::Proxy<Virtual::Light> value) { m_point_light = value; }
		System::Proxy<Virtual::PointLight> GetPointLight() { return m_point_light; }

	private:
		System::Proxy<Virtual::PointLight> m_point_light;
	};
}

REGISTER_MANAGER(L"resource.point_light_nodes", L"*.point_light_node", System::Environment::Instance()->GetModelFolder(), System::ObjectType::POINT_LIGHT_NODE, Scene, PointLightNode);

#endif	//	_H_PUNK_SCENE_POINT_LIGHT_NODE
