#ifndef _H_PUNK_UTILITY_HUMAN
#define _H_PUNK_UTILITY_HUMAN

#include "../config.h"
#include "../model/static_mesh.h"
#include "../model/armature.h"

namespace Utility
{
	class LIB_UTILITY Human
	{
		StaticMesh* m_head;
		StaticMesh* m_hair;
		StaticMesh* m_body;
		StaticMesh* m_arms;
		StaticMesh* m_legs;
		StaticMesh* m_feet;

		Armature* m_armature;
		
		ArmatureAnimation* m_head_animation;
		ArmatureAnimation* m_hear_animation;
		ArmatureAnimation* m_body_animation;
		ArmatureAnimation* m_arms_animation;
		ArmatureAnimation* m_legs_animation;
		ArmatureAnimation* m_feet_animation;
				
	public:

		StaticMesh* GetHead() { return m_head; }
		StaticMesh* GetHair() { return m_hair; }
		StaticMesh* GetBody() { return m_body; }
		StaticMesh* GetArms() { return m_arms; }
		StaticMesh* GetLegs() { return m_legs; }
		StaticMesh* GetFeet() { return m_feet; }

		void SetHead(StaticMesh* head) { m_head = head; }
		void SetHair(StaticMesh* hair) { m_hair = hair; }
		void SetBody(StaticMesh* body) { m_body = body; }
		void SetArms(StaticMesh* arms) { m_arms = arms; }
		void SetLegs(StaticMesh* legs) { m_legs = legs; }
		void SetFeet(StaticMesh* feet) { m_feet = feet; }
	};
}

#endif