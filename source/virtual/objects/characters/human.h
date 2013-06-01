#ifndef _H_PUNK_VIRTUAL_OBJECTS_HUMAN
#define _H_PUNK_VIRTUAL_OBJECTS_HUMAN

#include "../../data/module.h"

namespace Virtual
{
	class Armature;

	class PUNK_ENGINE_PUBLIC Human
	{
	public:
		Human();
		virtual ~Human();

		Armature* GetArmature();
		void SetArmature(Armature* value);
		Geometry* GetGeometry();
		void GetGeometry(Geometry* value);

		struct HumanImpl;
		HumanImpl* impl;

	private:
		Human(const Human&);
		Human& operator = (const Human&);
	};
}

#endif	//	_H_PUNK_VIRTUAL_OBJECTS_HUMAN
