#ifndef _H_PUNK_SCENE_POINT_LIGHT_NODE
#define _H_PUNK_SCENE_POINT_LIGHT_NODE

#include "../config.h"
#include "light_node.h"
#include "../virtual/data/lights/point_light.h"

namespace Scene
{
	class PUNK_ENGINE_API PointLightNode : public LightNode
	{
	public:

		PointLightNode();

		virtual bool Save(std::ostream& stream) const override;
		virtual bool Load(std::istream& stream) override;
		virtual bool Apply(AbstractVisitor* visitor) override;
		virtual Virtual::Light* GetLight() override { return m_point_light; }

		static PointLightNode* CreateFromFile(const System::string& path);
		static PointLightNode* CreateFromStream(std::istream& stream);

		void SetPointLight(Virtual::PointLight* value) { m_point_light = value; }
		Virtual::PointLight* GetPointLight() { return m_point_light; }

        virtual Node* Clone() const override;

	private:
		Virtual::PointLight* m_point_light;
	};
}

#endif	//	_H_PUNK_SCENE_POINT_LIGHT_NODE
