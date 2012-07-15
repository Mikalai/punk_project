#ifndef _H_PUNK_UTILITY_WEAPON
#define _H_PUNK_UTILITY_WEAPON

#include "config.h"

namespace Utility
{
	struct LIB_UTILITY  WeaponType
	{
		enum CalibreType { 
			CALIBRE_NO,
			CALIBRE_SMALL, 		//	���������������
			CALIBRE_NORMAL,		//	����������
			CALIBRE_LARGE		//	����������������
		};			

		enum PurposeType { 
			PURPOSE_NO,
			PURPOSE_WAR, 		//������
			PURPOSE_RANGING, 	//�������������
			PURPOSE_CLASS, 		//�������
			PURPOSE_SPORT, 		//����������
			PURPOSE_HUNT		//���������
		};			

		enum ControlType { 
			CONTROL_NO,
			CONTROL_ONE_HAND_KNIFE,		//���, �����
			CONTROL_TWO_HAND_KNIFE,		//�������� ����, ����, ����
			CONTROL_REVOLVER, 			//���������
			CONTROL_PISTOL, 			//��������
			CONTROL_SUBMACHINE_GUN, 	//��������-�������
			CONTROL_GUN,				//�������
			CONTROL_RIFLE,				//��������
			CONTROL_CARABINE,			//�������
			CONTROL_MACHINE_GUN, 		//�������
			CONTROL_GRENADE_LAUNCHER	//����������
		};

		enum KillSourceType {
			KILL_SOURCE_NO,
			KILL_SOURCE_COLD,			//�������� ������
			KILL_SOURCE_FIRING,			//�������������
			KILL_SOURCE_PNEUMATIC 		//��������������
		};

		enum UsageType {
			USAGE_NO,
			USAGE_PORTABLE,			//	������
			USAGE_STATIONAR			//	���������
		};			

		enum AutomaticType {
			AUTOMATIC_NO,
			AUTOMATIC_FULL,			//��������������
			AUTOMATIC_SELF_RELOADING,	//������������
		};			

		enum BarrelCountType {
			BARREL_COUNT_NO,
			BARREL_COUNT_ONE, 			//�������������
			BARREL_COUNT_TWO,			//�������������
			BARREL_COUNT_MANY 		//��������������
		};

		enum BarrelType {
			BARREL_NO,
			BARREL_RIFLED,	//��������
			BARREL_SMOOTH_BORE //���������������
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