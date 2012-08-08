#include <ostream>
#include <istream>
#include <string.h>

#include "../system/logger.h"
#include "weapon_type.h"
#include "model\punk_scene_loader.h"
#include "model\object.h"

namespace Utility
{
	void WeaponType::WeaponElement::Save(std::ostream& stream)
	{
		stream.write((char*)&m_support, sizeof(m_support));
		stream.write((char*)&m_geom_name[0], sizeof(m_geom_name));	//	filename in the geometry resources
		stream.write((char*)&m_geom_index, sizeof(m_geom_index));
		stream.write((char*)&m_transform, sizeof(m_transform));
		m_animation.Save(stream);	//	index in animation resources
	}

	void WeaponType::WeaponElement::Load(std::istream& stream)
	{
		stream.read((char*)&m_support, sizeof(m_support));
		stream.read((char*)&m_geom_name[0], sizeof(m_geom_name));	//	filename in the geometry resources
		stream.read((char*)&m_geom_index, sizeof(m_geom_index));
		stream.read((char*)&m_transform, sizeof(m_transform));
		m_animation.Load(stream);	//	index in animation resources
	}

	void WeaponType::SoundElement::Save(std::ostream& stream)
	{
		stream.write((char*)&m_sound_index, sizeof(m_sound_index));
		m_sound_name.Save(stream);
	}

	void WeaponType::SoundElement::Load(std::istream& stream)
	{
		stream.read((char*)&m_sound_index, sizeof(m_sound_index));
		m_sound_name.Load(stream);
	}

	void WeaponType::Save(std::ostream& stream)
	{
		m_name.Save(stream);		
		m_description.Save(stream);
		stream.write((char*)&m_weight, sizeof(m_weight));
		stream.write((char*)&m_holder_size, sizeof(m_holder_size));		//	count
		stream.write((char*)&m_kill_range, sizeof(m_kill_range));			//	meters
		stream.write((char*)&m_bullet_type, sizeof(m_bullet_type));		//	bullet type index in bullets array
//		stream.write((char*)&m_backsight_type, sizeof(m_backsight_type));	//	index of the backsight
		stream.write((char*)&m_callibre_type, sizeof(m_callibre_type));
		stream.write((char*)&m_purpose, sizeof(m_purpose));
		stream.write((char*)&m_control_type, sizeof(m_control_type));
		stream.write((char*)&m_kill_source_type, sizeof(m_kill_source_type));
		stream.write((char*)&m_usage_type, sizeof(m_usage_type));
		stream.write((char*)&m_automatic_type, sizeof(m_automatic_type));
		stream.write((char*)&m_barrel_count_type, sizeof(m_barrel_count_type));
		stream.write((char*)&m_barrel_type, sizeof(m_barrel_type));
		
		m_body.Save(stream);
		m_holder.Save(stream);
		m_backsight.Save(stream);
		m_light.Save(stream);
		m_lock.Save(stream);
		m_grenade.Save(stream);

		m_reload_sound.Save(stream);
		m_shoot_sound.Save(stream);

		m_diffuse_map.Save(stream);
		m_normal_map.Save(stream);
	}

	void WeaponType::Load(std::istream& stream)
	{
		m_name.Load(stream);		
		m_description.Load(stream);
		stream.read((char*)&m_weight, sizeof(m_weight));
		stream.read((char*)&m_holder_size, sizeof(m_holder_size));		//	count
		stream.read((char*)&m_kill_range, sizeof(m_kill_range));			//	meters
		stream.read((char*)&m_bullet_type, sizeof(m_bullet_type));		//	bullet type index in bullets array
//		stream.read((char*)&m_backsight_type, sizeof(m_backsight_type));	//	index of the backsight
		stream.read((char*)&m_callibre_type, sizeof(m_callibre_type));
		stream.read((char*)&m_purpose, sizeof(m_purpose));
		stream.read((char*)&m_control_type, sizeof(m_control_type));
		stream.read((char*)&m_kill_source_type, sizeof(m_kill_source_type));
		stream.read((char*)&m_usage_type, sizeof(m_usage_type));
		stream.read((char*)&m_automatic_type, sizeof(m_automatic_type));
		stream.read((char*)&m_barrel_count_type, sizeof(m_barrel_count_type));
		stream.read((char*)&m_barrel_type, sizeof(m_barrel_type));
	
		m_body.Load(stream);
		m_holder.Load(stream);
		m_backsight.Load(stream);
		m_light.Load(stream);
		m_lock.Load(stream);
		m_grenade.Load(stream);

		m_reload_sound.Load(stream);
		m_shoot_sound.Load(stream);

		m_diffuse_map.Load(stream);
		m_normal_map.Load(stream);
	}

	WeaponType::TextureElement::TextureElement()
		: m_diffuse_map_index(-1)
		, m_diffuse_map_name(L"")
		, m_normal_map_index(-1)
		, m_normal_map_name(L"")
	{}
		
	WeaponType::TextureElement::TextureElement(const System::string& diffuse, const System::string& normal)
		: m_diffuse_map_index(-1)
		, m_diffuse_map_name(diffuse)
		, m_normal_map_index(-1)
		, m_normal_map_name(normal)
	{}

	void WeaponType::TextureElement::Save(std::ostream& stream)
	{
		stream.write((char*)&m_diffuse_map_index, sizeof(m_diffuse_map_index));
		m_diffuse_map_name.Save(stream);
		stream.write((char*)&m_normal_map_index, sizeof(m_normal_map_index));
		m_normal_map_name.Save(stream);
	}
	
	void WeaponType::TextureElement::Load(std::istream& stream)
	{
		stream.read((char*)&m_diffuse_map_index, sizeof(m_diffuse_map_index));
		m_diffuse_map_name.Load(stream);
		stream.read((char*)&m_normal_map_index, sizeof(m_normal_map_index));
		m_normal_map_name.Load(stream);
	}

	void WeaponType::MakeFromScheme(const System::string& name, const Scene& scene)
	{
		const Object* weapon_tranform = scene.FindObjectByName(L"weapon_transform");
		if (!weapon_tranform)
		{
			System::Logger::Instance()->WriteError(L"Can't find 'weapon_tranform' scene is not a weapon scheme");
			return;
		}

		{
			const Object* body_mesh = weapon_tranform->GetChild(name + L"_body_mesh");
			if (!body_mesh)
			{
				System::Logger::Instance()->WriteError(L"Can't find '*body_mesh' scene is not a weapon scheme");
				return;
			}
			m_body.m_support = true;
			m_body.m_geom_index = -1;
			System::string filename = name + L"_body_mesh.vao";
			filename.ToANSI(m_body.m_geom_name, sizeof(m_body.m_geom_name));
			m_body.m_transform = body_mesh->GetLocalMatrix();
			m_body.m_animation = weapon_tranform->AsAnimationMixer();
		}

		//
		//	Look for backsight
		//
		{
			const Object* backsight_transform = weapon_tranform->GetChild(L"backsight_transform");
			if (!backsight_transform)
			{
				m_backsight.m_support = false;
				m_backsight.m_geom_index = -1;
				memset(m_backsight.m_geom_name, 0, sizeof(m_backsight.m_geom_name));
				m_backsight.m_transform = Math::mat4::CreateIdentity();
			}
			else
			{
				const Object* backsight_mesh = backsight_transform->GetChild(name + L"_backsight_mesh");
				if (!backsight_mesh)
				{
					System::Logger::Instance()->WriteError(L"Can't find '*backsight_mesh' though 'backsight_transform was found, scene is not a weapon scheme");
					return;
				}
				m_backsight.m_support = true;
				System::string filename = name + L"_backsight_mesh.vao";
				filename.ToANSI(m_backsight.m_geom_name, sizeof(m_backsight.m_geom_name));
				m_backsight.m_geom_index = -1;
				m_backsight.m_transform = backsight_transform->GetLocalMatrix();
				m_backsight.m_animation = backsight_transform->AsAnimationMixer();
			}
		}

		//
		//	Look for holder
		//
		{
			const Object* holder_transform = weapon_tranform->GetChild(L"holder_transform");
			if (!holder_transform)
			{
				m_holder.m_support = false;
				m_holder.m_geom_index = -1;
				memset(m_holder.m_geom_name, 0, sizeof(m_holder.m_geom_name));
				m_holder.m_transform = Math::mat4::CreateIdentity();
			}
			else
			{
				const Object* holder_mesh = holder_transform->GetChild(name + L"_holder_mesh");
				if (!holder_mesh)
				{
					System::Logger::Instance()->WriteError(L"Can't find '*holder_mesh' though 'holder_transform was found, scene is not a weapon scheme");
					return;
				}
				m_holder.m_support = true;
				System::string filename = name + L"_holder_mesh.vao";
				filename.ToANSI(m_holder.m_geom_name, sizeof(m_holder.m_geom_name));
				m_holder.m_geom_index = -1;
				m_holder.m_transform = holder_transform->GetLocalMatrix();
				m_holder.m_animation = holder_transform->AsAnimationMixer();
			}
		}

		//
		//	Look for light transform
		//
		{
			const Object* light_transform = weapon_tranform->GetChild(L"light_transform");
			if (!light_transform)
			{
				m_light.m_support = false;
				m_light.m_geom_index = -1;
				memset(m_light.m_geom_name, 0, sizeof(m_light.m_geom_name));
				m_light.m_transform = Math::mat4::CreateIdentity();
			}
			else
			{
				const Object* light_mesh = light_transform->GetChild(name + L"_light_mesh");
				if (!light_mesh)
				{
					System::Logger::Instance()->WriteError(L"Can't find '*light_mesh' though 'holder_transform was found, scene is not a weapon scheme");
					return;
				}
				m_light.m_support = true;
				System::string filename = name + L"_light_mesh.vao";
				filename.ToANSI(m_light.m_geom_name, sizeof(m_light.m_geom_name));
				m_light.m_geom_index = -1;
				m_light.m_transform = light_transform->GetLocalMatrix();
				m_light.m_animation = light_transform->AsAnimationMixer();				
			}
		}

		//
		//	Look for lock transform
		//
		{
			const Object* lock_transform = weapon_tranform->GetChild(L"lock_transform");
			if (!lock_transform)
			{
				m_lock.m_support = false;
				m_lock.m_geom_index = -1;
				memset(m_lock.m_geom_name, 0, sizeof(m_lock.m_geom_name));
				m_lock.m_transform = Math::mat4::CreateIdentity();
			}
			else
			{
				const Object* lock_mesh = lock_transform->GetChild(name + L"_lock_mesh");
				if (!lock_mesh)
				{
					System::Logger::Instance()->WriteError(L"Can't find '*light_mesh' though 'holder_transform was found, scene is not a weapon scheme");
					return;
				}
				m_lock.m_support = true;
				System::string filename = name + L"_light_mesh.vao";
				filename.ToANSI(m_lock.m_geom_name, sizeof(m_lock.m_geom_name));
				m_lock.m_geom_index = -1;
				m_lock.m_transform = lock_transform->GetLocalMatrix();
				m_lock.m_animation = lock_transform->AsAnimationMixer();
			}
		}

		//
		//	Look for grenade transform
		//
		{
			const Object* grenade_transform = weapon_tranform->GetChild(L"grenade_transform");
			if (!grenade_transform)
			{
				m_grenade.m_support = false;
				m_grenade.m_geom_index = -1;
				memset(m_grenade.m_geom_name, 0, sizeof(m_grenade.m_geom_name));
				m_grenade.m_transform = Math::mat4::CreateIdentity();
			}
			else
			{
				const Object* grenade_mesh = grenade_transform->GetChild(name + L"_grenade_mesh");
				if (!grenade_mesh)
				{
					System::Logger::Instance()->WriteError(L"Can't find '*light_mesh' though 'holder_transform was found, scene is not a weapon scheme");
					return;
				}
				m_grenade.m_support = true;
				System::string filename = name + L"_light_mesh.vao";
				filename.ToANSI(m_grenade.m_geom_name, sizeof(m_grenade.m_geom_name));
				m_grenade.m_geom_index = -1;
				m_grenade.m_transform = grenade_transform->GetLocalMatrix();
				m_grenade.m_animation = grenade_transform->AsAnimationMixer();
			}
		}
	}
}
