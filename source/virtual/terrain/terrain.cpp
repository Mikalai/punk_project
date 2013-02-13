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
		strcpy_s<16>(m_head, "MAPDESCBIN");
	}

	Terrain::Terrain()		
	{
		m_cells.SetSize(1,1);
	}

	Terrain::~Terrain()
	{
		safe_delete(m_material);
		for (int row = 0; row < m_cells.RowCount(); ++row)
			for (int col = 0; col < m_cells.ColumnCount(); ++col)
				safe_delete(m_cells.At(row, col));
	}

	void Terrain::SetNumBlocks(int value)
	{
		m_core.m_num_blocks = value;
		m_cells.SetSize(value, value);
		for (int row = 0; row < m_cells.RowCount(); ++row)
		{
			for (int col = 0; col < m_cells.ColumnCount(); ++col)
			{
				m_cells.At(row, col) = new TerrainCell;
			}
		}
	}

	bool Terrain::AddOrUpdateCell(const TerrainCell& value)
	{
		if (value.GetLocation().X() < 0 || value.GetLocation().X() >= m_cells.ColumnCount())
			throw System::PunkInvalidArgumentException(L"Cell X position " + System::string::Convert(value.GetLocation().X()) + L" is incorrect. Should be in the range [0; " + System::string::Convert(m_cells.ColumnCount()) + L"]");
		if (value.GetLocation().Y() < 0 || value.GetLocation().Y() >= m_cells.RowCount())
			throw System::PunkInvalidArgumentException(L"Cell Y position " + System::string::Convert(value.GetLocation().Y()) + L" is incorrect. Should be in the range [0; " + System::string::Convert(m_cells.RowCount()) + L"]");
		auto v = m_cells.At(value.GetLocation().Y(), value.GetLocation().X());
		TerrainCell& t = *v;
		t = value;
		return true;
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
				stream << L"\t*raw_data_source " << std::endl << L"\t{ " << std::endl;
				stream << L"\t\t*ref { " << cell->GetRawDataSource().GetRawFile().Data() << L" }" << std::endl;
				stream << L"\t}" << std::endl;
				stream << L"}" << std::endl;
			}
		}
		return System::string(stream.str().c_str());
	}

	bool Terrain::Save(std::ostream& stream) const
	{		
		Object::Save(stream);

		stream.write((char*)&m_core, sizeof(m_core));
		for (int y = 0; y < GetNumBlocks(); ++y)
		{
			for (int x = 0; x < GetNumBlocks(); ++x)
			{
				const TerrainCell* cell = GetCell(x, y);
				cell->Save(stream);
			}
		}
		return true;
	}

	bool Terrain::Load(std::istream& stream)
	{
		Object::Load(stream);
		stream.read((char*)&m_core, sizeof(m_core));
		SetNumBlocks(GetNumBlocks());
		for (int y = 0; y < GetNumBlocks(); ++y)
		{
			for (int x = 0; x < GetNumBlocks(); ++x)
			{
				TerrainCell* cell = GetCell(x, y);
				cell->Load(stream);
			}
		}
		return true;
	}
}