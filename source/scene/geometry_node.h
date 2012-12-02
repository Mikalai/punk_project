#ifndef _H_PUNK_SCENE_GEOMETRY
#define _H_PUNK_SCENE_GEOMETRY

#include "../config.h"
#include "../virtual/data/geometry.h"
#include "node.h"

namespace Scene
{
	class PUNK_ENGINE GeometryNode : public Node
	{
	public:

		GeometryNode();

		void SetGeometry(System::Proxy<Virtual::Geometry> value) { m_geometry = value; }
		const System::Proxy<Virtual::Geometry> GetGeometry() const { return m_geometry; }

		virtual bool Save(std::ostream& stream) const;
		virtual bool Load(std::istream& stream);

		static System::Proxy<GeometryNode> CreateFromFile(const System::string& path);
		static System::Proxy<GeometryNode> CreateFromStream(std::istream& stream);

		virtual bool Apply(AbstractVisitor* visitor);			

	private:		

		System::Proxy<Virtual::Geometry> m_geometry;		
	};
}

REGISTER_MANAGER(L"resource.geom_nodes", L"*.geometry_node", System::Environment::Instance()->GetModelFolder(), System::ObjectType::GEOMETRY_NODE, Scene, GeometryNode);

#endif	//	_H_PUNK_SCENE_GEOMETRY
