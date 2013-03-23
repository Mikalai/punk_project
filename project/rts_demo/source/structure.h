#ifndef _H_STRUCTURE
#define _H_STRUCTURE

#include "../../../source/punk_engine.h"
#include "dynamic.h"

class StructureScheme;
class GameEntity;

class Structure : public IDynamic
{
public:

	Structure(StructureScheme*);

	StructureScheme* GetStructureScheme();	
	const Math::BoundingSphere GetBoundingSphere();
	const Math::vec3 GetPosition();
	const Math::vec3 GetDirection();
	void SetPosition(const Math::vec3& value);

	GameEntity* ToGameEntity();

	void EnableDestruction(bool value);
	bool IsDestructible() const;

protected:
	StructureScheme* m_scheme;
	GameEntity* m_node;
	Scene::TransformNode* m_transform_node;
	Math::vec3 m_location;
	float m_angle_orientation; //	angle around z-axis
	bool m_destructuble;
};

#endif	//	_H_STRUCTURE
