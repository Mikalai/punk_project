#ifndef _H_PUNK_VIRTUAL_TRANSFORM
#define _H_PUNK_VIRTUAL_TRANSFORM

#include "entity.h"
#include "../../math/mat4.h"
#include "../../system/compound_object.h"

namespace Utility { class ObjectDesc; }

namespace Virtual
{
	class PUNK_ENGINE_API TransformNode : public System::CompoundObject
	{
	public:

		TransformNode();
		TransformNode(const Math::mat4& m);
		
		void Set(const Math::mat4& value) { m_transform = value; }
		const Math::mat4& Get() const { return m_transform; }
		Math::mat4& Get() { return m_transform; }

		virtual bool Save(std::ostream& stream) const;
		virtual bool Load(std::istream& stream);

		virtual ~TransformNode();

	private:
		Math::mat4 m_transform;

	private:
		TransformNode(const TransformNode&);
		TransformNode& operator = (const TransformNode&);
	};
}

#endif	//	_H_PUNK_VIRTUAL_TRANSFORM