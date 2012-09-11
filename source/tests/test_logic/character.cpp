#include "character.h"
#include "all_armature.h"

Character::Character() : m_body(MALE), m_state(IDLE)
{
	m_bbox.Min() = Math::vec3(-0.5, 0, -0.5);
	m_bbox.Max() = Math::vec3(0.5, 1.8, 0.5);
	m_armature = AllArmature::Instance()->m_male_armature.get();
	m_scale = 4.0;
}

void Save(std::ostream& stream)
{

}