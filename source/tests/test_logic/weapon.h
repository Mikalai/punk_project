#ifndef _H_WEAPON
#define _H_WEAPON

#include "../punk_engine/system/driver/video/driver.h"

class WeaponType
{
public:
	Math::vec3 m_position;
	int m_shoot_speed;
	int m_max_holder_capacity;
	int m_reload_time_ms;
};

class Weapon
{
public:
	WeaponType* m_type;
	Math::vec3 m_position;
	int m_holder_bullets_count;	
	OpenGL::Texture2D* m_diffuse_map_body;
	OpenGL::StaticObject* m_body_vao;
	OpenGL::Texture2D* m_diffuse_map_holder;
	OpenGL::StaticObject* m_holder_vao;
	OpenGL::Texture2D* m_diffuse_map_backsight;
	OpenGL::StaticObject* m_backsight_vao;
};

class Character;

class WeaponRenderable
{
public:
	void Render(Weapon* weapon, Character* player, OpenGL::TextureContext* tc, OpenGL::RenderContext* rc);
};

struct AllWeapon
{
	std::auto_ptr<Weapon> m_mini14;
	std::auto_ptr<Weapon> m_m16a2;

	static std::auto_ptr<AllWeapon> m_instance;

	AllWeapon();

	static AllWeapon* Instance() 
	{
		if (!m_instance.get())
			m_instance.reset(new AllWeapon);
		return m_instance.get();
	}

	static void Destroy()
	{
		m_instance.reset(0);
	}
};

#endif //	_H_WEAPON