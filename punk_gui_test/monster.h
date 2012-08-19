#ifndef _H_MONSTER_CONTROL
#define _H_MONSTER_CONTROL

#include "../punk_engine/punk_engine.h"
#include "field.h"

class MonsterControl
{
	float m_timer;
	Math::mat4 m_location;
	Utility::ArmatureRef m_armature;
	Utility::ObjectRef m_character;
	Utility::CameraRef m_camera;
	std::auto_ptr<Render::CharacterRender> m_chr_render;

	Field* m_field;

	float m_speed;
	float m_rot_speed;
	float m_horizontal_rotation;
	Math::vec3 m_dir;

	std::vector<float> m_animation;

	enum States { STATE_GO_FORWARD, STATE_STAY, STATE_STRAFE_LEFT};

	States m_state;

	float m_back_rotation;

	Audio::Player m_players[2];

public:
	MonsterControl();
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

	Math::mat4& GetLocation() { return m_location; }
	const Math::mat4& GetLocation() const { return m_location; }
	void SetLocation(const Math::mat4 l) { m_location = l; }
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

#endif	//	_H_MONSTER_CONTROL