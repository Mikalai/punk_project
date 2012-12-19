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

		virtual bool Save(std::ostream& stream) const;
		virtual bool Load(std::istream& stream);

		static System::Proxy<GeometryNode> CreateFromFile(const System::string& path);
		static System::Proxy<GeometryNode> CreateFromStream(std::istream& stream);

		virtual bool Apply(AbstractVisitor* visitor);			
		
	protected:
		System::Proxy<Virtual::Geometry> GetGeometry() { return m_geometry; }

	private:		
		System::Proxy<Virtual::Geometry> m_geometry;		
	};
}

REGISTER_MANAGER(L"resource.geom_nodes", L"*.geometry_node", System::Environment::Instance()->GetModelFolder(), System::ObjectType::GEOMETRY_NODE, Scene, GeometryNode, return, return);

#endif	//	_H_PUNK_SCENE_GEOMETRY
