#include "../../system/logger.h"
#include "../../system/binary_file.h"
#include "terrain_loader.h"

namespace Virtual
{
	TerrainLoader::TerrainLoader(const System::string& map_name, const Math::ivec2& block)
		: m_map_name(map_name)
		, m_block(block)
		, m_data(nullptr)
	{}

	unsigned TerrainLoader::Load()
	{
		System::string filename = System::string::Format(L"%s_%s.raw", m_block.X(), m_block.Y());
		
		System::Buffer buffer;
		if (!System::BinaryFile::Load(filename, buffer))
			return (out_error() << "Can't load " << filename << std::endl, 0);
		m_size = buffer.GetSize();
		m_data = buffer.Release();
		return ~0;
	}

	unsigned TerrainLoader::Decompress(void** data, unsigned* size)
	{
		*data = m_data;
		*size = m_size;
		return ~0;
	}

	unsigned TerrainLoader::Destroy()
	{
		return ~0;
	}

	TerrainLoader::~TerrainLoader()
	{
		//	it's ok, i hope. better call destroy separately
		Destroy();
	}
}