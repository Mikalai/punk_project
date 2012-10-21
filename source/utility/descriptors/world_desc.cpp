#include <sstream>
#include "../../system/logger.h"
#include "action_desc.h"
#include "material_desc.h"
#include "object_desc.h"
#include "world_desc.h"

namespace Utility
{
	std::wostream& WorldDesc::out_formatted(std::wostream& stream) const
	{
		stream << Tab() << typeid(*this).name() << std::endl;
		Tab::Inc();
		stream << Tab() << L"Objects: " << std::endl;
		Tab::Inc();
		for (auto object : m_objects)
			object->out_formatted(stream) << std::endl;
		Tab::Dec();
		stream << Tab() << L"Materials: " << std::endl;
		Tab::Inc();
		for (auto material : m_materials)
			material.second->out_formatted(stream) << std::endl;
		Tab::Dec();

		stream << Tab() << L"Actions: " << std::endl;
		Tab::Inc();
		for (auto action : m_actions)
			action.second->out_formatted(stream) << std::endl;
		Tab::Dec();
		
		stream << Tab::Dec() << typeid(*this).name();
		return stream;
	}

	const System::string WorldDesc::ToString() const
	{
		std::wstringstream stream;
		out_formatted(stream);
		std::wstring s = stream.str();
		return System::string(s.c_str());
	}

	WorldDesc::~WorldDesc()
	{
		for (auto object : m_objects)
			delete object;

		for (auto material : m_materials)
			delete material.second;

		for (auto action : m_actions)
			delete action.second;
	}
}