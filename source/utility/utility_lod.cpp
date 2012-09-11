#include <ostream>
#include <istream>

#include "utility_lod.h"

namespace Utility
{
	void LodContainer::PushLod(StaticMesh* lod)
	{
		m_meshes.push_back(lod);
	}

	StaticMesh* LodContainer::GetLod(int level)
	{
		if (level >= (int)m_meshes.size())
			return 0;
		return m_meshes[level];
	}

	void LodContainer::Save(std::ostream& stream)
	{
		int size = m_meshes.size();
		stream.write(reinterpret_cast<const char*>(&size), sizeof(size));
		for (int i = 0; i < size; ++i)
		{
			m_meshes[i]->Save(stream);
		}
	}

	void LodContainer::Load(std::istream& stream)
	{
		int size;
		stream.read(reinterpret_cast<char*>(&size), sizeof(size));
		for (int i = 0; i < size; ++i)
		{
			StaticMesh* mesh = new StaticMesh;
			mesh->Load(stream);
			m_meshes.push_back(mesh);
		}
	}
}