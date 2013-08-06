#ifndef _H_PUNK_VIRTUAL_DATA_DOOR
#define _H_PUNK_VIRTUAL_DATA_DOOR

#include "../../config.h"
#include "../../math/portal.h"
#include "../../system/object.h"
#include "../../opengl/renderable/renderable_data.h"

namespace Virtual
{
	class Location;

	class PUNK_ENGINE_API Door : public System::Object
	{
	public:
		enum State { CLOSED, OPENED };

	public:

		virtual void Save(System::Buffer* buffer) const;
		virtual void Load(System::Buffer* buffer);

		State GetState() const { return m_state; }
		void SetState(State value) { m_state = value; }

		const Math::Portal& GetPortal() const { return m_portal; }
		const System::string& GetLocationName() const {return m_location_name; }

	private:

		State m_state;
		Math::Portal m_portal;
		System::string m_location_name;		
	};
}

#endif	//	_H_PUNK_VIRTUAL_DATA_DOOR
