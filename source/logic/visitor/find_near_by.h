//#ifndef _H_FIND_NEAR_BY
//#define _H_FIND_NEAR_BY
//
//#include "../config.h"
//#include <vector>
//#include <string>
//#include "../../math/vec3.h"
//#include "visitor.h"
//
//namespace Logic
//{
//	class PUNK_LOGIC_MODULE FindNearBy : public Visitor
//	{
//		Math::vec3 m_center;
//		float m_radius;
//		std::wstring m_type;
//		std::vector<SolidEntity*> m_result;
//	public:
//		FindNearBy(const Math::vec3& center, float radius, const wchar_t* type);
//		virtual bool Visit(AbstractEntity* e) { return true; }
//		virtual bool Visit(ComplexEntity* e);
//		virtual bool Visit(SimpleEntity* e);
//		virtual bool Visit(SpaceEntity* e) { return true; }
//		std::vector<SolidEntity*>& GetResult() { return m_result; }
//	};
//}
//
//#endif
