#ifndef _H_PUNK_BONE
#define _H_PUNK_BONE

#include "../config.h"
#include "../../math/mat4.h"
#include "../../system/string.h"

namespace Utility
{
	class LIB_UTILITY Bone
	{
		int m_parent;
		System::string m_name;
		Math::mat4 m_matrix;

	public:
	//	void SetParent(int parent);
		void SetName(const System::string& name);
		void SetMatrix(const Math::mat4& matrix);

		const System::string& GetName() const;
		const Math::mat4& GetMatrix() const;
	//	int GetParent() const;
	};
}

#endif