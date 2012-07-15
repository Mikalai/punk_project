#ifndef _H_BULLET_TYPE
#define _H_BULLET_TYPE

#include "config.h"

namespace Utility
{
	struct LIB_UTILITY BulletType
	{
		static const int MAX_NAME_SIZE = 64;
		static const int MAX_DESCRIPTION_SIZE = 192;
		wchar_t m_name[MAX_NAME_SIZE];
		wchar_t m_description[MAX_DESCRIPTION_SIZE];
		int m_weight;			//grams
		int m_start_speed;		//meters per second
		int m_energy;			//joul
		int m_index;			//index in the array of bullets
		int m_kill_range;

		void SetName(const wchar_t* name);
		void SetDescription(const wchar_t* desc);
		void Save(std::ostream& stream);
		void Load(std::istream& stream);
	};


};

#endif	//	_H_BULLET_TYPE