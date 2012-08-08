#ifndef _H_PUNK_UTILITY_WEAPON
#define _H_PUNK_UTILITY_WEAPON

#include "config.h"
#include "decl_property.h"
#include "../math/mat4.h"
#include "animation\animation_mixer.h"

namespace Utility
{
	class Scene;

	class LIB_UTILITY  WeaponType
	{
	public:
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

		struct WeaponElement
		{
			bool m_support;
			char m_geom_name[256];	//	filename in the geometry resources
			int  m_geom_index;
			Math::mat4 m_transform;
			AnimationMixer m_animation;	//	index in animation resources

			void Save(std::ostream& stream);
			void Load(std::istream& stream);
		};

		struct SoundElement
		{
			int m_sound_index;
			System::string m_sound_name;

			SoundElement() : m_sound_index(-1), m_sound_name(L"") {}
			SoundElement(const System::string& name) : m_sound_index(-1), m_sound_name(name) {} 
			void Save(std::ostream& stream);
			void Load(std::istream& stream);
		};

		struct TextureElement
		{
			int m_diffuse_map_index;
			System::string m_diffuse_map_name;
			int m_normal_map_index;
			System::string m_normal_map_name;
			
			void SetDiffuse(const System::string& v) { m_diffuse_map_name = v; }
			void SetNormal(const System::string& v) { m_normal_map_name = v; }
			
			const System::string& GetDiffuse() const { return m_diffuse_map_name; }
			const System::string& GetNormal() const { return m_normal_map_name; }

			TextureElement();
			TextureElement(const System::string& diffuse, const System::string& normal);

			void Save(std::ostream& stream);
			void Load(std::istream& stream);
		};

		void Save(std::ostream& stream);
		void Load(std::istream& stream);

		void MakeFromScheme(const System::string& name, const Scene& scene);

		PROPERTY(System::string, Name, m_name);
		PROPERTY(System::string, Description, m_description);
		PROPERTY(int, Weight, m_weight);
		PROPERTY(int, HolderSize, m_holder_size);
		PROPERTY(int, KillRange, m_kill_range);
		PROPERTY(int, BulletType, m_bullet_type);
//		PROPERTY(int, BackSightType, m_backsight_type);
		PROPERTY(CalibreType, TypeCallibre, m_callibre_type);
		PROPERTY(PurposeType, TypePurpose, m_purpose);
		PROPERTY(ControlType, TypeControl, m_control_type);
		PROPERTY(KillSourceType, TypeKillSource, m_kill_source_type);
		PROPERTY(UsageType, TypeUsage, m_usage_type);
		PROPERTY(AutomaticType, TypeAutomatic, m_automatic_type);
		PROPERTY(BarrelCountType, TypeBarrelCount, m_barrel_count_type);
		PROPERTY(BarrelType, TypeBarrel, m_barrel_type);
		PROPERTY(WeaponElement, Body, m_body);
		PROPERTY(WeaponElement, Holder, m_holder);
		PROPERTY(WeaponElement, Backsight, m_backsight);
		PROPERTY(WeaponElement, Light, m_light);
		PROPERTY(WeaponElement, GrenadeLauncher, m_grenade);
		PROPERTY(SoundElement, SoundShoot, m_shoot_sound);
		PROPERTY(SoundElement, SoundReload, m_reload_sound);
		PROPERTY(TextureElement, MapDiffuse, m_diffuse_map);
		PROPERTY(TextureElement, MapNormal, m_normal_map);

	private:

		System::string m_name;		
		System::string m_description;
		int m_weight;			//	gramms
		int m_holder_size;		//	count
		int m_kill_range;			//	meters
		int m_bullet_type;		//	bullet type index in bullets array
		//int m_backsight_type;	//	index of the backsight
		CalibreType m_callibre_type;
		PurposeType m_purpose;
		ControlType m_control_type;
		KillSourceType m_kill_source_type;
		UsageType m_usage_type;
		AutomaticType m_automatic_type;
		BarrelCountType m_barrel_count_type;
		BarrelType m_barrel_type;
		SoundElement m_shoot_sound;
		SoundElement m_reload_sound;

		TextureElement m_diffuse_map;
		TextureElement m_normal_map;

		WeaponElement m_body;
		WeaponElement m_holder;
		WeaponElement m_backsight;
		WeaponElement m_light;
		WeaponElement m_lock;
		WeaponElement m_grenade;		

	};	//WeaponType
}

#endif	//	_H_PUNK_UTILITY_WEAPON