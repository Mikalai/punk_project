#ifndef _H_CHARACTER_BODY
#define _H_CHARACTER_BODY

#include "../punk_engine/punk_engine.h"

class CharacterBody : public Render::
{
	int m_feet_geom;
	int m_low_geom;
	int m_arms_geom;
	int m_head_geom;
	int m_up_geom;

};

#endif	//	_H_CHARACTER_BODY