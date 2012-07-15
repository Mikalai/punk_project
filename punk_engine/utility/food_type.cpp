#include <istream>
#include <ostream>
#include <iostream>

#include "food_type.h"
#include "../system/string.h"

namespace Utility
{
	void FoodType::SetName(const wchar_t* name)
	{
		wcsncpy(m_name, name, MAX_NAME - 1);
	}

	void FoodType::SetDescription(const wchar_t* desc)
	{
		wcsncpy(m_description, desc, MAX_DESCRIPTION_LENGTH - 1);
	}

	void FoodType::FromTextFileANSI(const char* filename)
	{
		std::ifstream stream(filename);
		char buf[256];
		stream >> buf;
		System::string tmp(buf);
		SetName(tmp.Data());
		stream >> buf;

		SetDescription(System::string(buf).Replace(L"_", L" ").Data());
		stream >> m_satiety;
		stream.close();
	}

	void FoodType::FromTextFileUTF(const char* filename)
	{}

	void FoodType::Save(std::ostream& stream)
	{
		stream.write(reinterpret_cast<const char*>(this), sizeof(FoodType));
	}

	void FoodType::Load(std::istream& stream)
	{
		stream.read(reinterpret_cast<char*>(this), sizeof(FoodType));
	}
}