#ifndef _H_PUNK_UTILITY_WEAPON
#define _H_PUNK_UTILITY_WEAPON

#include "config.h"

namespace Utility
{
	struct LIB_UTILITY  WeaponType
	{
		enum CalibreType { 
			CALIBRE_NO,
			CALIBRE_SMALL, 		//	мелкокалиберное
			CALIBRE_NORMAL,		//	нормальное
			CALIBRE_LARGE		//	крупнокалиберное
		};			

		enum PurposeType { 
			PURPOSE_NO,
			PURPOSE_WAR, 		//боевое
			PURPOSE_RANGING, 	//пристрелочное
			PURPOSE_CLASS, 		//учебное
			PURPOSE_SPORT, 		//спортивное
			PURPOSE_HUNT		//охотничье
		};			

		enum ControlType { 
			CONTROL_NO,
			CONTROL_ONE_HAND_KNIFE,		//нож, сабля
			CONTROL_TWO_HAND_KNIFE,		//двурчный мечь, шест, бита
			CONTROL_REVOLVER, 			//револьвер
			CONTROL_PISTOL, 			//пистолет
			CONTROL_SUBMACHINE_GUN, 	//пистолет-пулемет
			CONTROL_GUN,				//автомат
			CONTROL_RIFLE,				//винтовка
			CONTROL_CARABINE,			//карабин
			CONTROL_MACHINE_GUN, 		//пулемет
			CONTROL_GRENADE_LAUNCHER	//гранатомет
		};

		enum KillSourceType {
			KILL_SOURCE_NO,
			KILL_SOURCE_COLD,			//холодное оружие
			KILL_SOURCE_FIRING,			//огнестрельное
			KILL_SOURCE_PNEUMATIC 		//пневматическое
		};

		enum UsageType {
			USAGE_NO,
			USAGE_PORTABLE,			//	ручное
			USAGE_STATIONAR			//	станковое
		};			

		enum AutomaticType {
			AUTOMATIC_NO,
			AUTOMATIC_FULL,			//автоматическое
			AUTOMATIC_SELF_RELOADING,	//самозарядное
		};			

		enum BarrelCountType {
			BARREL_COUNT_NO,
			BARREL_COUNT_ONE, 			//одноствольное
			BARREL_COUNT_TWO,			//двухствольное
			BARREL_COUNT_MANY 		//многоствольное
		};

		enum BarrelType {
			BARREL_NO,
			BARREL_RIFLED,	//нарезной
			BARREL_SMOOTH_BORE //гладкоствольный
		};	

		static const int MAX_NAME_SIZE = 64;
		static const int MAX_DESCRIPTION_SIZE = 192;
		wchar_t m_name[MAX_NAME_SIZE];
		wchar_t m_description[MAX_DESCRIPTION_SIZE];
		int m_weight;			//	gramms
		int m_holder_size;		//	count
		int m_kill_range;			//	meters
		int m_bullet_type;		//	bullet type index in bullets array
		int m_backsight_type;	//	index of the backsight
		int m_index;			//	index of the weapon in the array
		CalibreType m_callibre_type;
		PurposeType m_purpose;
		ControlType m_control_type;
		KillSourceType m_kill_source_type;
		UsageType m_usage_type;
		AutomaticType m_automatic_type;
		BarrelCountType m_barrel_count_type;
		BarrelType m_barrel_type;

		void SetName(const wchar_t* name);
		void SetDescription(const wchar_t* desc);
		void Save(std::ostream& stream);
		void Load(std::istream& stream);
	};	//WeaponType
}

#endif	//	_H_PUNK_UTILITY_WEAPON