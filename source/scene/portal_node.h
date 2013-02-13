#ifndef _H_PUNK_SCENE_PORTAL_NODE
#define _H_PUNK_SCENE_PORTAL_NODE

#include "../math/portal.h"
#include "transform_node.h"

namespace Scene
{

	class PUNK_ENGINE PortalNode : public TransformNode
	{
	public:

		PortalNode();

		virtual bool Save(std::ostream& stream) const;
		virtual bool Load(std::istream& stream);

		static PortalNode* CreateFromFile(const System::string& path);
		static PortalNode* CreateFromStream(std::istream& stream);

		virtual bool Apply(AbstractVisitor* visitor);

		void SetPortal(const Math::Portal& value) { m_portal = value; }
		const Math::Portal& GetPortal() const { return m_portal; }

	protected:
		Math::Portal m_portal;
	};
}

#endif