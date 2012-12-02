#ifndef _H_PUNK_UTILITY_ACTION
#define _H_PUNK_UTILITY_ACTION

#include "../../system/object.h"
#include "../../string/string.h"

namespace Utility
{
	class ActionDesc;
}

namespace Virtual
{
	class Animation;
}

namespace Virtual
{
	class Action : public System::Object
	{			
	public:		
		Action();
		Action(Utility::ActionDesc& desc);

		const System::string& GetName() const { return m_name; }
		int GetStartFrame() const { return m_start_frame; }		
		int GetEndFrame() const { return m_end_frame; }
		
		virtual bool Save(std::ostream& stream) const;
		virtual bool Load(std::istream& stream);
		virtual ~Action();

	protected:
//		void AddAnimation(Animation* value) { m_animations.push_back(value); }
		void SetEndFrame(const int frame) { m_end_frame = frame; }
		void SetName(const System::string& name);
		void SetStartFrame(int frame) { m_start_frame = frame; }

	private:
		Action(const Action&);
		Action& operator = (const Action&);

	private:
		System::string m_name;
		int m_start_frame;
		int m_end_frame;	
		std::vector<Animation*> m_animations;
	};
}

#endif