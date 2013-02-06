#ifndef _H_PUNK_UTILITY_ACTION
#define _H_PUNK_UTILITY_ACTION

#include "../../system/compound_object.h"
#include "../../system/aop/aop.h"
#include "../../system/smart_pointers/module.h"
#include "../../string/string.h"

namespace Virtual
{
	class Animation;
}

namespace Virtual
{
	//	Animation is a child of Action
	class Action : public System::CompoundObject, public System::Aspect<System::Proxy<Action>, System::string>
	{			
	public:		
		Action();

		int GetStartFrame() const { return m_start_frame; }		
		int GetEndFrame() const { return m_end_frame; }

		virtual bool Save(std::ostream& stream) const;
		virtual bool Load(std::istream& stream);
		virtual ~Action();

		static System::Proxy<Action> CreateFromFile(const System::string& path);
		static System::Proxy<Action> CreateFromStream(std::istream& stream);

		void SetEndFrame(const int frame) { m_end_frame = frame; }
		void SetStartFrame(int frame) { m_start_frame = frame; }

	private:
		Action(const Action&);
		Action& operator = (const Action&);

	private:
		int m_start_frame;
		int m_end_frame;			
	};
}

#endif