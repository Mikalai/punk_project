#ifndef _H_PUNK_UTILITY_ACTION
#define _H_PUNK_UTILITY_ACTION

#include "../../system/compound_object.h"
#include "../../system/aop/aop.h"
#include "../../system/serializable.h"
#include "../../system/smart_pointers/module.h"
#include "../../string/string.h"

namespace Virtual
{
    class Animation;

	//	Animation is a child of Action
    class PUNK_ENGINE_API Action : public System::CompoundObject
	{
	public:
		Action();
        Action(const Action&) = delete;
        Action& operator = (const Action&) = delete;
        virtual ~Action();

		int GetStartFrame() const { return m_start_frame; }
		int GetEndFrame() const { return m_end_frame; }

		void SetEndFrame(const int frame) { m_end_frame = frame; }
		void SetStartFrame(int frame) { m_start_frame = frame; }

        void SetName(System::string& value);
        const System::string& GetName() const;

	private:
		int m_start_frame;
		int m_end_frame;
        System::string m_name;

        PUNK_OBJECT(Action)
	};

    PUNK_OBJECT_UTIL(Action)
}

#endif
