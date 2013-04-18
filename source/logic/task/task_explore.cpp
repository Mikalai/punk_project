//#include "task.h"
//#include "task_explore.h"
//#include "../entities/character.h"
//
//namespace Logic
//{
//	TaskExplore::TaskExplore(const Math::vec3& center, float radius)
//		: m_center(center)
//		, m_radius(radius)
//	{
//		m_priority = 0;
//	}
//
//	bool TaskExplore::Perform(Character* c, float delta_in_ms)
//	{
//		const Math::vec3& chr_pos = c->GetPosition();
//
//		if ((chr_pos - m_next_point).Length() < 0.5)
//			m_next_point.Set((rand() / (float)RAND_MAX)*m_radius, 0, (rand() / (float)RAND_MAX)*m_radius);
//
//		Math::vec3 p = c->GetPosition();
//
//		double speed = c->GetPropertyCollection()["SPEED"].AsReal();
//		Math::vec3 dir = (m_next_point - p).Normalized();
//		const Math::vec3& orient = c->GetOrientation();
//		dir = 0.8f * orient + 0.2f * dir;
//
//		p += dir * (float)speed * (float)delta_in_ms / (1000.0f);
//		c->SetOrientation(dir);
//		c->SetPosition(p);
//
//		return false;
//	}
//
//	const System::string TaskExplore::ToString() const
//	{
//		return System::string::Format(L"Go to: (%f, %f, %f)", m_next_point[0], m_next_point[1], m_next_point[2]);
//	}
//
//}
