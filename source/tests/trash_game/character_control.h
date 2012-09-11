#ifndef _H_CHARACTER_CONTROL
#define _H_CHARACTER_CONTROL

#include "../../punk_engine.h"
#include "field.h"

class CharacterControl
{
	float m_timer;

	Utility::ArmatureRef m_armature;

	Utility::ObjectRef m_character;

	std::auto_ptr<Utility::RigidBody> m_rb;

	OpenGL::VertexArrayObjectRef m_weapon_body;
	OpenGL::VertexArrayObjectRef m_weapon_holder;
	OpenGL::VertexArrayObjectRef m_weapon_backsight;
	OpenGL::VertexArrayObjectRef m_weapon_light;

	Utility::CameraRef m_camera;

	std::auto_ptr<Render::CharacterRender> m_chr_render;
	std::auto_ptr<OpenGL::RenderContextBumpMapping> m_weapon_rc;
	std::auto_ptr<OpenGL::TextureContext> m_tc;
	OpenGL::Texture2DRef m_diffuse_map;
	OpenGL::Texture2DRef m_normal_map;

	OpenGL::Texture2DRef m_weapon_diffuse_map;
	OpenGL::Texture2DRef m_weapon_normal_map;

	Field* m_field;

	float m_speed;
	float m_rot_speed;
	float m_horizontal_rotation;
	Math::vec3 m_dir;

	std::vector<float> m_animation;

	enum States { STATE_GO_FORWARD, STATE_STAY, STATE_STRAFE_LEFT};

	States m_state;

	float m_back_rotation;
	bool m_aiming;

	Utility::WeaponType* m_weapon;

	Audio::Player m_players[2];

	OpenGL::Line m_line;

	//	explosion on the ground
	std::auto_ptr<OpenGL::RenderContextParticle> m_rc_particle;
	std::auto_ptr<OpenGL::StaticObject> m_particle_vao;

public:
	CharacterControl();
	void Forward();
	void Backward();
	void StrafeLeft();
	void StrafeRight();
	void Stop();
	void Die();	 

	void Fire();

	void RotateHorizontal(float angle);
	void RotateVertical(float angle);
	void Aiming(bool flag);

	void Update(float dt);

	const Math::mat4 GetLocation() { return m_rb->GetLocation(); }
	void SetLocation(const Math::mat4 l) { m_rb->SetLocation(l); }
	Utility::ArmatureRef GetArmature() { return m_armature; }
	const Utility::ArmatureRef GetArmature() const { return m_armature; }
	void SetArmature(Utility::ArmatureRef amr) { m_armature = amr; }
	void SetCamera(Utility::CameraRef camera) { m_camera = camera; }

	void SetField(Field* field) { m_field = field; }
	Field* GetField() { return m_field; }

	void Update(float time, float dt);

	void Render();
	void Render(Utility::ObjectRef object, const Math::mat4& parent, const Math::mat4& view, const Math::mat4& proj);
	void RenderWeapon();
	void RenderPS();

	const Math::vec3 GetDirection() const;
	const Math::mat4 GetRightHandTransform() const;

	void RenderAxis();
};

#endif	//	_H_CHARACTER_CONTROL