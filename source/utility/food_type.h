#ifndef _H_PUNK_UTILITY_FOOD_TYPE
#define _H_PUNK_UTILITY_FOOD_TYPE

#include "../config.h"
#include <vector>
#include "../system/template_singletone.h"
#include <fstream>

namespace Utility
{

#define MAX_NAME  28
#define MAX_DESCRIPTION_LENGTH  100

	struct PUNK_ENGINE FoodType
	{
		int		m_code;					//	equals to the index in the allfoodtype array
		int		m_satiety;
		int		m_reserved[8];			//	some effects or other parameters
		wchar_t m_name[MAX_NAME];
		wchar_t m_description[MAX_DESCRIPTION_LENGTH];		

		void FromTextFileANSI(const char* filename);
		void FromTextFileUTF(const char* filename);
		void SetName(const wchar_t* name);
		void SetDescription(const wchar_t* desc);
		void Save(std::ostream& stream);
		void Load(std::istream& stream);
	};
/*
	struct AllFoodTypes : public System::Singletone<AllFoodTypes>
	{
		std::vector<FoodType> m_food_types;

		void Save(std::ostream& stream);
		void Load(std::istream& stream);
	};

	struct Food
	{
		int food_type;
	};*/
}

#endif