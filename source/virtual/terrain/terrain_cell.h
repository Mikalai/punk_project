#ifndef _H_PUNK_VIRTUAL_TERRAIN_CELL
#define _H_PUNK_VIRTUAL_TERRAIN_CELL

#include "../../config.h"
#include "../../string/string.h"
#include "../../math/vec2.h"

namespace Virtual
{
	class PUNK_ENGINE TerrainCell
	{
	public:
		TerrainCell();

		void SetLocation(const Math::ivec2& value) { m_core.m_location = value; }
		const Math::ivec2& GetLocation() const { return m_core.m_location; }

		void SetBaseHeight(float value) { m_core.m_base_height = value; }
		float GetBaseHeight() const { return m_core.m_base_height; }

		bool IsValid() { return m_core.m_is_valid; }

		void Validate() { m_core.m_is_valid = true; }
		void Invalidate() { m_core.m_is_valid = false; }

		void SetName(const System::string& value) { m_name = value; }
		const System::string& GetName() const { return m_name; }

		void SetRawFile(const System::string& value) { m_filename = value; }
		const System::string& GetRawFile() const { return m_filename; }

		bool Save(std::ostream& stream) const;
		bool Load(std::istream& stream);

	private:		

		struct Core
		{
			Math::ivec2 m_location;
			float m_base_height;
			bool m_is_valid;

			Core();
		};

		Core m_core;
		System::string m_name;
		System::string m_filename;		
	};
}

#endif	//	_H_PUNK_VIRTUAL_TERRAIN_CELL