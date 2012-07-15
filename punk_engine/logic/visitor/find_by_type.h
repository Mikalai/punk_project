#ifndef _H_FIND_BY_TYPE
#define _H_FIND_BY_TYPE

#include "../config.h"
#include <vector>
#include <string>

#include "visitor.h"

namespace Logic
{
	class PUNK_LOGIC_MODULE FindByType : public Visitor
	{
		std::wstring m_type;
		std::vector<SolidEntity*> m_result;
	public:
		FindByType(const wchar_t* type);
		virtual bool Visit(AbstractEntity* e) { return true; };
		virtual bool Visit(ComplexEntity* e);
		virtual bool Visit(SimpleEntity* e);
		virtual bool Visit(SpaceEntity* e) { throw "Not implemented"; }

		std::vector<SolidEntity*>& GetResult() { return m_result; }
	};
}

#endif