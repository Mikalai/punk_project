#ifndef _H_PUNK_VIRTUAL_RENDERABLE_PROXY
#define _H_PUNK_VIRTUAL_RENDERABLE_PROXY

#include "../../config.h"
//#include "../../system/object.h"
#include "entity.h"

namespace Virtual
{

	/*class PUNK_ENGINE Proxy : public System::Object
	{
	public:
		Proxy();
		explicit Proxy(const Utility::WorldDesc& world_desc, const Utility::ObjectDesc& value);

		void SetData(System::Object* value ) { m_data = value; }
		System::Object* AsObject() { return m_data; }
		const System::Object* AsObject() const { return m_data; }		

		virtual bool Save(std::ostream& stream) const;
		virtual bool Load(std::istream& stream);
		virtual ~Proxy();

	private:
		System::Object* m_data;
	};*/
}

#endif	//	_H_PUNK_VIRTUAL_RENDERABLE_PROXY