#ifndef _H_PLAYER
#define _H_PLAYER

#include "../punk_engine/logic/entities/character.h"
#include "../punk_engine/math/bounding_box.h"

namespace Utility { class Armature; }
enum ItemType { WEAPON, FOOD, TOOLS };

class Character : public Logic::Character
{
public:
	int m_id;
	enum StateType {IDLE};
	enum BodyType {MALE};
	Math::BoundingBox m_bbox;
	BodyType m_body;
	Utility::Armature* m_armature;
	StateType m_state;
	float m_scale;

	void Save(std::ostream& stream) {}
	void Load(std::istream& stream) {}

	Character();
};

#endif //	_H_PLAYER