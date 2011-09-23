#ifndef _H_PUNK_BONE
#define _H_PUNK_BONE

#include "../config.h"
#include "../../math/mat4.h"
#include "../../system/string.h"

namespace Utility
{
	typedef System::string BoneName;

	class LIB_UTILITY Bone
	{
		int        m_parent;
		BoneName   m_parent_name;
		BoneName   m_name;
		Math::mat4 m_matrix;

	public:
		void SetName(const System::string& name);
		void SetMatrix(const Math::mat4& matrix);
		void SetParent(int parent);
		void SetParentName(const System::string& name);

		const BoneName& GetName() const;
		const BoneName& GetParentName() const;
		const Math::mat4& GetMatrix() const;
		int GetParent() const;
	};
}

#endif