#ifndef _H_PUNK_SCENE_GEOMETRY
#define _H_PUNK_SCENE_GEOMETRY

#include "../config.h"
#include "../virtual/data/geometry.h"
#include "node.h"

namespace Scene
{
	class PUNK_ENGINE_API GeometryNode : public Node
	{
	public:

		GeometryNode();

		void SetGeometry(Virtual::Geometry* value) { m_geometry = value; }

		virtual bool Save(std::ostream& stream) const;
		virtual bool Load(std::istream& stream);

		static GeometryNode* CreateFromFile(const System::string& path);
		static GeometryNode* CreateFromStream(std::istream& stream);

		virtual bool Apply(AbstractVisitor* visitor);			
		
		bool HasGeometry() const { return nullptr != m_geometry; }

		Virtual::Geometry* GetGeometry() { return m_geometry; }

	private:		
		Virtual::Geometry* m_geometry;		
	};
}

#endif	//	_H_PUNK_SCENE_GEOMETRY
