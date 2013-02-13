#ifndef _H_PUNK_SCENE_TRANSFORM
#define _H_PUNK_SCENE_TRANSFORM

#include "../config.h"
#include "../math/mat4.h"
#include "node.h"

namespace Scene
{
	class PUNK_ENGINE TransformNode : public Node
	{
	public:

		TransformNode();

		virtual bool Save(std::ostream& stream) const;
		virtual bool Load(std::istream& stream);

		static TransformNode* CreateFromFile(const System::string& path);
		static TransformNode* CreateFromStream(std::istream& stream);

		virtual bool Apply(AbstractVisitor* visitor);

		void SetLocalMatrix(const Math::mat4& m) { m_local = m; }
		const Math::mat4& GetLocalMatrix() const { return m_local; }

		const Math::mat4& GetGlobalMatrix() const { return m_global; }

	private:
		Math::mat4 m_local;
		Math::mat4 m_global;
	};
}


#endif