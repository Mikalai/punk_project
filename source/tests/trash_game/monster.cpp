#include "monster.h"

MonsterControl::MonsterControl()
{
	m_armature = Utility::ArmatureManager::Instance()->Load(L"monster_armature.armature");
	m_armature->GetArmatureAnimation().EnableTrack(L"idle", true);

	m_character = Utility::ObjectManager::Instance()->Load(L"monster_armature.object");
	
	m_dir.Set(0, 0, 1);
	m_speed = 0;

	m_animation.resize(5);
	std::fill(m_animation.begin(), m_animation.end(), 0);

	m_state = STATE_STAY;

	m_back_rotation = 0;

	//	to initialize audio call instance
	Audio::AudioManager::Instance();
	for (int i = 0; i < sizeof(m_players)/sizeof(m_players[0]); ++i)
	{
		m_players[i].Init();
	}

	m_animation[0] = 0;

	m_chr_render.reset(new Render::CharacterRender());
}

void MonsterControl::Forward()
{
}

void MonsterControl::StrafeLeft()
{

}

void MonsterControl::Die()
{

}

void MonsterControl::Stop()
{

}

void MonsterControl::Aiming(bool v)
{

}

void MonsterControl::RotateHorizontal(float angle)
{	

}

void MonsterControl::RotateVertical(float angle)
{

}

void MonsterControl::Fire()
{

}

void MonsterControl::Update(float dt)
{		
	m_animation[0] +=  dt*10.0;
	m_armature->GetArmatureAnimation().UpdateBones(m_animation[0]);	
		
	Math::vec3 pos = m_location.TranslationPart();	
	pos.Y() = m_field->GetTerrain()->GetHeight(pos.X(), pos.Z());
	m_location = Math::mat4::CreateTranslate(pos)*m_location.RotationPart4x4();
}

void MonsterControl::Render()
{
	Render::CharacterRender::Parameters params(m_character, m_camera, m_armature, &m_location);
	params.m_show_bbox = true;
	params.m_show_aabb = true;
	m_chr_render->Render(&params);
}

void MonsterControl::Update(float time, float dt)
{
	m_timer += dt;
}

const Math::vec3 MonsterControl::GetDirection() const
{
	return (m_location).RotationPart()*
		Math::mat4::CreateRotation(-1, 0, 0, m_back_rotation).RotationPart()
		*Math::vec3(0,0,1);
}

const Math::mat4 MonsterControl::GetRightHandTransform() const
{
	Utility::Bone* arm1 = m_armature->GetBoneByName(L"Thumb_R");
	Math::mat4 m1 = arm1->GetAnimatedGlobalMatrix(Math::mat4())*arm1->GetWorldMatrix();
	return m_location*Math::mat4::CreateRotation(1, 0, 0, -Math::PI/2)*m1;
}

