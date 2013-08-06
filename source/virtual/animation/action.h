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
    class PUNK_ENGINE_API Action : public System::CompoundObject, public System::Aspect<Action*, System::string>
	{
	public:
		Action();

		int GetStartFrame() const { return m_start_frame; }
		int GetEndFrame() const { return m_end_frame; }
		virtual ~Action();

		void SetEndFrame(const int frame) { m_end_frame = frame; }
		void SetStartFrame(int frame) { m_start_frame = frame; }

        void SetName(System::string& value);
        const System::string& GetName() const;

        virtual void Save(System::Buffer* buffer) const override;
        virtual void Load(System::Buffer* buffer) override;

	private:
		Action(const Action&);
		Action& operator = (const Action&);

	private:
		int m_start_frame;
		int m_end_frame;
        System::string m_name;
	};
}

#endif
