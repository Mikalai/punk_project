#ifndef _H_PUNK_VIRTUAL_LIGHT_SET
#define _H_PUNK_VIRTUAL_LIGHT_SET

#include "../../config.h"
#include "../../system/compound_object.h"

namespace Virtual
{
	class Light;

	class PUNK_ENGINE_API LightSet : public System::CompoundObject
	{
	public:
		Light* GetLight(int index);
		const Light* GetLight(int index) const;
		virtual bool Save(std::ostream& stream) const;
		virtual bool Load(std::istream& stream);

		static LightSet* CreateFromStream(std::istream& stream);
	};
}

#endif	//	_H_PUNK_VIRTUAL_LIGHT_SET


