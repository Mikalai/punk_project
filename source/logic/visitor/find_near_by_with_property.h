//#ifndef _H_FIND_NEAR_BY_WITH_PROPERTY
//#define _H_FIND_NEAR_BY_WITH_PROPERTY
//
//#include "../config.h"
//#include <vector>
//#include <string>
//
//#include "visitor.h"
//#include "../code.h"
//
//namespace Logic
//{
//	class PUNK_LOGIC_MODULE FindNearByWithProperty : public Visitor
//	{
//		Math::vec3 m_center;
//		float m_radius;
//		std::wstring m_type;
//		ID m_required_property;
//		std::vector<SolidEntity*> m_result;
//	public:
//		FindNearByWithProperty(const Math::vec3& center, float radius, const wchar_t* type, ID property);
//		virtual bool Visit(AbstractEntity* e) { return true; }
//		virtual bool Visit(ComplexEntity* e);
//		virtual bool Visit(SimpleEntity* e);
//		virtual bool Visit(SpaceEntity* e) { return true; }
//		std::vector<SolidEntity*>& GetResult() { return m_result; }
//	};
//}
//
//#endif
