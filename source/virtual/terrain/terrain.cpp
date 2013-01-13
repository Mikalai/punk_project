#include <sstream>
#include "../../system/logger.h"
#include "terrain.h"

namespace Virtual
{
	Terrain::Core::Core()		
		: m_num_blocks(1)
		, m_block_scale(0.5)
		, m_block_size(512)
		, m_height_scale(1000)
		, m_origin(0,0)
	{
		strcpy(m_head, "MAPDESCBIN");
	}

	Terrain::Terrain()		
	{
		m_cells.SetSize(1,1);
	}

	void Terrain::SetNumBlocks(int value)
	{
		m_core.m_num_blocks = value;
		m_cells.SetSize(value, value);
	}

	const System::string Terrain::ToString() const
	{
		std::wstringstream stream;
		stream << L"MAPDESCTEXT" << std::endl;
		stream << L"*num_blocks { " << m_core.m_num_blocks << L" } " << std::endl;
		stream << L"*block_scale { " << m_core.m_block_scale << L" } " << std::endl;
		stream << L"*block_size { " << m_core.m_block_size << L" } " << std::endl;
		stream << L"*height_scale { " << m_core.m_height_scale << L" } " << std::endl;
		stream << L"*world_origin { " << m_core.m_origin[0] << " " << m_core.m_origin[1] << L" } " << std::endl;
		
		for (int y = 0; y < m_core.m_num_blocks; ++y)
		{
			for (int x = 0; x < m_core.m_num_blocks; ++x)
			{
				const TerrainCell* cell = GetCell(x, y);
				stream << L"*cell " << std::endl << L"{ " << std::endl;
				stream << L"\t*name { " << cell->GetName().Data() << L" }" << std::endl;
				stream << L"\t*location { " << cell->GetLocation().X() << " " << cell->GetLocation().Y() << L" }" << std::endl;
				stream << L"\t*raw_file " << std::endl << L"\t{ " << std::endl;
				stream << L"\t\t*ref { " << cell->GetRawFile().Data() << L" }" << std::endl;
				stream << L"\t}" << std::endl;
				stream << L"}" << std::endl;
			}
		}
		return System::string(stream.str().c_str());
	}

	bool Terrain::Save(std::ostream& stream) const
	{		
		stream.write((char*)&m_core, sizeof(m_core));
		for (int y = 0; y < GetNumBlocks(); ++y)
		{
			for (int x = 0; x < GetNumBlocks(); ++x)
			{
				const TerrainCell* cell = GetCell(x, y);
				if (!cell->Save(stream))
					return (out_error() << "Can't save terrain cell" << std::endl, false);
			}
		}
		return true;
	}

	bool Terrain::Load(std::istream& stream)
	{
		stream.read((char*)&m_core, sizeof(m_core));
		m_cells.SetSize(GetNumBlocks(), GetNumBlocks());
		for (int y = 0; y < GetNumBlocks(); ++y)
		{
			for (int x = 0; x < GetNumBlocks(); ++x)
			{
				TerrainCell* cell = GetCell(x, y);
				if (!cell->Load(stream))
					return (out_error() << "Can't load terrain cell" << std::endl, false);
			}
		}
		return true;
	}
}