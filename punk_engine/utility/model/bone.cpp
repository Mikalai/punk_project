#include "bone.h"

namespace Utility
{
	const Math::mat4& Bone::GetMatrix() const
	{
		return m_matrix;
	}

	const System::string& Bone::GetName() const
	{
		return m_name;
	}

	void Bone::SetMatrix(const Math::mat4& matrix)
	{
		m_matrix = matrix;
	}

	void Bone::SetName(const System::string& name)
	{
		m_name = name;
	}

}