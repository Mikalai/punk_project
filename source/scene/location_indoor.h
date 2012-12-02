#ifndef _H_PUNK_SCENE_LOCATION_INDOOR
#define _H_PUNK_SCENE_LOCATION_INDOOR

#include "../math/convex_shape_mesh.h"
#include "transform_node.h"

namespace Scene
{
	class PUNK_ENGINE LocationIndoorNode : public TransformNode
	{
	public:
			
		LocationIndoorNode();

		virtual bool Save(std::ostream& stream) const;
		virtual bool Load(std::istream& stream);

		static System::Proxy<LocationIndoorNode> CreateFromFile(const System::string& path);
		static System::Proxy<LocationIndoorNode> CreateFromStream(std::istream& stream);

		virtual bool Apply(AbstractVisitor* visitor);

		void SetConvexMesh(const Math::ConvexShapeMesh shape) { m_convex_mesh = shape; }
		const Math::ConvexShapeMesh& GetConvexShape() const { return m_convex_mesh; }

	protected:
		Math::ConvexShapeMesh m_convex_mesh;
	};
}

REGISTER_MANAGER(L"resource.indoor_locations", L"*.indoor", System::Environment::Instance()->GetModelFolder(), System::ObjectType::LOCATION_INDOOR, Scene, LocationIndoorNode);

#endif	//	_H_PUNK_SCENE_LOCATION_INDOOR