#include "structure.h"
#include "game_entity.h"


Structure::Structure(StructureScheme* scheme)
	: m_scheme(scheme)
{}

StructureScheme* Structure::GetStructureScheme()
{
	return m_scheme;
}

const Math::BoundingSphere Structure::GetBoundingSphere()
{
	return m_node->GetBoundingSphere();
}

const Math::vec3 Structure::GetPosition()
{
	return m_world_position;
}

const Math::vec3 Structure::GetDirection()
{
	Math::vec3 dir(sinf(m_angle_orientation), 0, cosf(m_angle_orientation));
	return dir;
}
	
GameEntity* Structure::ToGameEntity()
{
	return m_node;
}