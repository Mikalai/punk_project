#include "bone.h"

namespace Utility
{
	const Math::mat4& Bone::GetMatrix() const
	{
		return m_matrix;
	}

	const Math::mat4& Bone::GetBoneMatrix() const
	{
		return m_bone_matrix;
	}

	const System::string& Bone::GetName() const
	{
		return m_name;
	}

	const System::string& Bone::GetParentName() const
	{
		return m_parent_name;
	}

	void Bone::SetMatrix(const Math::mat4& matrix)
	{
		m_matrix = matrix;
	}

	void Bone::SetName(const System::string& name)
	{
		m_name = name;
	}

	void Bone::SetParent(int parent)
	{
		m_parent = parent;
	}

	void Bone::SetParentName(const System::string& pname)
	{
		m_parent_name = pname;
	}

	void Bone::SetBoneMatrix(const Math::mat4& m)
	{
		m_bone_matrix = m;
	}

	int Bone::GetParent() const
	{
		return m_parent;
	}
}